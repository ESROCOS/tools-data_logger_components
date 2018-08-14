/* This file was generated automatically: DO NOT MODIFY IT ! */

/* Declaration of the functions that have to be provided by the user */

#ifndef __USER_CODE_H_rbs_replay__
#define __USER_CODE_H_rbs_replay__

#include "C_ASN1_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

void rbs_replay_startup();

void rbs_replay_PI_trigger();

extern void rbs_replay_RI_sample(const asn1SccBase_samples_RigidBodyState *);

#ifdef __cplusplus
}
#endif


#endif
