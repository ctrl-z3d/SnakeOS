#include <Arduino.h>
#include "functions.h"
#include "global_variables.h"
#include <Adafruit_SSD1306.h> 
#include <Adafruit_GFX.h>



void read_joystick(int &joy_x, int &joy_y){

   joy_y = analogRead(A0);
   joy_x = analogRead(A1);
  
   joy_x = map(joy_x, 0, 1023, -180, 180);
   joy_y = map(joy_y, 0, 1023, -180, 180);

}

void swap(int &a, int &b){
  int temp = a;
  a = b;
  b = temp;
}


void menu_options(int &start_menu, int &menu_rect_y_pos, int &joystick_z){
  if(joystick_z == 0){
    if(start_menu == 1){
      // leaving menu, going to game
      if(menu_rect_y_pos != (24-20) + 32){
        reset_game();  // Start selected
      }
      // Resume selected, do nothing
      start_menu = 0;
    } else {
      // leaving game, going to menu
      start_menu = 1;
    }
    while(digitalRead(2) == 0);
}
}

void start_menu_display(Adafruit_SSD1306 &display, int &joy_y){

  display.invertDisplay(true);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(34, 24-16);
  display.println("Start");
  display.setCursor(34, 24+16);
  display.println("Resume");

  if(joy_y == -180){
       menu_rect_x_pos = (33 - 5);
       menu_rect_y_pos = (24-20) + 32;
       menu_rect_width = 7*12 ;
    } 
    
    else if(joy_y == 180){
       menu_rect_x_pos = 33 - 5;
       menu_rect_y_pos = 24-20;
       menu_rect_width = 7*10 ;
    }
     display.drawRect(menu_rect_x_pos, menu_rect_y_pos, menu_rect_width, 26, WHITE);
     display.display();
}

void reset_game(){
   snake_x = 0;
   snake_y = 0;
   snake_speed_y = 0;
   snake_speed_x = 1;
   snake_width = 20;
   snake_height = 5;
   score = 0;
   snake_speed = 1;
   snake_length = 20;
   tail_length = 1;
}

void snake_out_of_screen(int &snake_x, int &snake_y){
      //Snake is out of screen
    if(snake_x > 128) snake_x = 0;
    else if (snake_x < -20) snake_x = 128;
    if(snake_y > 64) snake_y = 0;
    else if (snake_y < -20) snake_y = 64;
}


int get_orientation(int sx, int sy){
    if (sx > 0) return 1;
    if (sx < 0) return -1;
    if (sy > 0) return 2;
    if (sy < 0) return -2;
    return 0;
}

void update_snake_orientation(int joy_x, int joy_y, int &snake_width, int &snake_height, int snake_speed,  int &snake_speed_x, int &snake_speed_y){
  
  if(((joy_y >= -180 && joy_y <= -150) || (joy_y >= 150 && joy_y <= 180))){  //change to y movement
     snake_width = 5;
    snake_height = snake_length;
    snake_speed_x = 0;

    snake_speed_y = (joy_y >= -180 && joy_y <= -150) ? snake_speed : -snake_speed;
    }
  
    if(((joy_x >= -180 && joy_x <= -150) || (joy_x >= 150 && joy_x <= 180))){  // change to x movement
     snake_height = 5;
     snake_width = snake_length;
     snake_speed_y = 0;

     snake_speed_x = (joy_x >= -180 && joy_x <= -150) ? -snake_speed : snake_speed;
    }
}


void snake_caught_ball(int snake_speed_x, int snake_speed_y, int &snake_length, int &ball_x, int &ball_y, int &score){

    ball_x = random(0, 126);
    ball_y = random(10, 62);
    score = score + 1;
    tail_length++;
    make_snake_tail_longer(snake_speed_x, snake_speed_y, snake_length, score); //current score value needed so keep in bottom
}


void make_snake_tail_longer(int snake_speed_x, int snake_speed_y, int &snake_length, int score){
  //move along x axis, increase width
  //move along y axis, increase height
  int orientation = get_orientation (snake_speed_x, snake_speed_y);

  snake_length = (orientation == 1 || orientation == -1 || orientation == 2 || orientation == -2) ? snake_length + 1: snake_length;
    

}


//Eats away RAM
/*void store_tail_memory(int* tail_x, int* tail_y){
  Serial.println("store start");
  
  if(tail_length >= 99) tail_length = 99;

   Serial.print("tail_length: ");
  Serial.println(tail_length);

  for(int k = tail_length-1; k > 0 ; k--){

    tail_x[k] = tail_x[k-1]; 
    tail_y[k] = tail_y[k-1]; // each slot takes the value of the slot ahead

  }
  Serial.println("shift done");
  tail_x[0] = snake_x;
  tail_y[0] = snake_y;
  Serial.println("head stored");
}
  */
  
