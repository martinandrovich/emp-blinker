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
#include "timepoint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"

/*****************************    Defines    *******************************/

typedef struct BUTTON BUTTON;
typedef enum   BUTTON_NAME BUTTON_NAME;
typedef enum   KEYSTATE KEYSTATE;

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

/*****************************   MAIN STRUCT   *****************************/

extern struct BUTTON_CLASS
{
    // Constructor & Destructor
    BUTTON*	(* const new)(BUTTON_NAME SW);
    void    (* const del)(BUTTON * this);

    /** Methods ************************************************************/
    void (* const controller)(BUTTON * this);
    void (* const set_callback)(BUTTON * this, void(*callback)(INT64U _duration_ms));

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
    INT64U duration_ms;
    INT8U button;

    void (* callback)();
};

/****************************** End Of Module ******************************/
