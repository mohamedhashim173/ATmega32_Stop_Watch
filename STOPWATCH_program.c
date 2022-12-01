/*
 * STOPWATCH_program.c
 *
 *  Created on: Oct 12, 2022
 *      Author: MSAEED99
 */


// AVR libraries
#include <util/delay.h>

// Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"

// HAL
#include "LCD_interface.h"
#include "KEYPAD_interface.h"

#include "STOPWATCH_config.h"
#include "STOPWATCH_interface.h"

// Global variables
u32 time = 0;
u32 hrs = 0;
u32 min = 0;
u32 sec = 0;

u8 select = 0;
u8 run = 0;
u8 timeout = 0;

u8 pressed_key;

u32 blink_counter = 0;


void welcome_screen(void)
{
	LCD_voidSendString("Mohamed Hashim's");
	LCD_voidPositionSet(1, 0);
	LCD_voidSendString("   Stop Watch   ");

	_delay_ms(welcome_screen_delay);

	LCD_voidInit();
}


void draw_hours(void)
{
	LCD_voidPositionSet(0, 2);

	// Print 2 digits
	if(hrs < 10)
	{
		LCD_voidSendCharacter('0');
	}

	// Send number
	LCD_voidWriteNum(hrs);
	LCD_voidSendString("h:");
}


void draw_minutes(void)
{
	LCD_voidPositionSet(0, 6);

	// Print 2 digits
	if(min < 10)
	{
		LCD_voidSendCharacter('0');
	}

	// Send number
	LCD_voidWriteNum(min);
	LCD_voidSendString("m:");
}


void draw_seconds(void)
{
	LCD_voidPositionSet(0, 10);

	// Print 2 digits
	if(sec < 10)
	{
		LCD_voidSendCharacter('0');
	}

	// Send number
	LCD_voidWriteNum(sec);
	LCD_voidSendString("s");
}


void increment_hours(void)
{
	// Loop over hrs counter
	if(hrs_max == hrs)
	{
		hrs = 0;
	}
	else
	{
		hrs++;
	}

	draw_hours();
}


void decrement_hours(void)
{
	// Loop over hrs counter
	if(0 == hrs)
	{
		hrs = hrs_max;
	}
	else
	{
		hrs--;
	}

	draw_hours();
}


void increment_minutes(void)
{
	// Loop over min counter
	if(min_max == min)
	{
		min = 0;
	}
	else
	{
		min++;
	}

	draw_minutes();
}


void decrement_minutes(void)
{
	// Loop over min counter
	if(0 == min)
	{
		min = min_max;
	}
	else
	{
		min--;
	}

	draw_minutes();
}


void increment_seconds(void)
{
	// Loop over sec counter
	if(sec_max == sec)
	{
		sec = 0;
	}
	else
	{
		sec++;
	}

	draw_seconds();
}


void decrement_seconds(void)
{
	// Loop over sec counter
	if(0 == sec)
	{
		sec = sec_max;
	}
	else
	{
		sec--;
	}

	draw_seconds();
}


void update_time(void)
{
	draw_hours();
	draw_minutes();
	draw_seconds();
}


void blink_selection(void)
{

	LCD_voidPositionSet(1, 0);
	LCD_voidSendString("   Set Timer    ");

	// ON
	if(blink_counter < blink_counter_max / 2)
	{
		switch(select)
		{
		case 0: draw_hours(); break;
		case 1: draw_minutes(); break;
		case 2: draw_seconds(); break;
		}
	}
	// OFF
	else
	{
		switch(select)
		{
		case 0:
			draw_minutes();
			draw_seconds();

			LCD_voidPositionSet(0, 2);

			LCD_voidSendString("   ");
			break;

		case 1:
			draw_hours();
			draw_seconds();

			LCD_voidPositionSet(0, 6);
			LCD_voidSendString("   ");
			break;

		case 2:
			draw_hours();
			draw_minutes();

			LCD_voidPositionSet(0, 10);
			LCD_voidSendString("   ");
			break;
		}
	}

	// Reset loop counter
	if(blink_counter > blink_counter_max)
	{
		blink_counter = 0;
	}

	blink_counter++;
}

void timeout_blink(void)
{
	// Timeout
	LCD_voidPositionSet(1, 0);
	LCD_voidSendString("    Time Out    ");

	// Buzzer & LED Port output
	DIO_voidSetPinDirection(STOP_WATCH_BUZZER_PORT, STOP_WATCH_BUZZER_PIN, DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(STOP_WATCH_LED_PORT, STOP_WATCH_LED_PIN, DIO_u8PIN_OUTPUT);

	// ON
	if(blink_counter < blink_counter_max / 3)
	{
		// Buzzer & LED ON
		DIO_voidSetPinValue(STOP_WATCH_BUZZER_PORT, STOP_WATCH_BUZZER_PIN, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STOP_WATCH_LED_PORT, STOP_WATCH_LED_PIN, DIO_u8PIN_HIGH);

		//Blink ON
		LCD_voidPositionSet(0, 0);
		update_time();
	}

	// OFF
	else
	{
		// Buzzer & LED OFF
		DIO_voidSetPinValue(STOP_WATCH_BUZZER_PORT, STOP_WATCH_BUZZER_PIN, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STOP_WATCH_LED_PORT, STOP_WATCH_LED_PIN, DIO_u8PIN_LOW);

		// Blink OFF
		LCD_voidPositionSet(0, 0);
		LCD_voidSendString("                ");
	}

	// Reset loop counter
	if(blink_counter > blink_counter_max / 2)
	{
		blink_counter = 0;
	}

	blink_counter++;
}



void reset_timer(void)
{
	run = 0;
	timeout = 0;
	select = 0;

	time = 0;
	hrs = 0;
	min = 0;
	sec = 0;

	// Buzzer & LED OFF
	blink_counter = 0;
	DIO_voidSetPinValue(STOP_WATCH_BUZZER_PORT, STOP_WATCH_BUZZER_PIN, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STOP_WATCH_LED_PORT, STOP_WATCH_LED_PIN, DIO_u8PIN_LOW);

	LCD_voidInit();
	update_time();
}

























