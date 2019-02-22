/***************************** Include files *******************************/

#include <stdint.h>
#include <stdio.h>

#include "tm4c123gh6pm.h"
#include "src/emp_type.h"
#include "src/button.h"
#include "src/timepoint.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

TIMEPOINT * tp_global;

/************************   Interrupt Handlers   ***************************/

void ISR_SYSTICK(void)
{
    tp.tick(tp_global);
    // CLEAR INT FLAG
}

/*******************************   Main   **********************************/
int main(void)
{

    // init global timepoint instance
    tp_global = tp.new(SYSTEM);
    tp.set_systick(tp_global, 200, ms);
    tp.set_callback(tp_global, NULL);

    // init local timepoint instance
    TIMEPOINT * tp_local = tp.new(NORMAL);
    tp.set_value(tp_local, (INT64U[]){200, 0, 0, 2});

    // Test
    int diff = tp.delta(tp_local, tp_global, ms);
    printf("Test gives: %u.", diff);
}

