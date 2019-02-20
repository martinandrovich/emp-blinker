#pragma once

#include "emp_type.h"

typedef struct
{
    INT16U hours;
    INT16U hours;
    INT16U seconds;
    INT16U milliseconds;
    INT16U microseconds;
    INT16U nanoseconds;

    INT32U unit_ns;

    void tick(/* arguments */)
    {
        // add unit_ns to current counters
    };

    INTU16 delta_ms(TIMEPOINT * tp)
    {
        /* code */
    };

} TIMEPOINT;
