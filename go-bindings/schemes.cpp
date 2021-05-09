#include "schemes.h"

#include <string>
#include <vector>

#include "bls.hpp"
#include "error.h"

CPrivateKey CAugSchemeMPLKenGen(void* p, int size)
{
    const uint8_t* input = reinterpret_cast<const uint8_t*>(p);
    const vector<uint8_t> inputVec(input, input + size);
    return new bls::PrivateKey(bls::AugSchemeMPL().KeyGen(inputVec));
}

CPrivateKey CPrivateKeyDeriveChildSk(CPrivateKey csk, uint32_t index)
{
    bls::PrivateKey* sk = (bls::PrivateKey*)csk;
    return new bls::PrivateKey(bls::AugSchemeMPL().DeriveChildSk(*sk, index));
}

CPrivateKey CDeriveChildSkUnhardened(CPrivateKey csk, uint32_t index)
{
    bls::PrivateKey* sk = (bls::PrivateKey*)csk;
    return new bls::PrivateKey(
        bls::AugSchemeMPL().DeriveChildSkUnhardened(*sk, index));
}
CG1Element CDeriveChildPkUnhardened(CG1Element cpk, uint32_t index)
{
    bls::G1Element* pk = (bls::G1Element*)cpk;
    return new bls::G1Element(
        bls::AugSchemeMPL().DeriveChildPkUnhardened(*pk, index));
}

CG2Element CG2ElementsAggregate(void** signs, int size)
{
    // build signature vector
    std::vector<bls::G2Element> vecG2Elements;
    for (int i = 0; i < size; ++i) {
        bls::G2Element* sign = (bls::G2Element*)signs[i];
        vecG2Elements.push_back(*sign);
    }

    bls::G2Element* sign;
    try {
        sign = new bls::G2Element(bls::AugSchemeMPL().Aggregate(vecG2Elements));
    } catch (const std::exception& ex) {
        // set err
        gErrMsg = ex.what();
        return nullptr;
    }

    return sign;
}

CG2Element CSign(CPrivateKey csk, void* msg, int size)
{
    bls::PrivateKey* sk = (bls::PrivateKey*)csk;
    bls::Bytes msgBytes = bls::Bytes(static_cast<uint8_t*>(msg), size);

    vector<uint8_t> v(msgBytes.begin(), msgBytes.end());
    return new bls::G2Element(bls::AugSchemeMPL().Sign(*sk, v));
}
CG2Element CSign2(
    CPrivateKey csk,
    void* msg,
    int size,
    CG1Element prepend_pk)
{
    bls::PrivateKey* sk = (bls::PrivateKey*)csk;
    bls::G1Element* pk = (bls::G1Element*)prepend_pk;
    bls::Bytes msgBytes = bls::Bytes(static_cast<uint8_t*>(msg), size);
    vector<uint8_t> v(msgBytes.begin(), msgBytes.end());
    return new bls::G2Element(bls::AugSchemeMPL().Sign(*sk, v, *pk));
}

bool CVerify(CG1Element cpk, void* msg, int size, CG2Element sign)
{
    bls::G1Element* pk = (bls::G1Element*)cpk;
    bls::G2Element* g2 = (bls::G2Element*)sign;
    bls::Bytes msgBytes = bls::Bytes(static_cast<uint8_t*>(msg), size);
    vector<uint8_t> v(msgBytes.begin(), msgBytes.end());
    return (bls::AugSchemeMPL().Verify(*pk, v, *g2));
}

bool CAggregateVerify(void ** publicKeys, int numPublicKeys, void ** msgs, int numMsgs, CG2Element sign){
    std::vector<bls::G1Element> vecG1Elements;
    bls::G1Element ** g1s = reinterpret_cast<bls::G1Element**>(publicKeys);
    for(int i =0; i < numPublicKeys; i ++){
        vecG1Elements.push_back(*g1s[i]);
    }
     vector<vector<uint8_t>> vecs(numMsgs);
    for (int i = 0; i < numMsgs; ++i) {
        std::string s(reinterpret_cast<char*>(msgs[i]));
        vecs[i] = vector<uint8_t>(s.begin(), s.end());
    }
    bls::G2Element * g2 = (bls::G2Element*)sign;
  return bls::AugSchemeMPL().AggregateVerify(vecG1Elements, vecs, *g2);
}