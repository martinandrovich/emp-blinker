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
    tp_global->tick(tp_global);
    // CLEAR INT FLAG
}

/*******************************   Main   **********************************/
int main(void)
{

    // Initialize global timepoint instance
    tp_global = new_TIMEPOINT(SYSTEM);
    tp_global->set_systick(tp_global, 200, ms);

    // Initialize local timepoint instance
    TIMEPOINT * tp_local = new_TIMEPOINT(NORMAL);

    //tp_local->set_systick(tp_local, 200, ms); // should give runtime error

    // Test
    TIMEPOINT_copy(tp_local, tp_global);
    int delta_value = TIMEPOINT_delta(tp_local, tp_global, ms);

    printf("Test gives: %u.", delta_value);
}

