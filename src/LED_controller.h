/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: LED_controller.h
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
*******************************************************************************/
#pragma once

/*****************************    Includes    *********************************/

#include "../tm4c123gh6pm.h"
#include "emp_type.h"
#include "stdlib.h"
#include "LED.h"
#include "timepoint.h"
#include "driver.h"

/*****************************    Defines    **********************************/

typedef struct  LED_CONTROLLER_CLASS    LED_CONTROLLER_CLASS;
typedef struct  LED_CONTROLLER          LED_CONTROLLER;
typedef ENUM    LED_CONTROLLER_MODE     LED_CONTROLLER_MODE;
typedef ENUM    LED_CONTROLLER_DIR      LED_CONTROLLER_DIR;

#define REF_AUTOMODE_MS 200

/******************************************************************************/

extern TIMEPOINT * tp_global;

/*************************** MAIN Constructs   ********************************/
extern struct LED_CONTROLLER_CLASS
{
    LED_CONTROLLER * (* const new)(void);
    void  (* const del)(LED_CONTROLLER * this);

    void  (* const controller)(LED_CONTROLLER * this, LED * led_obj);
    void  (* const set_callback)(LED_CONTROLLER * this, INT32S duration_ms);

    void  (* const set_mode)(LED_CONTROLLER * this, LED_CONTROLLER_MODE mode);
    LED_CONTROLLER_MODE  (* const get_mode)(LED_CONTROLLER * this);

    void  (* const set_reference_ms)(LED_CONTROLLER * this, INT32S reference_ms);
    INT32S  (* const get_reference_ms)(LED_CONTROLLER * this);

} led_ctrl;

/*************************    CONSTRUCTS         ******************************/

ENUM LED_CONTROLLER_MODE
{
    MANUAL   =  0,
    AUTO     =  1
};

ENUM LED_CONTROLLER_DIR
{
    UP      =   0,
    DOWN    =   1
};

struct LED_CONTROLLER
{

    LED_CONTROLLER_MODE     mode_controller;
    LED_CONTROLLER_DIR      mode_direction;
    INT32S                  reference_ms;
    INT8U                   state_led; // state of led {001} {010}... etc RGB
    TIMEPOINT *             tp_pressed;

};
/***************************** END MODULE    **********************************/
