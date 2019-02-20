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


typedef struct BUTTON BUTTON;

extern void del_button();
extern void handler_button (BUTTON*);
extern void button_isr (void);
extern BUTTON* new_button();


struct BUTTON
{
    ENUM KEYSTATE
    {
       NO_STATE    = 0,
       KEY_DOWN    = 1,
       KEY_UP      = 2,
       KEY_PRESSED = 3
    } state;

    BOOLEAN debounced;

    TIMEPOINT tp_pressed;

    INT16U duration;

    void (*debouncing_button)(BUTTON*);
    void (*handler_button)(BUTTON*);
    int (*get_isr)(BUTTON*);
};

