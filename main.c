/***************************** Include files *******************************/

#include <stdint.h>
#include <stdio.h>

#include "tm4c123gh6pm.h"
#include "src/driver.h"
#include "src/emp_type.h"
#include "src/button.h"
#include "src/timepoint.h"
#include "src/LED.h"
#include "src/LED_controller.h"

/*****************************    Defines    *******************************/

#define SYSTICK_ms		1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

TIMEPOINT * tp_global;
LED * led_1;
LED_CONTROLLER * ledc;

/************************   Interrupt Handlers   ***************************/

void ISR_SYSTICK(void)
{
    tp.tick(tp_global);
}

void mofo_dannyboy(INT32S duration_ms)
{
	//printf("Daniel er en fucktard.");
	__enable_irq();

	if(duration_ms == -1)
	{
		//led.set_color(led_1, (RGB){0, 0, 1});
		led.invert_colors(led_1);
	}
	else
	{
		led.toggle(led_1);
	}

	__disable_irq();
}

void mofo_pattyboy(INT32S duration_ms)
{
	led_ctrl.callback(ledc, duration_ms);
}

/*******************************   Main   **********************************/
int main(void)
{

    // enable IRQ
	__enable_irq();

	// init global timepoint instance
    tp_global = tp.new(SYSTEM);
    tp.set_systick(tp_global, SYSTICK_ms, ms);

    sys_tick_init(SYSTICK_ms);

    // create LED_new
    led_1 = led.new();
    led.set_color(led_1, (RGB){1, 0, 0});
    led.set_state(led_1, 1);

    led.set_color(led_1, (RGB){0, 1, 0});

    // LED controller
    ledc = led_ctrl.new();

    // create button SW1
	BUTTON * btn_sw1 = btn.new(SW1);
	btn.set_callback(btn_sw1, mofo_pattyboy);

    for(;;)
    {
    	btn.controller(btn_sw1);
    	led_ctrl.controller(ledc, led_1);
    }

}
