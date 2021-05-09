package blschia

// #cgo LDFLAGS: -L../build -lbls -lstdc++
// #cgo CXXFLAGS: -std=c++14 -I../src -I../build/_deps/relic-src/include -I../build/_deps/relic-build/include
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

// PrivateKey represents a BLS private key
type PrivateKey struct {
	sk C.CPrivateKey
}

// PrivateKeyFromBytes constructs a new private key from bytes
func PrivateKeyFromBytes(data []byte) (PrivateKey, error) {
	// Get a C pointer to bytes
	cBytesPtr := C.CBytes(data)
	defer C.free(cBytesPtr)

	var sk PrivateKey
	sk.sk = C.CPrivateKeyFromBytes(cBytesPtr, C.int(len(data)))

	runtime.SetFinalizer(&sk, func(p *PrivateKey) { p.Free() })
	return sk, nil
}

// Free releases memory allocated by the key
func (sk PrivateKey) Free() {
	C.CPrivateKeyFree(sk.sk)
}

// Serialize returns the byte representation of the private key
func (sk PrivateKey) Serialize() []byte {
	ptr := C.CPrivateKeySerialize(sk.sk)
	defer C.SecFree(ptr)
	return C.GoBytes(ptr, C.CPrivateKeySizeBytes())
}

// FromBytes ...
func (sk PrivateKey) FromBytes(data []byte) PrivateKey  {
	cBytesPtr := C.CBytes(data)
	defer C.free(cBytesPtr)
	sk.sk = C.CPrivateKeyFromBytes(cBytesPtr, C.int(len(data)))
	runtime.SetFinalizer(&sk, func(p *PrivateKey) { p.Free() })
	return sk
}

// GetG1 returns the public key which corresponds to the private key
func (sk PrivateKey) GetG1() G1Element {
	var pk G1Element
	pk.pk = C.CPrivateKeyGetG1(sk.sk)
	runtime.SetFinalizer(&pk, func(p *G1Element) { p.Free() })
	return pk
}

// PrivateKeyAggregate securely aggregates multiple private keys into one
func PrivateKeyAggregate(privateKeys []PrivateKey) (PrivateKey, error) {
	// Get a C pointer to an array of private keys
	cPrivKeyArrPtr := C.AllocPtrArray(C.size_t(len(privateKeys)))
	defer C.FreePtrArray(cPrivKeyArrPtr)
	// Loop thru each key and add the key C ptr to the array of ptrs at index
	for i, privKey := range privateKeys {
		C.SetPtrArray(cPrivKeyArrPtr, unsafe.Pointer(privKey.sk), C.int(i))
	}

	var sk PrivateKey
	sk.sk = C.CPrivateKeyAggregate(cPrivKeyArrPtr, C.int(len(privateKeys)))

	runtime.SetFinalizer(&sk, func(p *PrivateKey) { p.Free() })
	return sk, nil
}
