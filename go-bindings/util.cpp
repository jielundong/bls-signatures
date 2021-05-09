#include "util.h"
#include "bls.hpp"
#include <string>


void * CUtilHash256(void * p, int size){
    const uint8_t *input = reinterpret_cast<const uint8_t *>(p);
    uint8_t * output = bls::Util::SecAlloc<uint8_t>(bls::BLS::MESSAGE_HASH_LEN);
    bls::Util::Hash256(output, input, size);
    return  reinterpret_cast<char *>(output);
}

void SecFree(void *p) {
    bls::Util::SecFree(p);
}

int CUtilHash256Size(){
    return bls::BLS::MESSAGE_HASH_LEN;
}