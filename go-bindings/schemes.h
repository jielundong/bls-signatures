#ifndef GO_BINDINGS_SCHEMES_H_
#define GO_BINDINGS_SCHEMES_H_
#include "privatekey.h"
#ifdef __cplusplus
extern "C" {
#endif

CPrivateKey CAugSchemeMPLKenGen(void* p, int size);
CPrivateKey CPrivateKeyDeriveChildSk(CPrivateKey csk, uint32_t index);
CPrivateKey CDeriveChildSkUnhardened(CPrivateKey csk, uint32_t index);
CG1Element CDeriveChildPkUnhardened(CG1Element cpk, uint32_t index);
CG2Element CG2ElementsAggregate(void ** signs , int size);
CG2Element CSign(CPrivateKey csk, void * msg, int size);
CG2Element CSign2(CPrivateKey csk, void *msg, int size, CG1Element prepend_pk);
bool CVerify(CG1Element cpk, void * msg, int size, CG2Element sign);
bool CAggregateVerify(void ** publicKeys, int numPublicKeys, void ** msgs, int numMsgs, CG2Element sign);
#ifdef __cplusplus
};
#endif
#endif //GO_BINDINGS_SCHEMES_H_