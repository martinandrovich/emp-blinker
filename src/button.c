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

/***************************** Include files *******************************/

#include "button.h"

/*****************************    Defines    *******************************/
#define SW1             4
#define DEBOUNCE_MIN    20
#define NS              0

/*****************************   Constants   *******************************/

/*************************  Function declaration ***************************/
void is_key_down(BUTTON* this);
void debounce_button(BUTTON* this);
void key_down(BUTTON* this );
BUTTON* new_button();
void del_button(BUTTON* this);

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void BUTTON_handler_button(BUTTON* this)
/****************************************************************************
*   Input    : Object this pointer, this is a method
*   Function : Finite State Machine determines, which state for button to be in
****************************************************************************/
{
    int int_systick_flag = 1; //remove

    if(int_systick_flag == 1)
    {
        switch (this->state)
        {
              case KEY_UP:
                    is_key_down(this);
              break;
              /*            ---             */
              case DEBOUNCING:
                    debounce_button(this);
              break;
              /*            ---             */
              case KEY_DOWN:
                    key_down(this);
              break;
              /*            ---             */
              default:
                    this->state = KEY_UP;
              break;
         }
     }

     return;
};


void is_key_down(BUTTON* this)
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, calculate if btn pressed
****************************************************************************/
{

    if(GPIO_PORTF_DATA_R & (1 << SW1))
    {
        this->state = DEBOUNCING;
        this->tp_pressed = (*tp_global);
    }

    return;
}

void debounce_button(BUTTON* this)
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, calculate debounce_state
****************************************************************************/
{
    if( GPIO_PORTF_DATA_R & (1 << SW1) )
    {
        if(TIMEPOINT_delta((*tp_global), this->tp_pressed, this->u_timepoint_delta) >= DEBOUNCE_MIN)
        {
            this->state = KEY_DOWN;
        }
        else
        {
            this->state = DEBOUNCING;
        };
    }
    else
    {
            this->state = KEY_UP;
    };

    return;
}


void key_down(BUTTON* this )
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, pick mode
****************************************************************************/
{

    if((GPIO_PORTF_DATA_R & (1 << SW1)) == FALSE )
    {

        this->duration = TIMEPOINT_delta((*tp_global), this->tp_pressed, this->u_timepoint_delta);

        this->state = KEY_UP;
    }

    return;
}


BUTTON* new_button()
/****************************************************************************
*   Output   : Object
*   Function : Constructor for Button.
****************************************************************************/
{
    BUTTON* this                =      malloc(sizeof(BUTTON));

    this->handler_button        =      &BUTTON_handler_button;

    this->duration              =      0;
    this->u_timepoint_delta     =      NS;

    return this;
}

void del_button(BUTTON* this)
/****************************************************************************
*   Input    : Pointer to Button object
*   Function : Destructor for object
****************************************************************************/
{
    free(this);
};

/****************************** End Of Module *******************************/
