#include "LED.h"
#include <malloc.h>


//Function descriptions given in  LED.h file.


/*************************  Function declaration ***************************/
static LED* LED_new();
static _Bool LED_get_state(LED* this);
static void LED_set_state(LED* this, _Bool state);
static RGB LED_get_color(LED* this);
static void LED_set_color(LED* this, RGB Value);
static void LED_set_callback(LED* this, void(*callback)(void));
static void LED_del(LED* this);


/*****************************   Functions   *******************************/


static LED* LED_new()
/****************************************************************************
*   Input    :
*   Output   : returns a pointer to an instance	 on the heap
*   Function : new
****************************************************************************/
{	 
	LED* obj = malloc(sizeof(LED));
	obj->state = 1;
	obj->color = (RGB){ 1,1,1 };
	return obj;
}


static void LED_del(LED* this)
/****************************************************************************
*   Input    : instance
*   Output   : void
*   Function : Free the memory of the instance.
****************************************************************************/
{
	free(this);
}


static _Bool LED_get_state(LED* this)
/****************************************************************************
*   Input    :  an instance
*   Output   :  returns the state of the LED ( on/off)
*   Function : get_state
****************************************************************************/
{
	return this->state;
}


static void LED_set_state(LED* this, _Bool _state)
/****************************************************************************
*   Input    :  set the state for the given instance of LED
*   Output   :  void
*   Function : set_state
****************************************************************************/
{
	this->state = _state;
}


static RGB LED_get_color(LED* this)
/****************************************************************************
*   Input    : instance of LED
*   Output   : returns the state of the given LED
*   Function : get_color
****************************************************************************/
{
	return this->color;
}


static void LED_set_color(LED* this, RGB _Value)
/****************************************************************************
*   Input    : A 3 bit value.
*   Output   : updates the color;
*   Function : set_color
****************************************************************************/
{
	this->color = _Value;
}


static void LED_set_callback(LED* this, void(*callback)(void) )
/****************************************************************************
*   Input    : Instance of LED, the desired function that should be called whenever, an event occurs.
*   Output   : void
*   Function : set_callback
****************************************************************************/
{
	this->callback = callback;
}


struct LED_CLASS LED_t =
{	.new = &LED_new,
	.get_state = &LED_get_state ,
	.set_state = &LED_set_state	,
	.get_color = &LED_get_color	,
	.set_color = &LED_set_color	,
	.set_callback = &LED_set_callback
};