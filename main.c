/*
 * main.c
 *
 *  Created on: Oct 7, 2022
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
extern u32 time;
extern u32 hrs;
extern u32 min;
extern u32 sec;

extern u8 select;
extern u8 run;
extern u8 timeout;

extern u8 pressed_key;


void main(void)
{
	LCD_voidInit();
	welcome_screen();
	KEYPAD_voidPinInit();

	// Display Timer
	update_time();


	while(1)
	{
		pressed_key = KEYPAD_u8GetPressedKey();

		// ========================================================
		// Edit Mode
		// ========================================================
		if(0 == run)
		{
			blink_selection();

			// Switch (Next)
			if('n' == pressed_key)
			{
				select++;

				if(select > 2)
				{
					select = 0;
				}
			}

			// Increment
			if('+' == pressed_key)
			{
				switch(select)
				{
				case 0: increment_hours(); break;
				case 1: increment_minutes(); break;
				case 2: increment_seconds(); break;
				}
			}

			// Decrement
			if('-' == pressed_key)
			{

				switch(select)
				{
				case 0: decrement_hours(); break;
				case 1: decrement_minutes(); break;
				case 2: decrement_seconds(); break;
				}
			}

			// Enable Run Mode (Start)
			if('s' == pressed_key)
			{
				run = 1;
				LCD_voidInit();
			}
		}

		// ========================================================
		// Run Mode
		// ========================================================
		if(1 == run)
		{
			// Time now
			time = hrs*60*60 + min*60 + sec;

			// Count down
			if(time > 0)
			{
				time--;
				hrs = time / (60*60);
				min = (time - hrs*60*60) / 60 ;
				sec = time - hrs*60*60 - min*60;

				update_time();
				_delay_ms(count_down_delay);
			}
			// Time out
			else
			{
				timeout = 1;
				timeout_blink();
			}

			// Stop
			if('o' == pressed_key && 0 == timeout)
			{
				run = 0;
				select = 0;
			}
		}


		// ========================================================
		// Reset
		// ========================================================
		if('r' == pressed_key)
		{
			reset_timer();
		}
	}
}









