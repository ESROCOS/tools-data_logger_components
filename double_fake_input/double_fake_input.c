/* User code: This file will not be overwritten by TASTE. */

#include "double_fake_input.h"

void double_fake_input_startup()
{
    /* Write your initialization code here,
       but do not make any call to a required interface. */
}

void double_fake_input_PI_trigger()
{
    asn1SccT_Double val = 0.0;
    double_fake_input_RI_sample(&val);
}

