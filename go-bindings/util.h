#ifndef GO_BINDINGS_UTIL_H_
#define GO_BINDINGS_UTIL_H_
#ifdef __cplusplus
extern "C" {
#endif

// Export the BLS SecFree method
void SecFree(void *p);
void * CUtilHash256(void * p, int size);
int CUtilHash256Size();
#ifdef __cplusplus
};
#endif
#endif //GO_BINDINGS_UTIL_H_