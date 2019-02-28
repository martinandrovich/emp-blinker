/****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: LED_controller.c
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
#include "LED_controller.h"
/********************************* function decl ***************************/

static LED_CONTROLLER * LED_CONTROLLER_new(void);
static void LED_CONTROLLER_del(LED_CONTROLLER * this);

static void LED_CONTROLLER_callback(LED_CONTROLLER * this, INT32S duration_ms);
static void LED_CONTROLLER_controller(LED_CONTROLLER * this, LED * led_obj);
static void _LED_CONTROLLER_circulation(LED_CONTROLLER * this);

static void LED_CONTROLLER_set_mode(LED_CONTROLLER * this, LED_CONTROLLER_MODE mode);
static LED_CONTROLLER_MODE LED_CONTROLLER_get_mode(LED_CONTROLLER * this);

static void LED_CONTROLLER_set_reference_ms(LED_CONTROLLER * this, INT32S reference_ms);
static INT32S LED_CONTROLLER_get_reference_ms(LED_CONTROLLER * this);

/********************************defines   **********************************/

#define MAXLED      7
#define MINLED      0
#define BITONE      1
#define BITTWO      2
#define BITTHREE    3

/****************************************************************************/

static LED_CONTROLLER * LED_CONTROLLER_new(void)
/****************************************************************************
*   Input    : no input, constructor
*   Output   : object pointer
*   Function : creates object
****************************************************************************/
{
    // allocate memory
    LED_CONTROLLER * this = malloc(sizeof(LED_CONTROLLER));
    // set mode NORMAL -- and count up
    this->mode_controller   =   MANUAL;
    this->mode_direction    =   UP;
    // make timepoint as reference
    this->reference_ms      =   2000;
    // set state for LED
    this->state_led         =   0;
    //
    this->tp_pressed        =   tp.new(NORMAL);

    return this;
}

static void LED_CONTROLLER_del(LED_CONTROLLER * this)
/****************************************************************************
*   Input    : this object
*   Function : deletes object
****************************************************************************/
{
    // deallocate memory
    free(this);
}

static void LED_CONTROLLER_callback(LED_CONTROLLER * this, INT32S duration_ms)
/****************************************************************************
*   Input    : Duration
*   Function : LED controller, chooses state
****************************************************************************/
{
    switch (duration_ms)
    {
        case -1:
            this->mode_direction = (this->mode_direction == UP) ? DOWN : UP;
            break;
        // ^-- change mode if double click -- toggle -- does not change anything
        default:
            this->mode_controller = (this->reference_ms >= duration_ms) ? MANUAL : AUTO;
            // if normal mode change
            if(this->mode_controller == MANUAL)
            {
                _LED_CONTROLLER_circulation(this);
            }
            else
            {
                __disable_irq();
                tp.copy(this->tp_pressed, tp_global);
                __enable_irq();
            }
            break;
        // -- change mode if AUTO otherwise change to NORMAL and calculate new led.
    };
}

static void _LED_CONTROLLER_circulation(LED_CONTROLLER * this)
/****************************************************************************
*   Input    : this object
*   Function : update state_led
****************************************************************************/
{
    INT8U alias_state = this->state_led;

    if(this->mode_direction == UP)
    {
        alias_state += 1;
        this->state_led = (this->state_led == MAXLED) ? MINLED : alias_state;
    }
    else
    {
        alias_state -= 1;
        this->state_led = (this->state_led == MINLED) ? MAXLED : alias_state;
    }
}

static void LED_CONTROLLER_controller(LED_CONTROLLER * this, LED * led_obj)
/****************************************************************************
*   Input    : Duration
*   Function : LED controller, chooses state
****************************************************************************/
{
    if(this->mode_controller == AUTO)
    {
        __disable_irq();
            if(tp.delta(this->tp_pressed, tp_global, ms) >= REF_AUTOMODE_MS)
            {
                _LED_CONTROLLER_circulation(this);
                tp.copy(this->tp_pressed, tp_global);
            };
        __enable_irq();
    }

    led.set_color(led_obj, (RGB){(((this->state_led) >> 2) & 1), (((this->state_led) >> 0) & 1), (((this->state_led) >> 1) & 1)});

}


static void LED_CONTROLLER_set_mode(LED_CONTROLLER * this, LED_CONTROLLER_MODE mode)
/****************************************************************************
*   Input    : this and the mode u want to set
*   Function : set mode in this object
****************************************************************************/
{
    this->mode_controller = mode;
}

static LED_CONTROLLER_MODE LED_CONTROLLER_get_mode(LED_CONTROLLER * this)
/****************************************************************************
*   Input    : this object
*   Function : get this object mode
****************************************************************************/
{
    return this->mode_controller;
}

static void LED_CONTROLLER_set_reference_ms(LED_CONTROLLER * this, INT32S reference_ms)
/****************************************************************************
*   Input    : set reference_ms
*   Function : set reference in this object
****************************************************************************/
{
    this->reference_ms = reference_ms;
}

static INT32S LED_CONTROLLER_get_reference_ms(LED_CONTROLLER * this)
/****************************************************************************
*   Input    : get reference_ms
*   Function : set reference in this object
****************************************************************************/
{
    return this->reference_ms;
}

struct LED_CONTROLLER_CLASS led_ctrl =
/****************************************************************************
*   all functions for the object
****************************************************************************/
{
    .new                =   &LED_CONTROLLER_new,
    .del                =   &LED_CONTROLLER_del,

    .controller         =   &LED_CONTROLLER_controller,
    .callback           =   &LED_CONTROLLER_callback,
    .set_mode           =   &LED_CONTROLLER_set_mode,
    .get_mode           =   &LED_CONTROLLER_get_mode,
    .set_reference_ms   =   &LED_CONTROLLER_set_reference_ms,
    .get_reference_ms   =   &LED_CONTROLLER_get_reference_ms
};
