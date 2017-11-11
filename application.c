/*
 * Raspberry Pi gpio-display
 *
 */
 
#include <math.h>
#include <stdio.h>
#include <wiringPi.h>

#include "main.h"
#include "application.h"

// configuration data for each Pin

struct pinConfig_t {
	char *name;
	int raspiPin;
	int wiringPiPin;
	int value;
} pinConfig[41];

void pin_c(int number, char *name, int raspiPin, int wiringPiPin)
{
	if ((number >= 0) && (number <= 40)) {
		pinConfig[number].name = name;
		pinConfig[number].raspiPin = raspiPin;
		pinConfig[number].wiringPiPin = wiringPiPin;
		pinConfig[number].value = 0;
	}
}

void application_init()
{
	wiringPiSetup();
	
	pin_c( 1, "3.3V POWER",		 1, -1);
	pin_c( 2, "5V POWER",	     2, -1);
	pin_c( 3, "BCM 2 (SDA)",	 3, -1);
	pin_c( 4, "5V POWER",		 4, -1);
	pin_c( 5, "BCM 3 (SCL)",	 5, -1);
	pin_c( 6, "GROUND",		     6, -1);
	pin_c( 7, "BCM 4 (GPCLK0)",	 7,  7);
	pin_c( 8, "BCM 14 (TDX)",	 8, -1);
	pin_c( 9, "GROUND",			 9, -1);
	pin_c(10, "BCM 15 (RXD)", 	10, -1);
	pin_c(11, "BCM 17",			11,  0);
	pin_c(12, "BCM 18",			12,  1);
	pin_c(13, "BCM 27",	        13,  2);
	pin_c(14, "GROUND",  		14, -1);
	pin_c(15, "BCM 22",			15,  3);
	pin_c(16, "BCM 23",			16,  4);
	pin_c(17, "3.3V POWER",		17, -1);
	pin_c(18, "BCM 24"	,		18,  5);
	pin_c(19, "BCM 10 (MOSI)",	19, -1);
	pin_c(20, "GROUND",			20, -1);
	pin_c(21, "BCM 9 (MISO)",	21, -1);
	pin_c(22, "BCM 25",			22,  6);
	pin_c(23, "BM 11 (SCLK)",	23, -1);
	pin_c(24, "BCM 8 (CE0)",	24, -1);
	pin_c(25, "GROUND",			25, -1);
	pin_c(26, "BCM 7 (CE1)",	26, -1);
	pin_c(27, "BCM 0 (ID_SD)",	27, -1);
	pin_c(28, "BCM 1 (ID_SC)",	28, -1);
	pin_c(29, "BCM 5",			29, 21);
	pin_c(30, "GROUND",			30, -1);
	pin_c(31, "BCM 6",			31, 22);
	pin_c(32, "BCM 12 (PWM0)",	32, 26);
	pin_c(33, "BCM 13 (PWM1)",	33, 23);
	pin_c(34, "GROUND",			34, -1);
	pin_c(35, "BCM 19 (MISO)",	35, 24);
	pin_c(36, "BCM 16",			36, 27);
	pin_c(37, "BCM 26",			37, 25);
	pin_c(38, "BCM 20 (MOSI)",	38, 28);
	pin_c(39, "GROUND",			39, -1);
	pin_c(40, "BM 21 (SCLK)",	40, 29);	
}

int application_on_timer_event()
// if TIMER_INTERVAL in application.h is larger than zero, this function
// is called every TIMER-INTERVAL milliseconds
// if the function returns 1, the window is redrawn by calling applicatin_draw
{
	//  printf("application_on_timer_event called\n");
	int redraw = 0;
	int pin, wiringPiPin, newValue;
	
	for (pin = 1; pin <= 40; pin++) {
		wiringPiPin = pinConfig[pin].wiringPiPin;
		if (wiringPiPin >= 0) {
			newValue = digitalRead(wiringPiPin);
			// printf("pin %d, wiringPi = %d, value = %d\n", pin, wiringPiPin, newValue);
			if(newValue != pinConfig[pin].value) {
				// printf("pin %d change, new value = %d\n", pin, newValue);
				redraw = 1;
				pinConfig[pin].value = newValue;
			}
		}
	}
	
	return redraw;
}
 
int application_clicked(int button, int x, int y)
// is called if a mouse button is clicked in the window
// button = 1: means left mouse button; button = 3 means right mouse button
// x and y are the coordinates
// if the function returns 1, the window is redrawn by calling applicatin_draw
{
	printf("application_clicked called, button %d, x = %d, y= %d\n", button, x, y);	
	return 1;
}

