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

#pragma once

/***************************** Include files *******************************/

#include "emp_type.h"
#include "timepoint.h"
#include "stdlib.h"

/*****************************    Defines    *******************************/

typedef struct BUTTON BUTTON;

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

extern void handler_button (BUTTON*);
extern BUTTON* new_button();


/*****************************    Constructs   *****************************/

ENUM KEYSTATE
{
   KEY_UP        =  0,
   DEBOUNCING    =  1,
   KEY_DOWN      =  2
};

/*****************************   MAIN STRUCT   *****************************/

struct BUTTON
{

    ENUM KEYSTATE state;
    TIMEPOINT tp_pressed;
    INT16U duration;

/*****************************   PUBLIC FUNCT  *****************************/

    void(*handler_button)(BUTTON*);

};

/****************************** End Of Module ******************************/
