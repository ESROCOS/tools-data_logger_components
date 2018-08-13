/* This file was generated automatically: DO NOT MODIFY IT ! */

/* Declaration of the functions that have to be provided by the user */

#ifndef __USER_CODE_H_rbs_logger__
#define __USER_CODE_H_rbs_logger__

#include "C_ASN1_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

void rbs_logger_startup();

void rbs_logger_PI_sample(const asn1SccBase_samples_RigidBodyState *);

void rbs_logger_PI_shutdown();

#ifdef __cplusplus
}
#endif


#endif
