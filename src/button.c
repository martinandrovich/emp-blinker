/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.c
*
* PROJECT....: EMP
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

/*****************************   Variables   *******************************/

/*INT16S   dummy2;

/*****************************   Functions   *******************************/
void button_isr (void) // interrupt service routine
{

};

void handler_button ()
{

};

BUTTON* new_button()
{
    BUTTON* p = malloc(sizeof(BUTTON));
    p->debounced = 0;
    p->duration = 0;
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











