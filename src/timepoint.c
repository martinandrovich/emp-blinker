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

/************************  Function declarations ***************************/

void 	TIMEPOINT_increment(TIMEPOINT * this, INT64U value, INT8U unit);
void 	TIMEPOINT_tick(TIMEPOINT * this);
void 	TIMEPOINT_set_callback(TIMEPOINT * this, void(*callback)());
void 	TIMEPOINT_set_systick(TIMEPOINT * this, INT64U systick_dur_ns);
void 	TIMEPOINT_copy(TIMEPOINT * this, TIMEPOINT * other);
INT64U 	TIMEPOINT_delta(TIMEPOINT * this, TIMEPOINT * other, INT8U unit);
INT16U 	TIMEPOINT_delta_ms(TIMEPOINT * this, TIMEPOINT * other);

/*****************************   Functions   *******************************/

void TIMEPOINT_increment(TIMEPOINT * this, INT64U value, INT8U unit)
/****************************************************************************
*   Input    : this = pointer to TIMEPOINT instance.
               value = ammount to increment (unit defined by index).
               unit = index of time_array (0 = ns, 1 = us, 2 = ms ...).
*   Function : Recurisve increment of TIMEPOINT, until no overflow.
****************************************************************************/
{
    // CPP Version
    // https://gist.github.com/martinandrovich/17615f282af047c953e0d776b218e603

	this->time_array[unit] += value;

	INT64U remainder = this->time_array[unit] % 1000;
	INT64U quotient	= this->time_array[unit] / 1000;

	if (remainder != this->time_array[unit]) // OR quotient > 1 ????
	{
		this->time_array[unit] = remainder;
        TIMEPOINT_increment(this, quotient, unit + 1);
	}
}

void TIMEPOINT_tick(TIMEPOINT * this)
/****************************************************************************
*   Input    : Pointer to TIMEPOINT instance.
*   Function : Increment TIMEPOINT with a systick unit.
****************************************************************************/
{
	// increment time_array
	TIMEPOINT_increment(this, this->systick_dur_ns, ns);

	// call callback if defined
	if (this->callback != NULL)
	{
		this->callback();
	}
}

void TIMEPOINT_set_callback(TIMEPOINT * this, void(*callback)())
/****************************************************************************
*   Input    : this: Pointer to TIMEPOINT instance.
			   callback: Pointer to void function.
*   Function : Set the callback of a TIMEPOINT instance.
****************************************************************************/
{
	this->callback = callback;
}

void TIMEPOINT_set_systick(TIMEPOINT * this, INT64U systick_dur_ns)
/****************************************************************************
*   Input    : this: Pointer to TIMEPOINT instance.
			   systick_dur_ns: Duration of systick tick in ns.
*   Function : Set the systick_dur_ns of a TIMEPOINT instance.
****************************************************************************/
{
	this->systick_dur_ns = systick_dur_ns;
}

void TIMEPOINT_copy(TIMEPOINT * this, TIMEPOINT * other)
/****************************************************************************
*   Input    : this, other = Pointers to TIMEPOINT instances.
*   Function : Copy time_array from other TIMEPOINT to this TIMEPOINT.
****************************************************************************/
{
	// copy time_array
	for (int i = 0; i < TIME_ARRAY_SIZE; i++)
	{
		this->time_array[i] = other->time_array[i];
	}
}

INT64U TIMEPOINT_delta(TIMEPOINT * this, TIMEPOINT * other, INT8U unit)
/****************************************************************************
*   Input    : this, other = Pointers to TIMEPOINT instances.
               unit = TIMEUNIT to be used.
*   Output   : Unsigned integer.
*   Function : Calculate absolute delta duration between two TIMEPOINTs
               given in unit defined by TIMEUNIT.
****************************************************************************/
{
    return 0;
}

INT16U TIMEPOINT_delta_ms(TIMEPOINT * this, TIMEPOINT * other)
/****************************************************************************
*   Input    : this, other = Pointers to TIMEPOINT instances.
*   Output   : Unsigned integer.
*   Function : Calculate absolute delta duration between two TIMEPOINTs
               given in ms.
****************************************************************************/
{
    return 0;
}

/***********************   Constructive Functions   ************************/

TIMEPOINT * new_TIMEPOINT(INT64U systick_dur_ns)
/****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    // allocate object
    TIMEPOINT * tp = malloc(sizeof(TIMEPOINT));

    // initialize time_array
    //for (int i = 0; i < sizeof(tp->time_array)/sizeof(INT64U); i++)
    for (int i = 0; i < TIME_ARRAY_SIZE; i++)
    {
        tp->time_array[i] = 0;
    }

	// initialize callback to nullptr
	tp->callback = NULL;

    // set increment value given in ns
    tp->systick_dur_ns  = systick_dur_ns;
	//tp->type			= SYSTEM;

    // link function pointers
    tp->tick            = &TIMEPOINT_tick;
	tp->set_callback	= &TIMEPOINT_set_callback;
	tp->set_systick		= &TIMEPOINT_set_systick;
	tp->copy			= &TIMEPOINT_copy;
    tp->delta           = &TIMEPOINT_delta;
    tp->delta_ms        = &TIMEPOINT_delta_ms;

	// return pointer to instance
    return tp;
}

void del_TIMEPOINT(TIMEPOINT * this)
/****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    free(this);
}
