package blschia

// #cgo LDFLAGS: -L../build -lbls -lstdc++
// #cgo CXXFLAGS: -std=c++14 -I../src -I../build/_deps/relic-src/include -I../build/_deps/relic-build/include
// #include <stdbool.h>
// #include <stdlib.h>
// #include "blschia.h"
import "C"
import "runtime"

// G1Element represents a BLS public key
type G1Element struct {
	pk C.CG1Element
}

// G2Element represents a BLS signature
type G2Element struct {
	sign C.CG2Element
}

// G1ElementFromBytes ...
func G1ElementFromBytes(data []byte) (G1Element, error) {
	// Get a C pointer to bytes
	cBytesPtr := C.CBytes(data)
	defer C.free(cBytesPtr)
	var g1 G1Element
	g1.pk = C.CG1ElementFromBytes(cBytesPtr, C.int(len(data)))
	runtime.SetFinalizer(&g1, func(p *G1Element) { p.Free() })
	return g1, nil
}

// G1ElementGenerator ...
func G1ElementGenerator() G1Element {
	var g1 G1Element
	cg1 := C.CG1ElementGenerator()
	g1.pk = cg1
	runtime.SetFinalizer(&g1, func(p *G1Element) { p.Free() })
	return g1
}

// GetFingerprint ...
func (pk G1Element) GetFingerprint() uint32 {
	return uint32(C.uint(C.CG1ElementGetFingerprint(pk.pk)))
}

// Serialize ...
func (pk G1Element) Serialize() []byte {
	ptr := C.CG1ElementSerialize(pk.pk)
	defer C.free(ptr)
	return C.GoBytes(ptr, C.CG1ElementSizeBytes())
}
// FromBytes ...
func (pk G1Element) FromBytes(data []byte) G1Element  {
	cBytesPtr := C.CBytes(data)
	defer C.free(cBytesPtr)
	pk.pk = C.CG1ElementFromBytes(cBytesPtr, C.int(len(data)))
	runtime.SetFinalizer(&pk, func(p *G1Element) { p.Free() })
	return pk
}

// Negate ...
func (pk G1Element) Negate() G1Element {
	var g1 G1Element
	cg1 := C.CG1ElementNegate(pk.pk)
	g1.pk = cg1
	runtime.SetFinalizer(&g1, func(p *G1Element) { p.Free() })
	return g1
}

// Add ...
func (pk G1Element) Add(other G1Element) G1Element {
	var g1 G1Element
	cg1 := C.CG1ElementAdd(pk.pk, other.pk)
	g1.pk = cg1
	runtime.SetFinalizer(&g1, func(p *G1Element) { p.Free() })
	return g1
}

// Mul ...
// func (pk G1Element) Mul(other C.bn_t) G1Element {
// 	var g1 G1Element
// 	cg1 := C.CG1ElementMul(pk.pk, other)
// 	g1.pk = cg1
// 	runtime.SetFinalizer(&g1, func(p *G1Element) { p.Free() })
// 	return g1
// }

// RMul ...
// func (pk G1Element) RMul(other C.bn_t) G1Element {
// 	var g1 G1Element
// 	cg1 := C.CG1ElementRMul(other, pk.pk)
// 	g1.pk = cg1
// 	runtime.SetFinalizer(&g1, func(p *G1Element) { p.Free() })
// 	return g1
// }

// Free releases memory allocated for C.CG1Element
func (pk G1Element) Free() {
	C.CG1ElementFree(pk.pk)
}

//////G2Element//////////////////////////

// G2ElementFromBytes ...
func G2ElementFromBytes(data []byte) (G2Element, error) {
	// Get a C pointer to bytes
	cBytesPtr := C.CBytes(data)
	defer C.free(cBytesPtr)
	var g2 G2Element
	g2.sign = C.CG2ElementFromBytes(cBytesPtr, C.int(len(data)))
	runtime.SetFinalizer(&g2, func(p *G2Element) { p.Free() })
	return g2, nil
}

// G2ElementGenerator ...
func G2ElementGenerator() G2Element {
	var g2 G2Element
	cg2 := C.CG2ElementGenerator()
	g2.sign = cg2
	runtime.SetFinalizer(&g2, func(p *G2Element) { p.Free() })
	return g2
}

// Serialize ...
func (sign G2Element) Serialize() []byte {
	ptr := C.CG2ElementSerialize(sign.sign)
	defer C.free(ptr)
	return C.GoBytes(ptr, C.CG2ElementSizeBytes())
}

func (sign G2Element) FromBytes(data []byte) G2Element  {
	cBytesPtr := C.CBytes(data)
	defer C.free(cBytesPtr)
	sign.sign = C.CG2ElementFromBytes(cBytesPtr, C.int(len(data)))
	runtime.SetFinalizer(&sign, func(p *G2Element) { p.Free() })
	return sign
}

// Negate ...
func (sign G2Element) Negate() G2Element {
	var g2 G2Element
	cg2 := C.CG2ElementNegate(sign.sign)
	g2.sign = cg2
	runtime.SetFinalizer(&g2, func(p *G2Element) { p.Free() })
	return g2
}

// Add ...
func (sign G2Element) Add(other G2Element) G2Element {
	var g2 G2Element
	cg2 := C.CG2ElementAdd(sign.sign, other.sign)
	g2.sign = cg2
	runtime.SetFinalizer(&g2, func(p *G2Element) { p.Free() })
	return g2
}

// Free ...
func (sign G2Element) Free() {
	C.CG2ElementFree(sign.sign)
}
