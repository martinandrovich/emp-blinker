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
    //
    //
    ENUM KEYSTATE
    {
       KEY_UP    = 0,
       DEBOUNCING    = 1,
       KEY_DOWN      = 2
    } state;

    //
    //
    TIMEPOINT tp_pressed;

    //
    //
    INT16U i_duration;

    //
    //
    void (*m_handler_button)(BUTTON* );

    //
    //
    void (*m_is_key_down)(BUTTON* );


    //
    //
    void (*m_debounce_button)(BUTTON* );


    //
    //
    void (*m_key_down)(BUTTON* );



};
