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
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

static BOOLEAN SW1_TRIGGER = NULL;

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void button_isr (void) // interrupt service routine
{
    /* some static variable
      static BOOLEAN SW1_TRIGGER = true;
    */
};

int get_isr (BUTTON* this) // interrupt service routine
{
    //get static variable
    return 1;
};

void handler_button (BUTTON* this)
{
    if (this->get_isr = TRUE)
    {
      switch(this->state)
        {/*
          case NO_STATE:

            this->debounced = false;

            this->state = KEY_DOWN;

            this->tp_pressed = (get_time_Stamp)

            break;

            case KEY_DOWN:

            this is debouncing

            uint32 DIFFERENCE = getCurrentTimeStamp - this->tp_pressed;

            *if (difference >= DEBOUNCE)
            {
            this->debounced=true;

            }

            break;

            case KEY_UP:



            break;

            case KEY_PRESSED:
                // code here
                break;
          */
        }



    //disable interrupt for button;
    //init debouncing
    }

    return;
};

BUTTON* new_button()
{
    BUTTON* p = malloc(sizeof(BUTTON));
    p->debounced = 0;
    p->duration = 0;
    p->handler_button = &handler_button;
    p->get_isr = &get_isr;
    return p;
};

void del_button(BUTTON* p)
{
    free(p);
};


/*void test1(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
/*{
  dummy1++;
}*/

/*  extern void test2(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
/*{
  dummy2++;
}*/

/****************************** End Of Module *******************************/











