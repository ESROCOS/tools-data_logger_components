/* User code: This file will not be overwritten by TASTE. */

#include "fake_input.h"

void fake_input_startup()
{
    /* Write your initialization code here,
       but do not make any call to a required interface. */
}

void fake_input_PI_trigger()
{
    asn1SccBase_commands_Motion2D val;
    asn1SccBase_commands_Motion2D_Initialize(&val);
    fake_input_RI_sample(&val);
}

