/*
 * STOPWATCH_config.h
 *
 *  Created on: Oct 12, 2022
 *      Author: MSAEED99
 */

#ifndef STOPWATCH_CONFIG_H_
#define STOPWATCH_CONFIG_H_


// Macros
#define welcome_screen_delay	1500
#define	count_down_delay		100
#define blink_counter_max		15


// Buzzer Port
#define STOP_WATCH_BUZZER_PORT	DIO_u8PORTB
#define STOP_WATCH_LED_PORT		DIO_u8PORTB
#define STOP_WATCH_BUZZER_PIN	DIO_u8PIN0
#define STOP_WATCH_LED_PIN		DIO_u8PIN1


// Stop Watch maximum values
#define hrs_max			23
#define min_max			59
#define sec_max			59



#endif /* STOPWATCH_CONFIG_H_ */
