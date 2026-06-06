#include "functions.h"
#include "global_variables.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();


  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT_PULLUP);

  ball_x = random(0, 126);
  ball_y = random(10, 62);
  Serial.println("Setup started");
}

void loop() {
  Serial.println("loop start");
  display.clearDisplay();
  display.setTextColor(WHITE);

//Read values
  int joy_x, joy_y;
  read_joystick(joy_x, joy_y);
   Serial.println("joystick read");

//Show Menu With Rectangle
  int joystick_z = digitalRead(2);
  menu_options(start_menu, menu_rect_y_pos, joystick_z);
  Serial.println("menu options done");

// Menu Actions
  if(start_menu == 1){ //We are in Start Menu

    start_menu_display(display, joy_y);
    
    delay(50);}
    

 else{
    display.invertDisplay(false);
    display.drawRect(snake_x, snake_y, snake_width, snake_height, WHITE);
    snake_x = snake_x + snake_speed_x;
    snake_y = snake_y + snake_speed_y;

    //store_tail_memory(tail_x, tail_y);
    // for(int k = 1; k < tail_length; k++){
    // display.drawRect(tail_x[k], tail_y[k], snake_width, snake_height, WHITE);
    // }

    //Update Speed According To Score
    if((score != 1 || score != 0) && (score/4 > 1)){ 
        snake_speed = score/4;
      }

    //Snake is out of screen
    snake_out_of_screen(snake_x, snake_y);


    // move along x change to move along y
    update_snake_orientation(joy_x, joy_y, snake_width, snake_height, snake_speed,  snake_speed_x, snake_speed_y);
      

  //Ball
  display.drawRect(ball_x, ball_y, 4, 4, WHITE);
  
  if(ball_x >= snake_x && ball_x <= snake_x + snake_width && ball_y >= snake_y && ball_y <= snake_y + snake_height){
      
    snake_caught_ball(snake_speed_x, snake_speed_y, snake_length, ball_x, ball_y, score); //snake caught ball move it
  }


//Display Score and Speed
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Score " + String(score) + " Speed " + String(snake_speed));


    display.display();
  }

}













