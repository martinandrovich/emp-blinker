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

#define DEBOUNCE_MIN    0
#define NS              0
#define SW1_INT         30
#define button_bit      this->button

/*****************************   typedef   *********************************/

/*************************  Function declaration ***************************/
void BUTTON_is_key_down(BUTTON*);
void BUTTON_debounce_button(BUTTON*);
void BUTTON_key_down(BUTTON*);
void BUTTON_init_hardware(BUTTON*);

BUTTON* new_BUTTON(int);
void del_BUTTON(BUTTON*);

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void BUTTON_controller(BUTTON* this)
/****************************************************************************
*   Input    : Object this pointer, this is a method
*   Function : Finite State Machine determines, which state for button to be in
****************************************************************************/
{
    switch (this->state)
    {
          case KEY_UP:
                BUTTON_is_key_down(this);
          break;
          /*            ---             */
          case DEBOUNCING:
                BUTTON_debounce_button(this);
          break;
          /*            ---             */
          case KEY_DOWN:
                BUTTON_key_down(this);
          break;
          /*            ---             */
          default:
                this->state  =  KEY_UP;
          break;
     }

     return;
};

void BUTTON_is_key_down(BUTTON* this)
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, calculate if btn pressed
****************************************************************************/
{

    if( GPIO_PORTF_DATA_R & (1 << button_bit) ) //if btn pressed then
    {
        this->state         =   DEBOUNCING;
        //this->tp_pressed = new_TIMEPOINT(INT64U systick_dur_ns)
        //this->tp_pressed->copy(*(this->pressed), tp_global);
    }

    return;
}

void BUTTON_debounce_button(BUTTON* this)
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, calculate debounce_state
****************************************************************************/
{

    if( GPIO_PORTF_DATA_R & (1 << button_bit) ) //if btn pressed then
    {
        if(this->tp_pressed.delta_ms(tp_global, &(this->tp_pressed)) >= DEBOUNCE_MIN)
        {
            this->state     =   KEY_DOWN;
        }
        else
        {
            this->state     =   DEBOUNCING;
        };
    }                                             //else go to begin state
    else
    {
        this->state         =   KEY_UP;
    };

    return;
}


void BUTTON_key_down(BUTTON* this )
/****************************************************************************
*   Output   : Object
*   Function : Method for m_handler_button, pick mode
****************************************************************************/
{

    if((GPIO_PORTF_DATA_R & (1 << button_bit)) == FALSE )
    {

        this->duration_ms       =   this->tp_pressed.delta_ms(tp_global, &(this->tp_pressed));

        this->state             =   KEY_UP;

        /*
        if(this->callback != NULL)
        {

        }
        */
    }

    return;
}


BUTTON* new_BUTTON(int SW)
/****************************************************************************
*   Output   : Object
*   Function : Constructor for Button.
****************************************************************************/
{
    BUTTON* this                =   malloc(sizeof(BUTTON));

    this->BUTTON_controller     =   &BUTTON_controller;

    this->duration_ms           =   0;
    this->state                 =   KEY_UP;
    this->button                =   SW;

    BUTTON_init_hardware(this);

    return this;
}

void del_BUTTON(BUTTON* this)
/****************************************************************************
*   Input    : Pointer to Button object
*   Function : Destructor for object
****************************************************************************/
{
    free(this);
};

void BUTTON_init_hardware(BUTTON* this)
/****************************************************************************
*   Input    : input this Button and Parameter
*   Function : Setup Hardware
****************************************************************************/
{
    // Enable GPIO F Register
    SYSCTL_RCGCGPIO_R           |=  SYSCTL_RCGC2_GPIOF;

    asm volatile(
                " nop;"
                " nop;"
                " nop;"
            );

    // PORTF Direction for Button
    GPIO_PORTF_DIR_R            &=  (0 << button_bit);

    // PORF Pull UP - Active Low
    GPIO_PORTF_PUR_R            |=  (1 << button_bit);

    // 0 = Edge, 1 = Level - Interrupt Sense
    // GPIO_PORTF_IS_R    &=  (0 << SW); unused

    // 0 = No, 1 = Yes - Interrupt Both Edges
    // GPIO_PORTF_IBE_R   &=  (0 << SW1); unused

    // 0 = Falling, 1 = Rising - Interrupt Event
    // GPIO_PORTF_IEV_R   |=  (1 << SW1); unused

    // 0 = Masked , 1 = Enabled - Interrupt mask
    // GPIO_PORTF_IM_R    |=  (1 << SW1); unused

    // 0 = Masked , 1 = Enabled - Interrupt control register
    // GPIO_PORTF_ICR_R   |=  (1 << SW1);

    // Clear pending interrupt.
    // NVIC_UNPEND0_R |= (1 << SW1_INT);

    // Set Priority leave it to default.
    // NVIC_PRI7_R &= (0 << 23 | 1 << 22 | 1 << 21);

    // Enable interrupt on PORTF
    // NVIC_EN0_R |= (1 << SW1_INT); //Enable interrupt


};

/****************************** End Of Module *******************************/
