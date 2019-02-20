#pragma once

#include <stdlib.h>
#include "emp_type.h"

typedef struct
{
    INT16U hours;
    INT16U minutes;
    INT16U seconds;
    INT16U milliseconds;
    INT16U microseconds;
    INT16U nanoseconds;

    INT32U unit_ns;

    // Update timepoint with a systick unit.
    // void tick()
    // {
    //     ;
    // };
    //
    // // Get difference between two timepoints; return integer.
    // INTU16 delta_ms(TIMEPOINT * tp)
    // {
    //     ;
    // };

} TIMEPOINT;

extern  TIMEPOINT * new_TIMEPOINT(INT32U clock_freq, INT32U systick_dur);
extern  void        del_TIMEPOINT(TIMEPOINT * tp );
