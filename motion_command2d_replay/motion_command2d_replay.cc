/* User code: This file will not be overwritten by TASTE. */

#include "motion_command2d_replay.h"
#include <data_logger/LogFileReader.hpp>
#include <iostream>

using namespace data_logger;
#define LOGGER_TYPE asn1SccBase_commands_Motion2D
#define DECODING_FN asn1SccBase_commands_Motion2D_ACN_Decode
#define LOG_FILE "./motion_command2d_logger.cc.log"


int Decode(LOGGER_TYPE *pDst, BufferByte* pBuffer, size_t iBufferSize)
{
    (void)iBufferSize;
    int errorCode;

    BitStream strm;

    BitStream_AttachBuffer(&strm, pBuffer, iBufferSize);

    if (DECODING_FN(pDst, &strm, &errorCode)) {
        /* Decoding succeeded */
        return 0;
    } else {
    fprintf(stderr, "Could not decode LOGGER_TYPE (at %s, %d), error code was %d\n", __FILE__, __LINE__, errorCode);
        return -1;
    }
}


LogFileReader<LOGGER_TYPE> reader(LOG_FILE);
StreamHeader sth;
void motion_command2d_replay_startup()
{
    reader.setDecoding(Decode);
    sth = reader.readStreamHeader();
    std::cout << "\nData MetaModel: " << sth.dataMetaModel
              << "\nEncoding Hint: "<<sth.encodingHint<<"\n# Samples: "<<sth.nSamples<<std::endl;
}

void motion_command2d_replay_PI_trigger()
{
    LOGGER_TYPE sample_r;
    EncodedSample<LOGGER_TYPE> s;
    size_t idx = reader.readNextSample(s);
    if(idx == -1){
        std::cout << "\nNo more samples"<<std::endl;
        reader.closeLogfile();
        std::cout << "Closed"<<std::endl;
        return;
    }
    if((idx+1)%100 == 0){
        std::cout <<"\n"<< idx+1 << "/" << sth.nSamples<<" samples read"<<std::endl;
    }
    sample_r = s.getPayload();

    motion_command2d_replay_RI_sample(&sample_r);
}
