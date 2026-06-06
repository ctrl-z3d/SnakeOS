#include <Arduino.h>
#include "global_variables.h"



int menu_rect_x_pos = 33 - 5;
int menu_rect_y_pos = 24-20;
int menu_rect_width = 7*10 ;

int snake_width = 20;
int snake_height = 5;
int start_menu = 1; // 1 means dont reset
int snake_x = 0;
int snake_y = 0;
int snake_speed_y = 0;
int snake_speed_x = 1;
int snake_speed = 1;

int ball_x;
int ball_y;
int score = 0;

int snake_length = 20;

int tail_length = 1;
int tail_x[100];
int tail_y[100];