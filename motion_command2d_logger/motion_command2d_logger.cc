/* User code: This file will not be overwritten by TASTE. */

#include "motion_command2d_logger.h"
#include <data_logger/LogFileWriter.hpp>
#include <iostream>
#include <csignal>

using namespace data_logger;
#define LOGGER_TYPE asn1SccBase_commands_Motion2D
#define ENCODING_FN asn1SccBase_commands_Motion2D_ACN_Encode
#define ENCODING_HINT "ASN.1"
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

void shutdown( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n"<<std::endl;

   // cleanup and close up stuff here  
   // terminate program  
   writer.close();

   exit(signum);  
}

void motion_command2d_logger_startup()
{
    writer.setEncoding(Encode);
    writer.setDataModelFromFile(DATA_MODEL_FILE);
    writer.setEncodingHint(ENCODING_HINT);
    std::cout << "logging to " << LOG_FILE << std::endl;;
    writer.start();
    //Register signal handler for SIGINT to close log file
    signal(SIGINT, shutdown);
}

void motion_command2d_logger_PI_sample(const asn1SccBase_commands_Motion2D *IN_sample)
{
    writer.write(*IN_sample);
}

