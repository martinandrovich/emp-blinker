#include "emp_type.h"
#include "timepoint.h"
#include "stdlib.h"
/*
 * button.h
 *
 *  Created on: Feb 20, 2019
 *      Author:
 */

#pragma once


typedef struct
{
    ENUM KEYSTATE
    {
     KEY_DOWN    = 0,
     KEY_UP      = 1,
     KEY_PRESSED = 2
    } state;

    BOOLEAN debounced;
    TIMEPOINT tp_pressed;
    INT16U duration;

} BUTTON;

extern BUTTON* new_button();
extern void del_button();
extern void handler_button ();
extern void button_isr (void);


