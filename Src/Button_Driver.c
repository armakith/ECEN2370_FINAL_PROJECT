/*
 * Button_Driver.c
 *
 *  Created on: Apr 25, 2025
 *      Author: mgalchemy
 */

#include "Button_Driver.h"



void button_init(void){

	GPIO_InitTypeDef button_config;
	button_config.Pin = BUTTON_PIN;
	button_config.Mode = GPIO_MODE_IT_RISING;
	button_config.Speed = GPIO_SPEED_FREQ_HIGH;
	button_config.Pull = GPIO_NOPULL;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(USER_BUTTON_PORT, &button_config);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}


bool button_state(void){

	if(HAL_GPIO_ReadPin(USER_BUTTON_PORT, USER_BUTTON_PIN) == USER_BUTTON_PRESSED){
		return true;
	}
	else{
		return false;
	}
}


