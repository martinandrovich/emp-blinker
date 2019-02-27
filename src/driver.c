#include "driver.h"

static BOOLEAN irq_status;

void __enable_irq(void)
{
    asm volatile
    (
        "CPSIE i"
    );

    irq_status = 1;
}

void __disable_irq(void)
{
    asm volatile
    (
        "CPSID i"
    );

    irq_status = 0;
}

BOOLEAN __get__irq(void)
{
    return (BOOLEAN)irq_status;
}
