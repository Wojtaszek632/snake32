/*
 * snake.c
 *
 *  Created on: Aug 22, 2021
 *      Author: Wojciech
 */
#include "snake.h"




int dx=5;
int dy=0;
int snake_len=1;
position snake[(LCD_WIDTH*LCD_HEIGHT)/25]={{50,50}};
position apple={100,100};




 int GetDist(position *pos1, position *pos2)
 {
	 int disx=pos1->x-pos2->x;
	 int disy=pos1->y-pos2->y;
	 return sqrt(disx*disx+disy*disy);

 }

 void get_user_input(uint16_t value[2],enum UserInput *user_input){

	 //map ADC values to <-1;1>
 	 float x_maped = (value[1] / 2048.0f)-1.0f ;
 	 float y_maped = ((value[0]/2048.0f)-1.0f);

 	 //calculate polar cords
 	 float radius = sqrt(x_maped*x_maped+y_maped*y_maped);
 	 float theta = atan2(y_maped,x_maped);

 	  if(radius<= 0.8f)
 	  {
 		  *user_input=CENTER;
 	  }
 	  else
 	  {
 		if(theta >= -0.8f && theta <= 0.8f) 		*user_input=RIGHT;
 	  	else if(theta > 0.8f && theta <= 2.3f) 		*user_input=UP;
 	  	else if(theta > 2.3f || theta < -2.3f) 		*user_input=LEFT;
 	  	else if(theta >= -2.3f && theta < -0.8f) 	*user_input=DOWN;
 	  }

   }

 //insert snake body parts
 void insert_snake(void)
 {
	 for(int body_frag=0; body_frag < snake_len; body_frag++)  //for every body fragment
	 	{
	 		for(int x_offset=-2; x_offset<3; x_offset++) //it should be 5 pixels wide
	 		{
	 			for(int y_offset=-2;y_offset<3;y_offset++) //and 5 pixels in height
	 			{
	 				lcd_put_pixel(snake[body_frag].x+x_offset, snake[body_frag].y+y_offset, __REV16(0x1f00));
	 			}
	 		}
	 	}
 }

 void insert_apple(void){
	 for(int x_offset=-2;x_offset<3;x_offset++) //it should be 5 pixels wide
	 {
		 for(int y_offset=-2;y_offset<3;y_offset++) //and 5 pixels in height
		 {
			 lcd_put_pixel(apple.x+x_offset,apple.y+y_offset, __REV16(0xe007));
		 }
	 }
}

 void check_for_colison_x(void)
 {
	 if( snake[0].x >= LCD_WIDTH-3)  snake[0].x=3;
	 if( snake[0].x <= 2)            snake[0].x=LCD_WIDTH-2;

 }

 void check_for_colison_y(void)
 {
	 if( snake[0].y >= LCD_HEIGHT-3)  snake[0].y=3;
	 if( snake[0].y <= 2)  			  snake[0].y=LCD_HEIGHT-2;
 }

 void check_for_end(void)
 {
	for(int body_frag=1; body_frag<snake_len; body_frag++) //for every body fragment
	{
		//if its distance to snake's head is smaller than size of one body fragment, snake ate itself
		if( GetDist(&snake[0] , &snake[body_frag]) < 5 )  snake_len=1;
	 }
 }

 void snake_follow(void)
 {
	//for every body fragment starting from the end
	for(int body_frag=(sizeof(snake)/sizeof(position))-1; body_frag>0; body_frag--)
	 {
		//move fragment to the coords of the body fragment before him (snake will folow itself)
		snake[body_frag].x=snake[body_frag-1].x;
		snake[body_frag].y=snake[body_frag-1].y;
	 }

 }
