#ifndef functions_H
#define functions_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>



void read_joystick(int &joy_x, int &joy_y);
void menu_options(int &start_menu, int &menu_rect_y_pos, int &joystick_z);
void swap(int &a, int &b);
void start_menu_display(Adafruit_SSD1306 &display, int &joy_y);
void reset_game();
void snake_out_of_screen(int &snake_x, int &snake_y);
int get_orientation(int sx, int sy);
void update_snake_orientation(int joy_x, int joy_y, int &snake_width, int &snake_height, int snake_speed,  int &snake_speed_x, int &snake_speed_y);
void snake_caught_ball(int snake_speed_x, int snake_speed_y, int &snake_length, int &ball_x, int &ball_y, int &score);
void make_snake_tail_longer(int snake_speed_x, int snake_speed_y, int &snake_length, int score);
void store_tail_memory(int* tail_x, int* tail_y);

#endif