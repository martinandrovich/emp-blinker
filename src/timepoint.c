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

void TIMEPOINT_increment(TIMEPOINT * this, INT64U value, INT8U unit)
/****************************************************************************
*   Input    : this = pointer to TIMEPOINT instance
               value = ammount to increment (unit defined by index)
               index = index of time_array (0 = ns, 1 = us, 2 = ms ...)
*   Output   : -
*   Function : Recurisve increment of TIMEPOINT, until no overflow.
****************************************************************************/
{

    // CPP Version
    // https://gist.github.com/martinandrovich/17615f282af047c953e0d776b218e603

	this->time_array[unit] += value;

	INT16U remainder = this->time_array[unit] % 1000;
	INT16U quotient	= this->time_array[unit] / 1000;

	if (remainder != this->time_array[unit]) // OR quotient > 1 ????
	{
		this->time_array[unit] = remainder;
        TIMEPOINT_increment(this, quotient, unit + 1);
	}

    return;
}

void TIMEPOINT_tick(TIMEPOINT * this)
/****************************************************************************
*   Input    : Pointer to TIMEPOINT instance.
*   Output   : -
*   Function : Increment TIMEPOINT with a systick unit.
****************************************************************************/
{
    TIMEPOINT_increment(this, this->systick_dur_ns, ns);
    return;
}

INT64U TIMEPOINT_delta(TIMEPOINT * tp1, TIMEPOINT * tp2, INT8U unit)
/****************************************************************************
*   Input    : tp1, tp2 = Pointers to TIMEPOINT instances.
               unit = TIMEUNIT to be used
*   Output   : Unsigned integer
*   Function : Calculate absolute delta duration between two TIMEPOINTs
               given in unit defined by TIMEUNIT.
****************************************************************************/
{
    return 0;
}

INT16U TIMEPOINT_delta_ms(TIMEPOINT * tp1, TIMEPOINT * tp2)
/****************************************************************************
*   Input    : Pointer to this(tp1) and other(tp2) TIMEPOINT instance.
*   Output   : Unsigned integer
*   Function : Calculate absolute delta duration between two TIMEPOINTs
               given in ms.
****************************************************************************/
{
    return 0;
}

TIMEPOINT * new_TIMEPOINT(INT32U systick_dur_ns)
/****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    // allocate object
    TIMEPOINT * tp = malloc(sizeof(TIMEPOINT));

    // initialize time_array
    for (int i = 0; i < sizeof(tp->time_array)/sizeof(INT16U); i++)
    {
        tp->time_array[i] = 0;
    }

    // set increment value given in ns
    tp->systick_dur_ns  = systick_dur_ns;

    // link function pointers
    tp->tick            = &TIMEPOINT_tick;
    tp->delta           = &TIMEPOINT_delta;
    tp->delta_ms        = &TIMEPOINT_delta_ms;

    return tp;
};

void del_TIMEPOINT(TIMEPOINT * tp)
/****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    free(tp);
};
