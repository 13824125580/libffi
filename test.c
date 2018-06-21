#include <stdio.h>
#include <dlfcn.h>
#include <ffi.h>
#include <malloc.h>
#include <stdlib.h>

int main() {
  //拿函数指针
  void *lib_handle  = dlopen("./test_return.so", RTLD_NOW|RTLD_GLOBAL);
  void* functionPtr = dlsym(lib_handle, "testFunc");
  int argCount = 2;

  //按ffi要求组装好参数类型数组
  ffi_type **ffiArgTypes = alloca(sizeof(ffi_type *) *argCount);
  ffiArgTypes[0] = &ffi_type_sint;
  ffiArgTypes[1] = &ffi_type_sint;

   //按ffi要求组装好参数数据数组
  void **ffiArgs = alloca(sizeof(void *) *argCount);
  void *ffiArgPtr = alloca(ffiArgTypes[0]->size);
  int *argPtr = ffiArgPtr;
  *argPtr = 8;
  ffiArgs[0] = ffiArgPtr;

  void *ffiArgPtr2 = alloca(ffiArgTypes[1]->size);
  int *argPtr2 = ffiArgPtr2;
  *argPtr2 = 2;
  ffiArgs[1] = ffiArgPtr2;

  //生成 ffi_cfi 对象，保存函数参数个数/类型等信息，相当于一个函数原型
  ffi_cif cif;
  ffi_type *returnFfiType = &ffi_type_sint;
  ffi_status ffiPrepStatus = ffi_prep_cif_var(&cif, FFI_DEFAULT_ABI, (unsigned int)0, (unsigned int)argCount, returnFfiType, ffiArgTypes);

  if (ffiPrepStatus == FFI_OK) {
    //生成用于保存返回值的内存
    void *returnPtr = NULL;
    if (returnFfiType->size) {
      returnPtr = alloca(returnFfiType->size);
    }
    //根据cif函数原型，函数指针，返回值内存指针，函数参数数据调用这个函数
    ffi_call(&cif, functionPtr, returnPtr, ffiArgs);

    //拿到返回值
    int returnValue = *(int *)returnPtr;
    printf("ret: %d \n", returnValue);
  }
}
#if 0
int main() {
    ffi_cif cif;
    void *lib_handle   = dlopen("./test_return.so", RTLD_NOW|RTLD_GLOBAL);
    void * entry_point = dlsym(lib_handle, "test_return_sshort");
    ffi_status status  = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 0, &ffi_type_sshort, NULL);

    signed short ret;
    ffi_call(&cif, entry_point, &ret, NULL);
    fprintf(stderr, "%d\n", (signed short)ret);

    return 0;
}
#endif
