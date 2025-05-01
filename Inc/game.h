/*
 * game.h
 *
 *  Created on: Apr 23, 2025
 *      Author: mgalchemy
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

#include "LCD_Driver.h"
#include "Button_Driver.h"
#include "ApplicationCode.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_exti.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rng.h"

#include <stdbool.h>
#include <stdio.h>




//this structure hold important game logic for use with functions and game flow
typedef struct game_logic{

	volatile bool game_over;		// controls game loop
	volatile uint32_t time;			// keeps track of time a new game is started, to determine total game play time for one round at end
	volatile bool player_one;       // is it player ones turn (true) or not
	volatile uint8_t cursor_loc;    // keeps track of cursor location to drop coins into columns
	volatile bool button_pressed;   // signal for when button is pressed, used for touch screen option screens
	volatile bool two_player_mode;  // keeps track of if its one or two player mode
	volatile uint8_t score_one;     // keeps track of how many times player one has won
	volatile uint8_t score_two;     // keeps track of how many times player two has won

}game_logic;


//first screen, has game mode choice
void title_screen(game_logic *game_logic);

//create the game grid
void test_grid(void);

//the main game loop is a do/while loop that continues as long as its not game over
void game_loop(game_logic *game_logic, int grid[7][6], RNG_HandleTypeDef *hrng);

//initialize the grid and game logic state variables
void initialize_game(game_logic *game_logic, int grid[7][6]);

//draws the cursor on the screen
void draw_cursor(game_logic *game_logic, int grid[7][6]);

//the final screen of a game round, shows time, and player scores
void last_screen(game_logic *game_logic);

//resets the games state variables for a new round
void reset_game(game_logic *game_logic, int grid[7][6]);


#endif /* INC_GAME_H_ */
