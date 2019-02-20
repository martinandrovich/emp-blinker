/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: timepoint.c
*
* PROJECT....: emp-blinker
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190220  MA    Module created.
*
****************************************************************************/

/***************************** Include files *******************************/

#include "timepoint.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void        TIMEPOINT_tick(TIMEPOINT * self)
/****************************************************************************
*   Input    : Pointer to TIMEPOINT instance.
*   Output   : -
*   Function : Increment TIMEPOINT with a systick unit.
****************************************************************************/
{
    ;
}

INT16U      TIMEPOINT_delta_ms(TIMEPOINT * tp1, TIMEPOINT * tp2)
/****************************************************************************
*   Input    : Pointer to self(tp1) and other(tp2) TIMEPOINT instance.
*   Output   : Unsigned integer
*   Function : Calculate absolute delta duration between two TIMEPOINTs
               given in ms.
****************************************************************************/
{
    ;
}

TIMEPOINT * new_TIMEPOINT(INT32U clock_freq, INT32U systick_dur)
/****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    // allocate object
    TIMEPOINT * tp = malloc(sizeof(TIMEPOINT));

    // define default values
    tp->hours           = 0;
    tp->minutes         = 0;
    tp->seconds         = 0;
    tp->milliseconds    = 0;
    tp->microseconds    = 0;
    tp->nanoseconds     = 0;

    tp->tick            = &TIMEPOINT_tick;
    tp->delta_ms        = &TIMEPOINT_delta_ms;

    return tp;
};

void del_TIMEPOINT(TIMEPOINT * tp )
/****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    free(tp);
};
