/*
 * STOPWATCH_interface.h
 *
 *  Created on: Oct 12, 2022
 *      Author: MSAEED99
 */

#ifndef STOPWATCH_INTERFACE_H_
#define STOPWATCH_INTERFACE_H_


void welcome_screen(void);

void draw_hours(void);
void draw_minutes(void);
void draw_seconds(void);

void increment_hours(void);
void decrement_hours(void);

void increment_minutes(void);
void decrement_minutes(void);

void increment_seconds(void);
void decrement_seconds(void);

void blink_selection(void);
void update_time(void);

void timeout_blink(void);

void reset_timer(void);


#endif /* STOPWATCH_INTERFACE_H_ */
