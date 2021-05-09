#ifndef GO_BINDINGS_ELEMENTS_H_
#define GO_BINDINGS_ELEMENTS_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef void* CG1Element;
void CG1ElementFree(CG1Element inPtr);
CG1Element CG1ElementFromBytes(void *p, int size);
CG1Element  CG1ElementGenerator();
CG1Element CG1ElementNegate(CG1Element org);
uint32_t CG1ElementGetFingerprint(CG1Element g1);
CG1Element CG1ElementAdd(CG1Element a, CG1Element b);
// CG1Element CG1ElementMul(CG1Element a, const bn_t & k);
// CG1Element CG1ElementRMul(const bn_t& k, CG1Element a);
void* CG1ElementSerialize(CG1Element inPtr);
int CG1ElementSizeBytes();

typedef void* CG2Element;
void CG2ElementFree(CG2Element inPtr);
CG2Element CG2ElementFromBytes(void *p, int size);
CG2Element  CG2ElementGenerator();
CG2Element CG2ElementNegate(CG2Element org);
CG2Element CG2ElementAdd(CG2Element a, CG2Element b);
void* CG2ElementSerialize(CG2Element inPtr);
int CG2ElementSizeBytes();


#ifdef __cplusplus
};
#endif
#endif //GO_BINDINGS_ELEMENTS_H_