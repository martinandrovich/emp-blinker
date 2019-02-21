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

extern  TIMEPOINT * new_TIMEPOINT(INT64U systick_dur_ns);
/****************************************************************************
*   Input    : systick_dur_ns  = Duration of a SysTimer tick given in ns.
*   Output   : Pointer to a new TIMEPOINT instance.
*   Function : Constructor of a TIMEPOINT instance.
****************************************************************************/

extern  void        del_TIMEPOINT(TIMEPOINT * this);
/****************************************************************************
*   Input    : Pointer to a TIMEPOINT instance.
*   Function : Destructor of a TIMEPOINT instance.
****************************************************************************/

/*****************************    Constructs   *****************************/

enum TIMEUNIT
{
    ns,     // 0 = nanoseconds
    us,     // 1 = microseconds
    ms,     // 2 = milliseconds
    s       // 3 = seconds
};

struct TIMEPOINT
{
    /** Members ************************************************************/
    INT64U time_array[4];   // indexes 0: ns, 1: us, 2: ms, 3: s
    INT64U systick_dur_ns;
    FUNPTR callback; //void(*callback)();

    /** Methods ************************************************************/
    void(*tick)(TIMEPOINT * this);
    void(*copy)(TIMEPOINT * this, TIMEPOINT * other);
    void(*set_callback)(TIMEPOINT * this, void(*callback)());
    INT64U(*delta)(TIMEPOINT * this, TIMEPOINT * other, INT8U unit);
    INT16U(*delta_ms)(TIMEPOINT * this, TIMEPOINT * other);
};

/****************************** End Of Module ******************************/
