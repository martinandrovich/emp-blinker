/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: button.c
*
* PROJECT....: Project 1
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
/*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "button.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"
/*****************************    Defines    *******************************/
#define SW1 4
#define DEBOUNCE_MIN 20

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/



void BUTTON_handler_button(BUTTON * this)
/****************************************************************************
*   Input    : Object this pointer, this is a method
*   Function : Finite State Machine determines, which state for button to be in
****************************************************************************/
{
    int int_systick_flag = 1; //quick fix
  if(int_systick_flag == 1)
  {
    switch (this->state)
    {

      case KEY_UP:
        this->m_is_key_down(this);
      break;

      case DEBOUNCING:
        this->m_debounce_button(this);
      break;

      case KEY_DOWN:
        this->m_key_down(this);
      break;

      default:
        this->state = KEY_UP;
      break;

    }
  }

  return;
};


void BUTTON_is_key_down(BUTTON * this)
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, calculate if btn pressed
****************************************************************************/
{
  if(GPIO_PORTF_DATA_R & (1 << SW1))
  {
      this->state = DEBOUNCING;
      /* this->tp_pressed = tp_global; */
  }
  return;
}

void BUTTON_debounce_button(BUTTON * this)
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, calculate debounce_state
****************************************************************************/
{

  if( GPIO_PORTF_DATA_R & (1 << SW1) )
  {
    /*
    if(TIMEPOINT_delta_ms(tp_global,this->tp_pressed) >= DEBOUNCE_MIN)
    {
      this->state = KEY_DOWN;
    }
    else
    {
      this->state = DEBOUNCING;
    }
    */
  }
  else
  {
    this->state = KEY_UP;
  };

  return;

}


void BUTTON_key_down(BUTTON * this )
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, pick mode
****************************************************************************/
{
  if( GPIO_PORTF_DATA_R & (1 << SW1) )
  {



  }
}


BUTTON* new_button()
/****************************************************************************
*   Output   : Object
*   Function : Constructor for Button.
****************************************************************************/
{
    BUTTON* p = malloc(sizeof(BUTTON));
    p->m_handler_button = &BUTTON_handler_button;
    p->m_is_key_down = &BUTTON_is_key_down;
    p->m_debounce_button = &BUTTON_debounce_button;
    p->m_key_down = &BUTTON_key_down;
    return p;
};

void del_button(BUTTON* p)
/****************************************************************************
*   Input    : Pointer to Button object
*   Function : Destructor for object
****************************************************************************/
{
    free(p);
};

/****************************** End Of Module *******************************/
