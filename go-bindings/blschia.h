// Copyright 2019 Chia Network Inc

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GO_BINDINGS_BLSCHIA_H_
#define GO_BINDINGS_BLSCHIA_H_
#include <stdbool.h>
#include <stdint.h>
#include "privatekey.h"
#include "elements.h"
#include "schemes.h"
#ifdef __cplusplus
extern "C" {
#endif


// Additional C++ helper funcs for allocations
void** AllocPtrArray(size_t len);
void SetPtrArray(void **arrPtr, void *elemPtr, int index);
void FreePtrArray(void **inPtr);
void* GetPtrAtIndex(void **arrPtr, int index);

void* GetAddressAtIndex(uint8_t *ptr, int index);

const char* GetLastErrorMsg();

#ifdef __cplusplus
}
#endif
#endif  // GO_BINDINGS_BLSCHIA_H_
