#include <stdio.h>
#include <dlfcn.h>
#include <ffi.h>

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
