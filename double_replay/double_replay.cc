/* User code: This file will not be overwritten by TASTE. */

#include "double_replay.h"
#include <data_logger/LogFileReader.hpp>
#include <iostream>

using namespace data_logger;
#define LOGGER_TYPE asn1SccT_Double
#define DECODING_FN asn1SccT_Double_ACN_Decode
#define LOG_FILE "./double_logger.cc.log"


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

void double_replay_startup()
{
    reader.setDecoding(Decode);
    sth = reader.readStreamHeader();
    std::cout << "\nData MetaModel: " << sth.dataMetaModel
              << "\nEncoding Hint: "<<sth.encodingHint<<"\n# Samples: "<<sth.nSamples<<std::endl;
}

void double_replay_PI_trigger()
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

    double_replay_RI_sample(&sample_r);
}

