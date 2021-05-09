#include "elements.h"

#include <cstring>
#include <vector>

#include "bls.hpp"
#include "error.h"

CG1Element CG1ElementFromBytes(void* p, int size)
{
    bls::G1Element* g1Ptr;
    try {
        g1Ptr = new bls::G1Element(bls::G1Element::FromBytes(
            bls::Bytes(static_cast<const uint8_t*>(p), size)));
    } catch (const std::exception& ex) {
        gErrMsg = ex.what();
        return nullptr;
    }
    return g1Ptr;
}

CG1Element CG1ElementGenerator()
{
    bls::G1Element* g1Ptr;
    g1Ptr = new bls::G1Element(bls::G1Element::Generator());
    return g1Ptr;
}

CG1Element CG1ElementNegate(CG1Element org)
{
    bls::G1Element * g1 = (bls::G1Element*)org;
    bls::G1Element* g1Ptr;
    g1Ptr = new bls::G1Element(g1->Negate());
    return g1Ptr;
}

uint32_t CG1ElementGetFingerprint(CG1Element g1)
{
    bls::G1Element* g1Element = (bls::G1Element*)g1;
    return g1Element->GetFingerprint();
}

CG1Element CG1ElementAdd(CG1Element a, CG1Element b)
{
    bls::G1Element* g1Ptr;
    bls::G1Element* g1Element1 = (bls::G1Element*)a;
    bls::G1Element* g1Element2 = (bls::G1Element*)b;
    g1Ptr = new bls::G1Element(*g1Element1 + *g1Element2);
    return g1Ptr;
}
// CG1Element CG1ElementMul(CG1Element a, const bn_t& k)
// {
//     bls::G1Element* g1Ptr;
//     bls::G1Element* g1Element1 = (bls::G1Element*)a;
//     g1Ptr = new bls::G1Element(*g1Element1, k);
//     return g1Ptr;
// }
// CG1Element CG1ElementRMul(const bn_t& k, CG1Element a)
// {
//     return CG1ElementMul(a, k);
// }

void* CG1ElementSerialize(CG1Element inPtr)
{
    uint8_t* buffer = static_cast<uint8_t*>(malloc(bls::G1Element::SIZE));
    vector<uint8_t> out;

    bls::G1Element* key = (bls::G1Element*)inPtr;
    out = key->Serialize();
    memcpy_s(buffer, bls::G1Element::SIZE, out.data(), out.size());
    return static_cast<void*>(buffer);
}

int CG1ElementSizeBytes(){
    return bls::G1Element::SIZE;
}
void CG1ElementFree(CG1Element inPtr)
{
    bls::G1Element* key = (bls::G1Element*)inPtr;
    delete key;
}

////CG2Element///////////////////
void CG2ElementFree(CG2Element inPtr){
    bls::G2Element * sign = (bls::G2Element*)inPtr;
    delete sign;
}

CG2Element CG2ElementFromBytes(void *p, int size){
   bls::G2Element* g2Ptr;
    try {
        g2Ptr = new bls::G2Element(bls::G2Element::FromBytes(
            bls::Bytes(static_cast<const uint8_t*>(p), size)));
    } catch (const std::exception& ex) {
        gErrMsg = ex.what();
        return nullptr;
    }
    return g2Ptr;
}

CG2Element  CG2ElementGenerator(){
  bls::G2Element* g2Ptr;
    g2Ptr = new bls::G2Element(bls::G2Element::Generator());
    return g2Ptr;
}
CG2Element CG2ElementNegate(CG2Element org){
    bls::G2Element * g1 = (bls::G2Element*)org;
    bls::G2Element* g2Ptr;
    g2Ptr = new bls::G2Element(g1->Negate());
    return g2Ptr;
}

CG2Element CG2ElementAdd(CG2Element a, CG2Element b){
    bls::G2Element* g2Ptr;
    bls::G2Element* g2Element1 = (bls::G2Element*)a;
    bls::G2Element* g2Element2 = (bls::G2Element*)b;
    g2Ptr = new bls::G2Element(*g2Element1 + *g2Element2);
    return g2Ptr;
}
void* CG2ElementSerialize(CG2Element inPtr){
    uint8_t* buffer = static_cast<uint8_t*>(malloc(bls::G2Element::SIZE));
    vector<uint8_t> out;

    bls::G2Element* sign = (bls::G2Element*)inPtr;
    out = sign->Serialize();
    memcpy_s(buffer, bls::G2Element::SIZE, out.data(), out.size());
    return static_cast<void*>(buffer);
}

int CG2ElementSizeBytes(){
	return bls::G2Element::SIZE;
}