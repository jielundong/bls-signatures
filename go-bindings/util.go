package blschia

// #cgo LDFLAGS: -L../build -lbls -lstdc++ -lgmp
// #cgo CXXFLAGS: -std=c++17 -I../src -I../build/contrib/relic/include -I../contrib/relic/include
// #include <stdbool.h>
// #include <stdlib.h>
// #include "util.h"
import "C"

//Hash256 ...
func Hash256(msg []byte) []byte {
	cBytesPtr := C.CBytes(msg)
	defer C.free(cBytesPtr)
	retptr := C.CUtilHash256(cBytesPtr, C.int(len(msg)))
	defer C.SecFree(retptr)
	return C.GoBytes(retptr, C.CUtilHash256Size())
}
