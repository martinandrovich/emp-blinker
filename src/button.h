/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: button.c
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
* 190220  DT    Module created.
*
****************************************************************************/

#pragma once

/***************************** Include files *******************************/

#include "emp_type.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "timepoint.h"
#include "driver.h"

/*****************************    Defines    *******************************/

typedef struct BUTTON BUTTON;
typedef enum   BUTTON_NAME BUTTON_NAME;
typedef enum   KEYSTATE KEYSTATE;

/*****************************   Constants   *******************************/

/********************** External declaration of Variables ******************/

extern TIMEPOINT * tp_global;

/*****************************   Functions   *******************************/

/*****************************   MAIN STRUCT   *****************************/

extern struct BUTTON_CLASS
{
	// Constructor & Destructor
	BUTTON*	(* const new)(BUTTON_NAME SW);
	void    (* const del)(BUTTON * this);

	/** Methods ************************************************************/
	void (* const controller)(BUTTON * this);
	void (* const set_callback)(BUTTON * this, void(*callback)(INT32S duration_ms));

} btn;

/*****************************    Constructs   *****************************/

ENUM KEYSTATE
{
   KEY_UP        =  0,
   DEBOUNCING    =  1,
   KEY_DOWN      =  2
};

ENUM BUTTON_NAME
{
   SW2           =  0,
   SW1           =  4
};

struct BUTTON
{
	/** Members ************************************************************/
	ENUM KEYSTATE state;
	TIMEPOINT * tp_pressed;
	TIMEPOINT * tp_released;
	TIMEPOINT * tp_db;
	TIMEPOINT * tp_pending;
	INT32S duration_ms;
	INT32S db_delta_ms;
	BUTTON_NAME button;

	BOOLEAN pending_callback;

	void (* callback)(INT32S duration_ms);
};

/****************************** End Of Module ******************************/
