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

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

extern TIMEPOINT * tp_global;

/*************************  Function interfaces ****************************/

extern BUTTON* new_BUTTON(int SW);
extern void del_BUTTON(BUTTON*);

/*****************************    Constructs   *****************************/

ENUM KEYSTATE
{
   KEY_UP        =  0,
   DEBOUNCING    =  1,
   KEY_DOWN      =  2
};

ENUM BUTTONS
{
   SW2           =  0,
   SW1           =  4
};

/*****************************   MAIN STRUCT   *****************************/

struct BUTTON
{
    /** Members ************************************************************/
    ENUM KEYSTATE state;
    TIMEPOINT * tp_pressed;
    INT64U duration_ms;
    INT8U button;

    /** Methods ************************************************************/
    void (* const callback)();
    void (* const controller)(BUTTON * this);
    void (* const set_callback)(BUTTON * this, void(*callback)(INT64U _duration_ms));

};

/****************************** End Of Module ******************************/
