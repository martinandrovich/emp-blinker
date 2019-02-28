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

#define SYSTICK_DUR_MS		1
#define LAMBDA(c_) ({ c_ _;}) // should be moved to driver

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

TIMEPOINT * tp_global;

/************************   Interrupt Handlers   ***************************/

void ISR_SYSTICK(void)
{
    tp.tick(tp_global);
}

/*******************************   Main   **********************************/

int main(void)
{

	/*****************************     Init     ****************************/

    // enable IRQ
	__enable_irq();

	// init global TIMEPOINT instance
    tp_global = tp.new(SYSTEM);
    tp.set_systick(tp_global, SYSTICK_DUR_MS, ms);

    // init SYSTICK
    sys_tick_init(SYSTICK_DUR_MS);

    // init LED instance
    LED * led_1 = led.new();

    led.set_color(led_1, (RGB){1, 0, 0});
    led.set_state(led_1, 1);

    // init LED_CONTROLLER instance
    LED_CONTROLLER* ledc_1 = led_ctrl.new();

    // init BUTTON instance (SW1)
    BUTTON * btn_sw1 = btn.new(SW1);

    // init callbacks (lambdas)

    // method #1
    //void sw_1_callback (INT32S duration_ms){ led_ctrl.callback(ledc_1, duration_ms); }
	//btn.set_callback(btn_sw1, sw_1_callback);

    // method #2
	// btn.set_callback(btn_sw1,
	// 	({
	// 	 void sw_1_callback (INT32S duration_ms){ led_ctrl.callback(ledc_1, duration_ms); }
	// 	 sw_1_callback;
    // 	})
	// );

	// method #3 (same as 2, but using macro)
	btn.set_callback(btn_sw1, LAMBDA(void _(INT32S duration_ms)
		{
			led_ctrl.callback(ledc_1, duration_ms);
		}
	));

	/****************************    Main Loop      *************************/

    for(;;)
    {
    	btn.controller(btn_sw1);
    	led_ctrl.controller(ledc_1, led_1);
    }

    /****************************     Cleanup     **************************/

    // disable IRQ
    __disable_irq();

    // free memory
    tp.del(tp_global);
    led.del(led_1);
    btn.del(btn_sw1);
    led_ctrl.del(ledc_1);

    // exit
    return 0;
}
