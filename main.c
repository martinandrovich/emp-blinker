/***************************** Include files *******************************/

#include <stdint.h>
#include <stdio.h>

#include "tm4c123gh6pm.h"
#include "src/driver.h"
#include "src/emp_type.h"
#include "src/button.h"
#include "src/timepoint.h"
#include "src/LED.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

TIMEPOINT * tp_global;
LED * led_1;


/************************   Interrupt Handlers   ***************************/

void ISR_SYSTICK(void)
{
    tp.tick(tp_global);
}

void mofo_dannyboy(INT64U duration_ms)
{
	//printf("Daniel er en fucktard.");
	__enable_irq();
		led.toggle(led_1);
	__disable_irq();
}

/*******************************   Main   **********************************/
int main(void)
{

    // enable IRQ
	__enable_irq();

	// init global timepoint instance
    tp_global = tp.new(SYSTEM);
    tp.set_systick(tp_global, 1, ms);
    sys_tick_init(15999); //1 ms

    // create LED_new
    led_1 = led.new();
    led.set_color(led_1, (RGB){1, 0, 0});
    led.set_state(led_1, 1);

    // create button SW1
    BUTTON * btn_sw1 = btn.new(SW1);
    btn.set_callback(btn_sw1, &mofo_dannyboy);

    led.set_color(led_1, (RGB){0, 1, 0});

    for(;;)
    {
    	btn.controller(btn_sw1);
    }


    // init local timepoint instance
    //TIMEPOINT * tp_local = tp.new(NORMAL);
    //tp.set_value(tp_local, (INT64U[]){200, 0, 0, 2});

    // Test
    //int diff = tp.delta(tp_local, tp_global, ms);
    //printf("Test gives: %u.", diff);
}
