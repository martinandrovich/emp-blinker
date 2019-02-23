/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: timepoint.h
*
* PROJECT....: emp-blinker
*
* DESCRIPTION: A TIMEPOINT object, used to track time.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* ---------------------------------------------------------------------------
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

/*************************  Function Interfaces ****************************/

/*************************    Class Functions    ***************************/

extern struct TIMEPOINT_CLASS
{
	// Constructor & Destructor
	TIMEPOINT*	(* const new)(TP_TYPE type);
	void		(* const del)(TIMEPOINT * this);

	// Members
	BOOLEAN*	int_status;

	// Methods
	void		(* const tick)(TIMEPOINT * this);

	void		(* const set_callback)(TIMEPOINT * this, void(*callback)());
	void		(* const set_systick)(TIMEPOINT * this, INT64U duration, TIMEUNIT unit);
	void		(* const set_intptr)(BOOLEAN* addr);

	void		(* const set_value)(TIMEPOINT * this, INT64U time_array[TIME_ARRAY_SIZE]);
	INT64U		(* const get_value)(TIMEPOINT * this, TIMEUNIT unit);

	void		(* const copy)(TIMEPOINT * des, TIMEPOINT * src);
	INT64U		(* const delta)(TIMEPOINT * tp1, TIMEPOINT * tp2, TIMEUNIT unit);
} tp;

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
	INT64U  volatile time_array[TIME_ARRAY_SIZE]; // 0: ns, 1: us, 2: ms, 3: s
	INT64U  systick_dur_ns;

	TP_TYPE type:1;
	FUNPTR  callback; //void(*callback)();
};

/****************************** End Of Module ******************************/
