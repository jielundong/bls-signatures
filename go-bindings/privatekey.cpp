#include "privatekey.h"

#include "bls.hpp"
#include "error.h"

CPrivateKey CPrivateKeyFromBytes(void* p, int size)
{
    bls::PrivateKey* skPtr;
    if (size != bls::PrivateKey::PRIVATE_KEY_SIZE) {
        gErrMsg = "Length of bytes object not equal to PrivateKey::SIZE";
        return nullptr;
    }
    try {
        skPtr = new bls::PrivateKey(
            bls::PrivateKey::FromBytes(bls::Bytes(static_cast<uint8_t*>(p), size)));
    } catch (const std::exception& ex) {
        // set err
        gErrMsg = ex.what();
        return nullptr;
    }

    return skPtr;
}

void* CPrivateKeySerialize(CPrivateKey inPtr)
{
    bls::PrivateKey* key = (bls::PrivateKey*)inPtr;

    uint8_t* buffer =
        bls::Util::SecAlloc<uint8_t>(bls::PrivateKey::PRIVATE_KEY_SIZE);

    key->Serialize(buffer);
    return static_cast<void*>(buffer);
}

void CPrivateKeyFree(CPrivateKey inPtr) {
    bls::PrivateKey* key = (bls::PrivateKey*)inPtr;
    delete key;
}

CG1Element CPrivateKeyGetG1(CPrivateKey inPtr){
    bls::PrivateKey* key = (bls::PrivateKey*)inPtr;
    bls::G1Element* g1 = new bls::G1Element(key->GetG1Element());
    return g1;
}

CPrivateKey CPrivateKeyAggregate(void **privateKeys, int numPrivateKeys){
  // build privkey vector
    std::vector<bls::PrivateKey> vecPrivKeys;
    for (int i = 0 ; i < numPrivateKeys; ++i) {
        bls::PrivateKey* key = (bls::PrivateKey*)privateKeys[i];
        vecPrivKeys.push_back(*key);
    }

    bls::PrivateKey* key;
    try {
        key = new bls::PrivateKey(
            bls::PrivateKey::Aggregate(vecPrivKeys)
        );
    } catch (const std::exception& ex) {
        // set err
        gErrMsg = ex.what();
        return nullptr;
    }

    return key;
}

void CPrivateKeyRepr(CPrivateKey inPtr, void * repr){
    bls::PrivateKey* key = (bls::PrivateKey*)inPtr;
    uint8_t *output =
        bls::Util::SecAlloc<uint8_t>(bls::PrivateKey::PRIVATE_KEY_SIZE);
    key->Serialize(output);
    std::string ret =
        "<PrivateKey " +
        bls::Util::HexStr(output, bls::PrivateKey::PRIVATE_KEY_SIZE) + ">";
    bls::Util::SecFree(output);
    memcpy_s(repr, ret.size(), ret.c_str(), ret.size());
    return ;
}

int CPrivateKeySizeBytes(){
    return bls::PrivateKey::PRIVATE_KEY_SIZE;
}