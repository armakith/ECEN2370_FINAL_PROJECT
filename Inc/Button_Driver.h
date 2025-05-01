/*
 * Button_Driver.h
 *
 *  Created on: Apr 25, 2025
 *      Author: mgalchemy
 */

#ifndef INC_BUTTON_DRIVER_H_
#define INC_BUTTON_DRIVER_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"
//button = PA0

#define BUTTON_PIN GPIO_PIN_0
#define USER_BUTTON_PORT (GPIOA)
#define USER_BUTTON_PIN 0
#define USER_BUTTON_PRESSED 1
#define USER_BUTTON_NOT_PRESSED 0



void button_init(void);

bool button_state(void);



#endif /* INC_BUTTON_DRIVER_H_ */
