package blschia

// #cgo LDFLAGS: -L../build -lbls -lstdc++ -lgmp
// #cgo CXXFLAGS: -std=c++17 -I../build/_deps/relic-src/include -I../build/_deps/relic-build/include
// #include <stdbool.h>
// #include <stdlib.h>
// #include "privatekey.h"
// #include "blschia.h"
// #include "util.h"
import "C"
import (
	"runtime"
	"unsafe"
)

// KeyGen ...
func KeyGen(seed []byte) PrivateKey {
	var sk PrivateKey
	cBytesPtr := C.CBytes(seed)
	defer C.free(cBytesPtr)
	csk := C.CAugSchemeMPLKenGen(cBytesPtr, C.int(len(seed)))
	sk.sk = csk
	runtime.SetFinalizer(&sk, func(p *PrivateKey) { p.Free() })
	return sk
}

// DeriveChildSk ...
func DeriveChildSk(sk PrivateKey, index uint32) PrivateKey {
	var childSk PrivateKey
	csk := C.CPrivateKeyDeriveChildSk(sk.sk, C.uint(index))
	childSk.sk = csk
	runtime.SetFinalizer(&childSk, func(p *PrivateKey) { p.Free() })
	return childSk
}

// DeriveChildSkUnhardened ...
func DeriveChildSkUnhardened(sk PrivateKey, index uint32) PrivateKey {
	var childSk PrivateKey
	csk := C.CDeriveChildSkUnhardened(sk.sk, C.uint(index))
	childSk.sk = csk
	runtime.SetFinalizer(&childSk, func(p *PrivateKey) { p.Free() })
	return childSk
}

// DeriveChildPkUnhardened ...
func DeriveChildPkUnhardened(pk G1Element, index uint32) G1Element {
	var childPk G1Element
	cpk := C.CDeriveChildPkUnhardened(pk.pk, C.uint(index))
	childPk.pk = cpk
	runtime.SetFinalizer(&childPk, func(p *G1Element) { p.Free() })
	return childPk
}

// G2ElementsAggregate ...
func G2ElementsAggregate(signs []G2Element) (G2Element, error) {
	// Get a C pointer to an array of G2elments
	cG2ArrPtr := C.AllocPtrArray(C.size_t(len(signs)))
	defer C.FreePtrArray(cG2ArrPtr)
	// Loop thru each key and add the key C ptr to the array of ptrs at index
	for i, g2 := range signs {
		C.SetPtrArray(cG2ArrPtr, unsafe.Pointer(g2.sign), C.int(i))
	}

	var sign G2Element
	sign.sign = C.CG2ElementsAggregate(cG2ArrPtr, C.int(len(signs)))

	runtime.SetFinalizer(&sign, func(p *G2Element) { p.Free() })
	return sign, nil
}

// Sign ...
func Sign(sk PrivateKey, msg []byte) (G2Element, error) {
	var sign G2Element
	cBytesPtr := C.CBytes(msg)
	defer C.free(cBytesPtr)
	cg2 := C.CSign(sk.sk, cBytesPtr, C.int(len(msg)))
	sign.sign = cg2
	runtime.SetFinalizer(&sign, func(p *G2Element) { p.Free() })
	return sign, nil
}

// Sign2 ...
func Sign2(sk PrivateKey, msg []byte, pk G1Element) (G2Element, error) {
	var sign G2Element
	cBytesPtr := C.CBytes(msg)
	defer C.free(cBytesPtr)
	cg2 := C.CSign2(sk.sk, cBytesPtr, C.int(len(msg)), pk.pk)
	sign.sign = cg2
	runtime.SetFinalizer(&sign, func(p *G2Element) { p.Free() })
	return sign, nil
}

// Verify ...
func Verify(pk G1Element, msg []byte, sign G2Element) bool {
	cBytesPtr := C.CBytes(msg)
	defer C.free(cBytesPtr)
	return bool(C.CVerify(pk.pk, cBytesPtr, C.int(len(msg)), sign.sign))
}

// AggregateVerify ...
func AggregateVerify(pks []G1Element, msgs []string, sign G2Element) bool {
	cPubKeyArrPtr := C.AllocPtrArray(C.size_t(len(pks)))
	defer C.FreePtrArray(cPubKeyArrPtr)
	// Loop thru each key and add the key C ptr to the array of ptrs at index
	for i, pk := range pks {
		C.SetPtrArray(cPubKeyArrPtr, unsafe.Pointer(pk.pk), C.int(i))
	}

	cMsgsArrPtr := C.AllocPtrArray(C.size_t(len(msgs)))
	defer C.FreePtrArray(cMsgsArrPtr)
	for i, msg := range msgs {
		tmp := []byte(msg)
		tmp = append(tmp, 0)
		cBytesPtr := C.CBytes(tmp)
		defer C.free(cBytesPtr)
		C.SetPtrArray(cMsgsArrPtr, cBytesPtr, C.int(i))
	}

	return bool(C.CAggregateVerify(cPubKeyArrPtr, C.int(len(pks)), cMsgsArrPtr, C.int(len(msgs)), sign.sign))
}
