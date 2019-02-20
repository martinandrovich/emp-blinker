/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: timepoint.h
*
* PROJECT....: emp-blinker
*
* DESCRIPTION: A timepoint object, used to track time.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190220  MA    Module created.
*
****************************************************************************/

#pragma once

/***************************** Include files *******************************/

#include <stdlib.h>
#include "emp_type.h"

/*****************************    Defines    *******************************/

typedef struct TIMEPOINT TIMEPOINT;

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

extern  TIMEPOINT * new_TIMEPOINT(INT32U clock_freq, INT32U systick_dur);
/****************************************************************************
*   Input    : clock_freq   = Clock frequency of the MIC given in Hz.
*              systick_dur  = Duration of a systick timer tick given in ns.
*   Output   : Pointer to a new TIMEPOINT instance.
*   Function : Constructor of a TIMEPOINT instance.
****************************************************************************/

extern  void        del_TIMEPOINT(TIMEPOINT * tp );
/****************************************************************************
*   Input    : Pointer to a TIMEPOINT instance.
*   Output   : -
*   Function : Destructor of a TIMEPOINT instance.
****************************************************************************/

/*****************************    Constructs   *****************************/

struct TIMEPOINT
{
    /** Members ************************************************************/
    INT32U unit_ns;

    INT16U hours;
    INT16U minutes;
    INT16U seconds;
    INT16U milliseconds;
    INT16U microseconds;
    INT16U nanoseconds;

    /** Methods ************************************************************/
    void(*tick)(TIMEPOINT * self);
    INTU16(*delta_ms)(TIMEPOINT * tp1, TIMEPOINT * tp2);
};

/****************************** End Of Module ******************************/
