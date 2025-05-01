/*
 * game.c
 *
 *  Created on: Apr 23, 2025
 *      Author: mgalchemy
 */

#include "game.h"



#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS



//the title screen where a player choses game mode
void title_screen(game_logic *game_logic){

	char title[] = "CONNECT FOUR!";
	char one_player[] = "ONE PLAYER";
	char two_player[] = "TWO PLAYER";

	LCD_SetTextColor(LCD_COLOR_BLACK);

	LCD_SetFont(&Font16x24);

	uint16_t x_pos = 8;

	for(int i = 0; i < 13; i++){
		LCD_DisplayChar(x_pos, 30, title[i]);
		x_pos += 18;
	}

	//horizontal line
	for (uint16_t i = 0; i < 240; i++){
		LCD_Draw_Pixel(i, 60, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 61, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 62, LCD_COLOR_BLACK);
	}

	//vertical line
	for (uint16_t i = 0; i < 259; i++){
		LCD_Draw_Pixel(119, 61+i, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(120, 61+i, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(121, 61+i, LCD_COLOR_BLACK);
	}

	uint16_t y_pos = 80;

	for(int i = 0; i < 10; i++){
		LCD_DisplayChar(60, y_pos, one_player[i]);
		LCD_DisplayChar(180, y_pos, two_player[i]);
		y_pos += 20;
	}

	bool game_select = false;
	uint8_t selection = 0;

	do {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			//printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			selection = StaticTouchData.x;
			game_select = true;
			//HAL_Delay(100);
		}
	} while (game_select == false);

	if(selection >= 0 && selection <= 120){				//RIGHT HALF OF SCREEN
		printf("Two-player selected\n");
		game_logic->two_player_mode = true;
	}
	else if(selection >= 120 && selection <= 240){    	//LEFT HALF OF SCREEN
		printf("One-player select\n");
		game_logic->two_player_mode = false;
	}


	LCD_Clear(0, LCD_COLOR_WHITE);
	x_pos = 8;
	for(int i = 0; i < 13; i++){
		LCD_DisplayChar(x_pos, 30, title[i]);
		x_pos += 18;
	}


	HAL_Delay(10);

	//get system time right before game loop starts, then subtract the time when the game is over to get total elapsed game time
	game_logic->time = HAL_GetTick();
	//printf(" game started at: %d\n", (int)game_logic->time);
}

//creates the game grid
void test_grid(void){

	//draw a 3px thick line horizontally across screen
	for (uint16_t i = 0; i < 240; i++){
		LCD_Draw_Pixel(i, 320, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 319, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 318, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(i, 288, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 287, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 286, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(i, 256, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 255, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 254, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(i, 224, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 223, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 222, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(i, 192, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 191, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 190, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(i, 160, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 159, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 158, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(i, 128, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 127, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(i, 126, LCD_COLOR_BLACK);
	}

	HAL_Delay(10);

	uint16_t offset = 6;
	uint16_t height = 190;
	uint16_t start = 129;

	//vertical 3px thick lines
	for (uint16_t i = 0; i < height; i++){

		LCD_Draw_Pixel(0, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(1, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(2, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(3, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(4, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(5, i+start, LCD_COLOR_BLACK);


		LCD_Draw_Pixel(0+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(1+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(2+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(32+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(33+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(34+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(64+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(65+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(66+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(96+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(97+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(98+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(128+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(129+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(130+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(160+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(161+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(162+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(192+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(193+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(194+offset, i+start, LCD_COLOR_BLACK);

		LCD_Draw_Pixel(224+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(225+offset, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(226+offset, i+start, LCD_COLOR_BLACK);


		LCD_Draw_Pixel(233, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(234, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(235, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(236, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(237, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(238, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(239, i+start, LCD_COLOR_BLACK);
		LCD_Draw_Pixel(240, i+start, LCD_COLOR_BLACK);
	}
	//printf("testing draw offscreen bug...\n");

	printf("created grid\n");
	HAL_Delay(10);
}


//initializes game starting conditions
void initialize_game(game_logic *game_logic, int grid[7][6]){

	printf("initializing game\n");

	game_logic->game_over = false;
	game_logic->time = 0;   //biggest number a uint16_t can be is 65535
	game_logic->player_one = true; //is it player ones turn (true) or other player (false)
	game_logic->cursor_loc = 3;    // middle column on game piece (0 is left, 6, right)
	game_logic->button_pressed = false;
	game_logic->two_player_mode = false;
	game_logic->score_one = 0;
	game_logic->score_two = 0;

	//initialize a prefilled grid
	///*
	//grid[0][5] = 2 ; grid[1][5] = 0 ; grid[2][5] = 2 ; grid[3][5] = 1 ; grid[4][5] = 2 ; grid[5][5] = 1 ; grid[6][5] = 2 ;
	//grid[0][4] = 2 ; grid[1][4] = 1 ; grid[2][4] = 2 ; grid[3][4] = 1 ; grid[4][4] = 2 ; grid[5][4] = 1 ; grid[6][4] = 2 ;
	//grid[0][3] = 1 ; grid[1][3] = 2 ; grid[2][3] = 1 ; grid[3][3] = 2 ; grid[4][3] = 1 ; grid[5][3] = 2 ; grid[6][3] = 1 ;
	//grid[0][2] = 1 ; grid[1][2] = 2 ; grid[2][2] = 1 ; grid[3][2] = 2 ; grid[4][2] = 1 ; grid[5][2] = 2 ; grid[6][2] = 1 ;
	//grid[0][1] = 2 ; grid[1][1] = 1 ; grid[2][1] = 2 ; grid[3][1] = 1 ; grid[4][1] = 2 ; grid[5][1] = 1 ; grid[6][1] = 2 ;
	//grid[0][0] = 2 ; grid[1][0] = 1 ; grid[2][0] = 2 ; grid[3][0] = 1 ; grid[4][0] = 2 ; grid[5][0] = 1 ; grid[6][0] = 2 ;
	//*/
}

//draw the cursor depending on which column it hovers over
void draw_cursor(game_logic *game_logic, int grid[7][6]){

	uint16_t y = 110;

	uint16_t color;
	if(game_logic->player_one == true){
		color = LCD_COLOR_BLUE;
	}
	else{
		color = LCD_COLOR_RED;
	}

	//clears all spots before drawing new one
	//                   x    y   r
	LCD_Draw_Circle_Fill(23, y, 14, LCD_COLOR_WHITE); // test dot
	LCD_Draw_Circle_Fill(55, y, 14, LCD_COLOR_WHITE); // test dot
	LCD_Draw_Circle_Fill(87, y, 14, LCD_COLOR_WHITE); // test dot
	LCD_Draw_Circle_Fill(119, y, 14, LCD_COLOR_WHITE); // test dot
	LCD_Draw_Circle_Fill(151, y, 14, LCD_COLOR_WHITE); // test dot
	LCD_Draw_Circle_Fill(183, y, 14, LCD_COLOR_WHITE); // test dot
	LCD_Draw_Circle_Fill(215, y, 14, LCD_COLOR_WHITE); // test dot

	//placing cursor in correct location based on the game_logic variable
	uint16_t new_cursor = game_logic->cursor_loc;
	new_cursor *= 32;
	new_cursor += 23;
	//                   x    y   r
	LCD_Draw_Circle_Fill(new_cursor, y, 14, color); // test dot
	HAL_Delay(10);
}


//touch screen left or right to move the cursor location
void move_cursor(game_logic *game_logic, int grid[7][6]){

	uint8_t screen_side = 0;

	do {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			screen_side = StaticTouchData.x;
			game_logic->button_pressed = true;

			HAL_Delay(10);
		}
	} while (game_logic->button_pressed == false);

	game_logic->button_pressed = false;

	if(screen_side > 0 && screen_side <= 120){				//RIGHT HALF OF SCREEN
		printf("clicked right side\n");
		if(game_logic->cursor_loc < 6){
			printf("    moved right\n");
			game_logic->cursor_loc += 1;
			draw_cursor(game_logic, grid);
		}
	}
	else if(screen_side >= 120 && screen_side < 240){    	//LEFT HALF OF SCREEN
		printf("clicked left side\n");
		if(game_logic->cursor_loc > 0){
			printf("    moved left\n");
			game_logic->cursor_loc -= 1;
			draw_cursor(game_logic, grid);
		}
	}

	HAL_Delay(10);
}

//update the screen to show where game pieces are
void update_pieces(game_logic *game_logic, int grid[7][6]){

	//scans from bottom-left of grid to right & upward
	for(uint16_t y = 0; y < 6; y++){
		for(uint16_t x = 0; x < 7; x++){
			if(grid[x][y] == 0){
				LCD_Draw_Circle_Fill(23+(x*32), 303-(y*32), 14, LCD_COLOR_WHITE);
			}
			else if(grid[x][y] == 1){
				LCD_Draw_Circle_Fill(23+(x*32), 303-(y*32), 14, LCD_COLOR_BLUE);
			}
			else if(grid[x][y] == 2){
				LCD_Draw_Circle_Fill(23+(x*32), 303-(y*32), 14, LCD_COLOR_RED);
			}
		}
	}

	HAL_Delay(10);
}

//return where in the column an open spot is for coin to land
uint8_t open_spot(uint8_t column, int grid[7][6]){

	uint8_t open_spot = 6;

	for(int y = 0; y < 6; y++){
		if(grid[column][y] == 0){
			open_spot = y;
			break;
		}
	}

	return open_spot;
}


//swap the active players turns
void swap_player(game_logic *game_logic){
	//if(game_logic->two_player_mode == true){
	//	game_logic->player_one = !(game_logic->player_one);
	//}
	game_logic->player_one = !(game_logic->player_one);
	game_logic->cursor_loc = 3;
	HAL_Delay(10);
}

//place a game piece in the grid
void drop_game_piece(game_logic *game_logic, int grid[7][6], bool *button_press){

	uint8_t column;

	if(*button_press == true){

		*button_press = false;

		column =  game_logic->cursor_loc;
		uint8_t row = open_spot(column, grid);

		if (row < 6 && game_logic->player_one == true){ 				//player ones placement (two player mode)
			printf("    dropping game piece!\n");
			grid[column][row] = 1;
			swap_player(game_logic);//swap players after the piece is dropped
			draw_cursor(game_logic, grid);
			HAL_Delay(100);
		}
		else if (row < 6 && game_logic->player_one == false){ 			//player twos placement (one player mode)
			printf("    dropping game piece!\n");
			grid[column][row] = 2;
			swap_player(game_logic);//swap players after the piece is dropped
			draw_cursor(game_logic, grid);
			HAL_Delay(100);
		}
	}

	game_logic->button_pressed = true; //this will bypass move_cursor do/while loop to place a piece and update without needing to move cursor

	HAL_Delay(10);
}

//check if you have won the game based on pieces after youve moved
bool check_win(game_logic *game_logic, int grid[7][6]){
	//4 UP/DOWN in a column case
	for(int y = 0; y <= 2; y++){
		for(int x = 0; x <= 6; x++){
			if(grid[x][y]== 1 && grid[x][y+1] == 1 && grid[x][y+2] == 1 && grid[x][y+3] == 1){
				game_logic->game_over = true;
				game_logic->score_one++;
			}
		}
	}
	//4 LEFT/RIGHT in a row case
	for(int y = 0; y <= 5; y++){
		for(int x = 0; x <= 3; x++){
			if(grid[x][y]== 1 && grid[x+1][y] == 1 && grid[x+2][y] == 1 && grid[x+3][y] == 1){
				game_logic->game_over = true;
				game_logic->score_one++;
			}
		}
	}
	//4 UP/LEFT in a diagonal
	for(int y = 0; y <= 2; y++){
		for(int x = 3; x <= 6; x++){
			if(grid[x][y]== 1 && grid[x-1][y+1] == 1 && grid[x-2][y+2] == 1 && grid[x-3][y+3] == 1){
				game_logic->game_over = true;
				game_logic->score_one++;
			}
		}
	}
	//4 UP/RIGHT in a diagonal
	for(int y = 0; y <= 2; y++){
		for(int x = 0; x <= 3; x++){
			if(grid[x][y]== 1 && grid[x+1][y+1] == 1 && grid[x+2][y+2] == 1 && grid[x+3][y+3] == 1){
				game_logic->game_over = true;
				game_logic->score_one++;
			}
		}
	}
	return (game_logic->game_over);
}

//display the winning screen
void win_screen(void){
	LCD_Clear(0, LCD_COLOR_GREEN);
	HAL_Delay(500);
	char title[] = "  YOU  WIN!  ";
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_SetFont(&Font16x24);
	uint16_t x_pos = 8;
	for(int i = 0; i < 13; i++){
		LCD_DisplayChar(x_pos, 30, title[i]);
		x_pos += 18;
	}
	HAL_Delay(500);
}


// check if player two has won, aka player one lost
bool check_lose(game_logic *game_logic, int grid[7][6]){
	//4 UP/DOWN in a column case
	for(int y = 0; y <= 2; y++){
		for(int x = 0; x <= 6; x++){
			if(grid[x][y]== 2 && grid[x][y+1] == 2 && grid[x][y+2] == 2 && grid[x][y+3] == 2){
				//lose = true;
				game_logic->game_over = true;
				game_logic->score_two++;
			}
		}
	}
	//4 LEFT/RIGHT in a row case
	for(int y = 0; y <= 5; y++){
		for(int x = 0; x <= 3; x++){
			if(grid[x][y]== 2 && grid[x+1][y] == 2 && grid[x+2][y] == 2 && grid[x+3][y] == 2){
				//lose = true;
				game_logic->game_over = true;
				game_logic->score_two++;
			}
		}
	}
	//4 UP/LEFT in a diagonal
	for(int y = 0; y <= 2; y++){
		for(int x = 3; x <= 6; x++){
			if(grid[x][y]== 2 && grid[x-1][y+1] == 2 && grid[x-2][y+2] == 2 && grid[x-3][y+3] == 2){
				//lose = true;
				game_logic->game_over = true;
				game_logic->score_two++;
			}
		}
	}
	//4 UP/RIGHT in a diagonal
	for(int y = 0; y <= 2; y++){
		for(int x = 0; x <= 3; x++){
			if(grid[x][y]== 2 && grid[x+1][y+1] == 2 && grid[x+2][y+2] == 2 && grid[x+3][y+3] == 2){
				//lose = true;
				game_logic->game_over = true;
				game_logic->score_two++;
			}
		}
	}
	return (game_logic->game_over);
}

//display the losing screen
void lose_screen(void){
	LCD_Clear(0, LCD_COLOR_RED);
	HAL_Delay(500);
	char title[] = "  YOU LOSE!  ";
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	uint16_t x_pos = 8;
	for(int i = 0; i < 13; i++){
		LCD_DisplayChar(x_pos, 30, title[i]);
		x_pos += 18;
	}
	HAL_Delay(500);
}

//check if game is a draw
bool check_draw(game_logic *game_logic, int grid[7][6]){
	uint8_t count_board = 0;
	//4 UP/DOWN in a column case
	for(int y = 0; y < 6; y++){
		for(int x = 0; x < 7; x++){
			if(grid[x][y] == 1 || grid[x][y] == 2 ){
				count_board += 1;
			}
		}
	}

	if (count_board == 42){
		//draw = true;
		game_logic->game_over = true;
	}

	return (game_logic->game_over);
}


//display the game is a draw screen
void draw_screen(void){
	LCD_Clear(0, LCD_COLOR_CYAN);
	HAL_Delay(500);
	char title[] = "    DRAW!    "; // 13
	LCD_SetTextColor(LCD_COLOR_MAGENTA);
	LCD_SetFont(&Font16x24);
	uint16_t x_pos = 8;
	for(int i = 0; i < 13; i++){
		LCD_DisplayChar(x_pos, 30, title[i]);
		x_pos += 18;
	}
	HAL_Delay(500);
}

//reset the game logic for a new game
void reset_game(game_logic *game_logic, int grid[7][6]){

	for(int y = 0; y < 6; y++){
		for(int x = 0; x < 7; x++){
			grid[x][y] = 0;
		}
	}
	game_logic->game_over = false;
	game_logic->time = 0;
	game_logic->player_one = true;
	game_logic->cursor_loc = 3;
	game_logic->button_pressed = false;
	game_logic->two_player_mode = false;
}


//function for lcd screen display character function
uint16_t mod_length(uint32_t number){
	uint16_t digits = 0;
	uint32_t check_num = number;
	if(number == 0) return 1;
	else{
		do{
			digits += 1;
			check_num /= 10;
		} while (check_num != 0);
		return digits;
	}
}


//display the final screen that shows game time, points, and button to start a new game
void last_screen(game_logic *game_logic){

	/////////////////////////////////////////////////////////////////////////////////////// TIME CLOCK
	//printf(" game started at: %d\n", (int)game_logic->time);

	uint32_t end_game_time = HAL_GetTick(); //returns ms
	//printf("game ended at: %d\n", (int)end_game_time);

	uint32_t round_time = end_game_time - game_logic->time;
	//printf("  total round: %d\n", (int)round_time);

	uint32_t round_seconds = round_time/1000;
	//printf("  in_seconds: %d\n", (int)round_seconds);

	///////////////////////////////////////////////////////////////////////////////////////

	char time[] = "Total game time (seconds): ";
	LCD_SetTextColor(LCD_COLOR_BLUE); LCD_SetFont(&Font12x12);
	uint16_t x_pos = 8;
	for(int i = 0; i < 27; i++){
		LCD_DisplayChar(x_pos, 80, time[i]);
		x_pos += 8;
	}

	///////////////////////////////converting the integer to array of chars in order to print with lcd_displaychar

	uint16_t array_length = mod_length(round_seconds);
	//printf("  check arr length: %d\n", (int)array_length);

	char seconds[9];     //need enough room for value (uint32_t) for a lot of milliseconds
	sprintf(seconds, "%d", (int)round_seconds);
	LCD_SetTextColor(LCD_COLOR_BLACK); LCD_SetFont(&Font16x24);
	x_pos = 110;
	for(int i = 0; i < array_length; i++){
		LCD_DisplayChar(x_pos, 100, seconds[i]);
		x_pos += 18;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	char player_one[] = "Player One rounds won: ";
	LCD_SetTextColor(LCD_COLOR_BLUE); LCD_SetFont(&Font12x12);
	x_pos = 8;
	for(int i = 0; i < 23; i++){
		LCD_DisplayChar(x_pos, 140, player_one[i]);
		x_pos += 8;
	}

	///////////////////////////////converting the integer to array of chars in order to print with lcd_displaychar

	array_length = mod_length(game_logic->score_one);
	char score_one[6];//need enough room for value (uint16_t) 65535 plus the terminating character at end
	sprintf(score_one, "%d", game_logic->score_one);

	LCD_SetTextColor(LCD_COLOR_BLACK); LCD_SetFont(&Font16x24);
	x_pos = 110;
	for(int i = 0; i < array_length; i++){
		LCD_DisplayChar(x_pos, 160, score_one[i]);
		x_pos += 18;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	char player_two[] = "Player Two rounds won: ";
	LCD_SetTextColor(LCD_COLOR_BLUE); LCD_SetFont(&Font12x12);
	x_pos = 8;
	for(int i = 0; i < 23; i++){
		LCD_DisplayChar(x_pos, 200, player_two[i]);
		x_pos += 8;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	array_length = mod_length(game_logic->score_two);
	char score_two[6];//need enough room for value (uint16_t) 65535 plus the terminating character at end
	sprintf(score_two, "%d", game_logic->score_two);

	LCD_SetTextColor(LCD_COLOR_BLACK); LCD_SetFont(&Font16x24);
	x_pos = 110;
	for(int i = 0; i < array_length; i++){
		LCD_DisplayChar(x_pos, 220, score_two[i]);
		x_pos += 18;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	//horizontal lines for drawing a button box
	for(uint16_t y = 275; y < 305; y++){
		for (uint16_t x = 20; x < 225; x++){
			LCD_Draw_Pixel(x, y, LCD_COLOR_BLUE);
		}
	}

	LCD_SetTextColor(LCD_COLOR_GREEN); LCD_SetFont(&Font16x24);
	char play_again[] = " Play again? ";
	x_pos = 8;
	for(int i = 0; i < 13; i++){
		LCD_DisplayChar(x_pos, 280, play_again[i]);
		x_pos += 18;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	bool game_select = false;
	uint8_t selection = 0;

	do {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			//printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			selection = StaticTouchData.x;
			game_select = true;
			HAL_Delay(100);
		}
	} while (game_select == false && selection == 0);   // MIGHT WANT TO CHANGE THIS, LITERALLY JUST CHECKING IF YOU CLICKED ANYWHERE ON THE SCREEN DOESNT MATTER

	/////////////////////////////////////////////////////////////////////////////////////// reset the game_logic->time

	HAL_Delay(500);
}

//variable for the button interrupt
static bool button_press = false;

//the button interrupt
void EXTI0_IRQHandler(void){
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	printf("BUTTON PRESSED!\n");
	button_press = true; //this writes to the static variable above, state flag for if button was pushed
	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

//last check for AI moves, validates that there are pieces underneath the specified slot, meaning its a valid move
//aka pieces wont float in space,
bool obey_gravity(int column, int row, int grid[7][6]){
	bool valid_move = true;
	printf(" checking gravity\n");
	if(row > 0){
		for(int y = 0; y <= row-1; y++){
			printf(" checking %d,%d\n", column, y);
			if(grid[column][y] == 0){
				valid_move = false;
				break;
			}
		}
	}
	return valid_move;
}


//if the AI sees a chance to win on its turn, it should take it
bool offense(game_logic *game_logic, int grid[7][6], int *x_coord, int *y_coord){
	bool found = false;

	//vertical wins
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 6; x++){
				if(grid[x][y]== 2 && grid[x][y+1] == 2 && grid[x][y+2] == 2 && grid[x][y+3] == 0){
					*x_coord = x;
					*y_coord = y+3;
					found = true;
				}
			}
		}
	}

	//horizontal wins
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 0 && grid[x+1][y] == 2 && grid[x+2][y] == 2 && grid[x+3][y] == 2){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 2 && grid[x+1][y] == 0 && grid[x+2][y] == 2 && grid[x+3][y] == 2){
					if(obey_gravity(x+1, y, grid) == true){
						*x_coord = x+1;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 2 && grid[x+1][y] == 2 && grid[x+2][y] == 0 && grid[x+3][y] == 2){
					if(obey_gravity(x+2, y, grid) == true){
						*x_coord = x+2;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 2 && grid[x+1][y] == 2 && grid[x+2][y] == 2 && grid[x+3][y] == 0){
					if(obey_gravity(x+3, y, grid) == true){
						*x_coord = x+3;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}

	//4 UP/RIGHT in a diagonal
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 0 && grid[x+1][y+1] == 2 && grid[x+2][y+2] == 2 && grid[x+3][y+3] == 2){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 2 && grid[x+1][y+1] == 0 && grid[x+2][y+2] == 2 && grid[x+3][y+3] == 2){
					if(obey_gravity(x+1, y+1, grid) == true){
						*x_coord = x+1;
						*y_coord = y+1;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 2 && grid[x+1][y+1] == 2 && grid[x+2][y+2] == 0 && grid[x+3][y+3] == 2){
					if(obey_gravity(x+2, y+2, grid) == true){
						*x_coord = x+2;
						*y_coord = y+2;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 2 && grid[x+1][y+1] == 2 && grid[x+2][y+2] == 2 && grid[x+3][y+3] == 0){
					if(obey_gravity(x+3, y+3, grid) == true){
						*x_coord = x+3;
						*y_coord = y+3;
						found = true;
					}
				}
			}
		}
	}

	//4 UP/LEFT in a diagonal wins
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 0 && grid[x-1][y+1] == 2 && grid[x-2][y+2] == 2 && grid[x-3][y+3] == 2){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 2 && grid[x-1][y+1] == 0 && grid[x-2][y+2] == 2 && grid[x-3][y+3] == 2){
					if(obey_gravity(x-1, y+1, grid) == true){
						*x_coord = x-1;
						*y_coord = y+1;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 2 && grid[x-1][y+1] == 2 && grid[x-2][y+2] == 0 && grid[x-3][y+3] == 2){
					if(obey_gravity(x-2, y+2, grid) == true){
						*x_coord = x-2;
						*y_coord = y+2;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 2 && grid[x-1][y+1] == 2 && grid[x-2][y+2] == 2 && grid[x-3][y+3] == 0){
					if(obey_gravity(x-3, y+3, grid) == true){
						*x_coord = x-3;
						*y_coord = y+3;
						found = true;
					}
				}
			}
		}
	}

	return found;
}



// if the AI doesnt find an offensive move, then it should block the players winning moves next
bool defense(game_logic *game_logic, int grid[7][6], int *x_coord, int *y_coord){
	bool found = false;

	//vertical wins
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 6; x++){
				if(grid[x][y]== 1 && grid[x][y+1] == 1 && grid[x][y+2] == 1 && grid[x][y+3] == 0){
					*x_coord = x;
					*y_coord = y+3;
					found = true;
				}
			}
		}
	}

	//horizontal wins
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 0 && grid[x+1][y] == 1 && grid[x+2][y] == 1 && grid[x+3][y] == 1){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 1 && grid[x+1][y] == 0 && grid[x+2][y] == 1 && grid[x+3][y] == 1){
					if(obey_gravity(x+1, y, grid) == true){
						*x_coord = x+1;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 1 && grid[x+1][y] == 1 && grid[x+2][y] == 0 && grid[x+3][y] == 1){
					if(obey_gravity(x+2, y, grid) == true){
						*x_coord = x+2;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 1 && grid[x+1][y] == 1 && grid[x+2][y] == 1 && grid[x+3][y] == 0){
					if(obey_gravity(x+3, y, grid) == true){
						*x_coord = x+3;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}

	//horizontal setups (if player has 2 connected, need to premptivly block one side
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 4; x++){
				if(grid[x][y]== 0 && grid[x+1][y] == 1 && grid[x+2][y] == 1){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 5; y++){
			for(int x = 0; x <= 4; x++){
				if(grid[x][y]== 1 && grid[x+1][y] == 1 && grid[x+2][y] == 0){
					if(obey_gravity(x+2, y, grid) == true){
						*x_coord = x+2;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}

	//UP/RIGHT diagonal setups //prempitvely block a diagnoal setup
	if(found == false){
		for(int y = 0; y <= 3; y++){
			for(int x = 0; x <= 4; x++){
				if(grid[x][y]== 1 && grid[x+1][y+1] == 0 && grid[x+2][y+2] == 1){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x+1;
						*y_coord = y+1;
						found = true;
					}
				}
			}
		}
	}

	//4 UP/RIGHT in a diagonal
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 0 && grid[x+1][y+1] == 1 && grid[x+2][y+2] == 1 && grid[x+3][y+3] == 1){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 1 && grid[x+1][y+1] == 0 && grid[x+2][y+2] == 1 && grid[x+3][y+3] == 1){
					if(obey_gravity(x+1, y+1, grid) == true){
						*x_coord = x+1;
						*y_coord = y+1;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 1 && grid[x+1][y+1] == 1 && grid[x+2][y+2] == 0 && grid[x+3][y+3] == 1){
					if(obey_gravity(x+2, y+2, grid) == true){
						*x_coord = x+2;
						*y_coord = y+2;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 0; x <= 3; x++){
				if(grid[x][y]== 1 && grid[x+1][y+1] == 1 && grid[x+2][y+2] == 1 && grid[x+3][y+3] == 0){
					if(obey_gravity(x+3, y+3, grid) == true){
						*x_coord = x+3;
						*y_coord = y+3;
						found = true;
					}
				}
			}
		}
	}

	//up/left diagonal setups // preemptively get in the way of these setups
	if(found == false){
		for(int y = 0; y <= 3; y++){
			for(int x = 2; x <= 6; x++){
				if(grid[x][y]== 1 && grid[x-1][y+1] == 0 && grid[x-2][y+2] == 1){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x-1;
						*y_coord = y+1;
						found = true;
					}
				}
			}
		}
	}

	//4 UP/LEFT in a diagonal wins
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 0 && grid[x-1][y+1] == 1 && grid[x-2][y+2] == 1 && grid[x-3][y+3] == 1){
					if(obey_gravity(x, y, grid) == true){
						*x_coord = x;
						*y_coord = y;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 1 && grid[x-1][y+1] == 0 && grid[x-2][y+2] == 1 && grid[x-3][y+3] == 1){
					if(obey_gravity(x-1, y+1, grid) == true){
						*x_coord = x-1;
						*y_coord = y+1;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 1 && grid[x-1][y+1] == 1 && grid[x-2][y+2] == 0 && grid[x-3][y+3] == 1){
					if(obey_gravity(x-2, y+2, grid) == true){
						*x_coord = x-2;
						*y_coord = y+2;
						found = true;
					}
				}
			}
		}
	}
	if(found == false){
		for(int y = 0; y <= 2; y++){
			for(int x = 3; x <= 6; x++){
				if(grid[x][y]== 1 && grid[x-1][y+1] == 1 && grid[x-2][y+2] == 1 && grid[x-3][y+3] == 0){
					if(obey_gravity(x-3, y+3, grid) == true){
						*x_coord = x-3;
						*y_coord = y+3;
						found = true;
					}
				}
			}
		}
	}

	return found;
}


//if there is no meaningful move to make, AI will place a piece somewhere, favoring middle spots first
uint8_t neutral(game_logic *game_logic, int grid[7][6]){

	int column = 3;
	uint8_t row = open_spot(column, grid);
	if (row < 6) return 3;

	column = 4;
	row = open_spot(column, grid);
	if (row < 6) return 4;

	column = 2;
	row = open_spot(column, grid);
	if (row < 6) return 2;

	column = 5;
	row = open_spot(column, grid);
	if (row < 6) return 5;

	column = 0;
	row = open_spot(column, grid);
	if (row < 0) return 0;

	//only choice left is column 6
	return 6;

}

// the main function for the AI to select a move to make
void computers_move(game_logic *game_logic, int grid[7][6], RNG_HandleTypeDef *hrng){

	//TESTING
	//uint8_t random_column = 1;

	int x_choice, y_choice;

	bool offense_move = offense(game_logic, grid, &x_choice, &y_choice);
	if (offense_move == true){
		printf(" offensive move %d,%d\n", x_choice, y_choice);
		grid[x_choice][y_choice] = 2;
	}


	bool defense_move = defense(game_logic, grid, &x_choice, &y_choice);
	if (offense_move == false && defense_move == true){
		printf(" defensive move %d,%d\n", x_choice, y_choice);
		grid[x_choice][y_choice] = 2;
	}

	int random_column;

	if(offense_move == false && defense_move == false){
		random_column = neutral(game_logic, grid);
		int row = open_spot(random_column, grid); // check if theres space in that column for a new piece

		if (row < 6){
			printf("    arbitrarily placing piece!\n");
			grid[random_column][row] = 2;
		}
	}

	swap_player(game_logic); //swap players after the piece is dropped
	draw_cursor(game_logic, grid);
	HAL_Delay(100);

	game_logic->button_pressed = true; //this will bypass move_cursor do/while loop to place a piece and update without needing to move cursor

	HAL_Delay(10);
}

//the main game loop is a do/while loop that continues as long as its not game over
void game_loop(game_logic *game_logic, int grid[7][6], RNG_HandleTypeDef *hrng){

	do{
		if(game_logic->two_player_mode == true || game_logic->player_one == true){  // its either player one's turn (both modes) or player two (two person mode) turn
			drop_game_piece(game_logic, grid, &button_press);
		}
		else if (game_logic->two_player_mode == false && game_logic->player_one == false){ // its one player mode and its the computers turn
			computers_move(game_logic, grid, hrng);
		}

		move_cursor(game_logic, grid);

		update_pieces(game_logic, grid);

		if(check_win(game_logic, grid) == true){
			HAL_Delay(500);
			win_screen();
		}

		else if(check_lose(game_logic, grid) == true){
			HAL_Delay(500);
			lose_screen();
		}

		else if(check_draw(game_logic, grid) == true){
			HAL_Delay(500);
			draw_screen();
		}

	} while (game_logic->game_over == false);

	HAL_Delay(10);
}
