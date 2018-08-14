/* User code: This file will not be overwritten by TASTE. */

#include "rbs_fake_input.h"

void rbs_fake_input_startup()
{
    /* Write your initialization code here,
       but do not make any call to a required interface. */
}

void rbs_fake_input_PI_trigger()
{
    asn1SccBase_samples_RigidBodyState val;
    asn1SccBase_samples_RigidBodyState_Initialize(&val);
    val.position.data.arr[0] = 1;
    val.position.data.arr[1] = 2;
    val.position.data.arr[2] = 3;
    val.orientation.im.arr[0] = 4;
    val.orientation.im.arr[1] = 5;
    val.orientation.im.arr[2] = 6;
    val.orientation.re = 1;
    rbs_fake_input_RI_sample(&val);
}

