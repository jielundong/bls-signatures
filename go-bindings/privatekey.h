#ifndef GO_BINDINGS_PRIVATEKEY_H_
#define GO_BINDINGS_PRIVATEKEY_H_
#include "elements.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef void* CPrivateKey;

CPrivateKey CPrivateKeyFromBytes(void* p, int size);
void* CPrivateKeySerialize(CPrivateKey inPtr);
CG1Element CPrivateKeyGetG1(CPrivateKey inPtr);
CPrivateKey CPrivateKeyAggregate(void **privateKeys, int numPrivateKeys);
void CPrivateKeyRepr(CPrivateKey inPtr, void * repr);
void CPrivateKeyFree(CPrivateKey inPtr);
int CPrivateKeySizeBytes();
#ifdef __cplusplus
};
#endif
#endif //GO_BINDINGS_PRIVATEKEY_H_