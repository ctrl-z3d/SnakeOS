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
  Serial.print("Free RAM: ");
Serial.println(freeRam());
  display.clearDisplay();
  display.display();
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT_PULLUP);

  food_x = random(0, 126);
  food_y = random(10, 62);


  Serial.println("Setup started");
}

void loop() {
  Serial.println(F("loop start"));
  display.clearDisplay();
  display.setTextColor(WHITE);

//Read values
  int joy_x, joy_y;
  read_joystick(joy_x, joy_y);
   Serial.println(F("joystick read"));

//Show Menu With Rectangle
  int joystick_z = digitalRead(2);
  menu_options(start_menu, menu_rect_y_pos, joystick_z);
  Serial.println(F("menu options done"));

// Menu Actions
  if(start_menu == 1){ //We are in Start Menu

    start_menu_display(display, joy_y);
    
    delay(50);}
    

 else{
    display.invertDisplay(false);
    display.drawRect(snake_x, snake_y, snake_width, snake_height, WHITE);
    snake_x = snake_x + snake_speed_x;
    snake_y = snake_y + snake_speed_y;


    //Update Speed According To Score
    if((score != 1 || score != 0) && (score/4 > 1)){ 
        snake_speed = score/4;
      }

    //Snake is out of screen
    snake_out_of_screen(snake_x, snake_y);


    // move along x change to move along y
    update_snake_orientation(joy_x, joy_y, snake_width, snake_height, snake_speed,  snake_speed_x, snake_speed_y);
      

  //Food
  display.drawRect(food_x, food_y, 4, 4, WHITE);
  
  if(food_x >= snake_x && food_x <= snake_x + snake_width && food_y >= snake_y && food_y <= snake_y + snake_height){
      
    snake_caught_ball(snake_speed_x, snake_speed_y, snake_length, food_x, food_y, score); //snake caught ball move it
  }


//Display Score and Speed
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Score " + String(score) + " Speed " + String(snake_speed));


    display.display();







  }

}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}











