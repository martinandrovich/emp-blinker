/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: LED.h
*
* PROJECT....: EMP

* DESCRIPTION: Interface to a LED struct.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
****************************************************************************/

#pragma once
#include "emp_type.h"

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

typedef struct  LED LED;
typedef struct  RGB RGB;
typedef enum    LED_TYPE LED_TYPE;

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

#define     INC     4;

/*************************  Function interfaces ****************************/



/*************************    Class Functions    ***************************/

extern struct LED_CLASS
{
    LED* (*const new)();
	_Bool (*const get_state)(LED*);
	void (*const set_state)(LED*, _Bool);
	RGB (*const get_color)(LED*);
	void (*const set_color)(LED*,RGB);
	void (*const set_callback)(LED* ,void (*callback)(void));
	void(*const del)(LED*);
	
	

} LED_t;

/*****************************    Constructs   *****************************/



struct RGB 
{
	INT8U R : 1;
	INT8U G : 1;
	INT8U B : 1;
};


struct LED
{

	_Bool state;
	RGB color;
	void(*callback)(void);

};

/****************************** End Of Module ******************************/
