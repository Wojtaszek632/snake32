/*
 * snake.h
 *
 *  Created on: Aug 22, 2021
 *      Author: Wojciech
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#pragma once
#include <stdint.h>
#include <lcd.h>
#include "math.h"
#include <cmsis_gcc.h>


 enum UserInput {
	UP,//0
	DOWN,//1
	LEFT,//2
	RIGHT,//3
	CENTER//4
};

 typedef struct {
	 int x;
	 int y;
 }position;



 int dx;
 int dy;
 int snake_len;

 position snake[(LCD_WIDTH*LCD_HEIGHT)/25];
 position apple;


 int GetDist(position *pos1, position *pos2);
 void get_user_input(uint16_t value[2], enum UserInput *user_input);
 void insert_snake(void);
 void insert_apple(void);
 void check_for_colison_x(void);
 void check_for_colison_y(void);
 void check_for_end(void);
 void snake_follow(void);
#endif /* INC_SNAKE_H_ */