void application_quit()
// is called if the main window is called bevore the application exits
// put any code here which needs to be called on exit
{
	// printf("application quit called\n");
}

void application_draw(cairo_t *cr, int width, int height)
// draw onto the main window using cairo
// width is the actual width of the main window
// height is the actual height of the main window

#define FIELD_SIZE		20
#define CIRCLE_RADIUS	6

{	
	int i,x, y, pin, xNum, xLabel, xWiringPi;
	char str[16];
	
	// printf("application_draw called\n");
	
	// set the backgrond color
	cairo_rectangle(cr, 0.0, 0.0, width, height);
	cairo_set_source_rgb(cr, 0.93, 0.93, 0.93);
	cairo_fill(cr);
	
	cairo_set_font_size(cr, 11);
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	cairo_set_line_width (cr, 1);
	cairo_rectangle (cr, width / 2 - (9 * FIELD_SIZE),
		12, 18 * FIELD_SIZE, 22 * FIELD_SIZE);
		
	y = 26;
	x = (width / 2) - ((3 * FIELD_SIZE) / 2);
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "pi-gpio");
	
	x = (width / 2) - ((18 * FIELD_SIZE) / 2) + 6;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "wirPi");

	x = (width / 2) - ((11 * FIELD_SIZE) / 2) - 6;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "pin name");
	
	x = (width / 2) + ((7 * FIELD_SIZE) / 2) - 6;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "pin name");
	
	x = (width / 2) + ((14 * FIELD_SIZE) / 2) + 4;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, "wirPi");
		
	cairo_move_to(cr, width / 2 - (9 * FIELD_SIZE), 12 + FIELD_SIZE);
	cairo_line_to(cr, width / 2 + (9 * FIELD_SIZE), 12 + FIELD_SIZE);
	
	cairo_move_to(cr, width / 2 - (7 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 - (7 * FIELD_SIZE), 12 + (22 * FIELD_SIZE));
	
	cairo_move_to(cr, width / 2 - (2 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 - (2 * FIELD_SIZE), 12 + (22 * FIELD_SIZE));
	
	cairo_move_to(cr, width / 2 + (2 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 + (2 * FIELD_SIZE), 12 + (22 * FIELD_SIZE));
	
	cairo_move_to(cr, width / 2 + (7 * FIELD_SIZE), 12);
	cairo_line_to(cr, width / 2 + (7 * FIELD_SIZE), 12 + (22 * FIELD_SIZE));
		
	for (pin = 1; pin <= 40; pin++) {
		
		if (pin % 2) {
			x = (width / 2) - (FIELD_SIZE / 2);
			xNum = x - FIELD_SIZE - 6;
			xLabel = x - (6 * FIELD_SIZE) - 6;
			xWiringPi = (width / 2) - ((18 * FIELD_SIZE) / 2) + 12;
		}
		else {
			x = (width / 2) + (FIELD_SIZE / 2);
			xNum = x + FIELD_SIZE - 8;
			xLabel = x + (2 * FIELD_SIZE) - 2;
			xWiringPi = (width / 2) + ((14 * FIELD_SIZE) / 2) + 12;
		}
		
		y = FIELD_SIZE + 12 + (((pin + 1) / 2) * FIELD_SIZE);
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_move_to(cr, xNum, y + 4);
		sprintf(str, "%2d", pin);
		cairo_show_text(cr, str);
		
		cairo_stroke (cr);
		
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);    // black
		cairo_move_to(cr, x + CIRCLE_RADIUS, y);
		cairo_arc(cr, x, y, CIRCLE_RADIUS, 0, 2 * M_PI);
		if (pinConfig[pin].value) {
			cairo_stroke_preserve(cr);
			cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);    // fill red
			cairo_fill(cr);
		}
		else if (pinConfig[pin].wiringPiPin >= 0) {
			cairo_stroke_preserve(cr);
			cairo_set_source_rgb(cr, 0.5, 0.0, 0.0);    // fill dark red
			cairo_fill(cr);
		}
		cairo_stroke (cr);
		
		
		if (pinConfig[pin].wiringPiPin >= 0)
			cairo_set_source_rgb(cr, 0.0, 0.5, 0.0);    // dark green
		else
			cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);    // black
		
		cairo_move_to(cr, xLabel, y + 4);
		cairo_show_text(cr, pinConfig[pin].name);
		if (pinConfig[pin].wiringPiPin >= 0) {
			sprintf(str, "%2d", pinConfig[pin].wiringPiPin);
			cairo_move_to(cr, xWiringPi, y + 4);
		    cairo_show_text(cr, str);
		}
	}
	cairo_stroke (cr);

}
