/***************************** Include files *******************************/

#include <stdint.h>

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
    tp_global = new_TIMEPOINT(200);

}

