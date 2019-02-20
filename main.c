#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "src/emp_type.h"
#include "src/button.h"
#include "src/timepoint.h"

TIMEPOINT * tp_global;

int main(void)
{

    // Initialize global timepoint instance
    tp_global = new_TIMEPOINT(200);

	return 0;
}
