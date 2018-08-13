/* User code: This file will not be overwritten by TASTE. */

#include "rbs_logger.h"
#include <data_logger/LogFileWriter.hpp>
#include <iostream>
#include <csignal>

using namespace data_logger;
#define LOGGER_TYPE asn1SccBase_samples_RigidBodyState
#define ENCODING_FN asn1SccBase_samples_RigidBodyState_ACN_Encode
#define ENCODING_HINT "ASN.1/ACN"
#define DATA_MODEL_FILE "binary.c/dataview-uniq.asn"
#define LOG_FILE "./" __FILE__ ".log"

size_t Encode(BufferByte *pBuffer, 
	          size_t iMaxBufferSize, 
	          const LOGGER_TYPE *pSrc)
{
    (void)iMaxBufferSize;
    int errorCode;
    BitStream strm;

    BitStream_Init(&strm, pBuffer, iMaxBufferSize);

    if (ENCODING_FN(pSrc, &strm, &errorCode, TRUE) == FALSE) {
    	fprintf(stderr, "Could not encode LOGGER_TYPE (at %s, %d), errorCode was %d\n", __FILE__, __LINE__, errorCode);
        return -1;
    } else {
        return BitStream_GetLength(&strm);
    }
}


LogFileWriter<LOGGER_TYPE> writer(LOG_FILE);

void rbs_logger_startup()
{
    writer.setEncoding(Encode);
    writer.setDataModelFromFile(DATA_MODEL_FILE);
    writer.setEncodingHint(ENCODING_HINT);
    std::cout << "logging to " << LOG_FILE << std::endl;
    writer.start();
}

void rbs_logger_PI_sample(const asn1SccBase_samples_RigidBodyState *IN_sample)
{
    writer.write(*IN_sample);
}

void rbs_logger_PI_shutdown()
{
    writer.close();
}
