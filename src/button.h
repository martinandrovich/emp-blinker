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


ENUM KEYSTATE
{
   KEY_UP        = 0,
   DEBOUNCING    = 1,
   KEY_DOWN      = 2
};


struct BUTTON
{
    //
    //
    KEYSTATE e_state;

    //
    //
    TIMEPOINT tp_pressed;

    //
    //
    INT16U i_duration;

    //
    //
    void(*handler_button)(BUTTON*);

    //
    //
    void(*is_key_down)(BUTTON*);

    //
    //
    void(*debounce_button)(BUTTON*);

    //
    //
    void(*key_down)(BUTTON*);



};
