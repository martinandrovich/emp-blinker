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

typedef struct  TIMEPOINT TIMEPOINT;
typedef enum    TIMEUNIT TIMEUNIT;
typedef enum    TP_TYPE TP_TYPE;

// done instead of having to define e.g. void func(struct TIMEPOINT tp, )..

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

#define TIME_ARRAY_SIZE 4

/*************************  Function interfaces ****************************/

extern  TIMEPOINT * new_TIMEPOINT(TP_TYPE type);
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

extern  void        TIMEPOINT_copy(TIMEPOINT * des, TIMEPOINT * src);
/****************************************************************************
*   Input    : des, src = Pointers to TIMEPOINT instances.
*   Function : Copy time_array from 'src' TIMEPOINT to 'des' TIMEPOINT.
****************************************************************************/

extern  INT64U      TIMEPOINT_delta(TIMEPOINT * tp1, TIMEPOINT * tp2, TIMEUNIT unit);
/****************************************************************************
*   Input    : tp1, tp2 = Pointers to TIMEPOINT instances.
               unit = TIMEUNIT to be used.
*   Output   : Unsigned integer.
*   Function : Calculate absolute delta duration between two TIMEPOINTs
               given in unit defined by TIMEUNIT.
****************************************************************************/

/*****************************    Constructs   *****************************/

enum TP_TYPE
{
    NORMAL,
    SYSTEM
};

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
    INT64U  time_array[TIME_ARRAY_SIZE]; // indexes 0: ns, 1: us, 2: ms, 3: s
    INT64U  systick_dur_ns;

    TP_TYPE type;
    FUNPTR  callback; //void(*callback)();

    /** Methods ************************************************************/
    void    (*tick)(TIMEPOINT * this);
    void    (*set_callback)(TIMEPOINT * this, void(*callback)());
    void    (*set_systick)(TIMEPOINT * this, INT64U duration, TIMEUNIT unit);
    INT64U  (*get_value)(TIMEPOINT * this, TIMEUNIT unit);
    // void(*copy)(TIMEPOINT * this, TIMEPOINT * other);
    // INT64U(*delta)(TIMEPOINT * this, TIMEPOINT * other, TIMEUNIT unit);
    // INT16U(*delta_ms)(TIMEPOINT * this, TIMEPOINT * other);
};

/****************************** End Of Module ******************************/
