#include <stdio.h>
#include <stdlib.h>
extern signed short test_return_sshort() {
    return 102;
}

int testFunc(int m, int n) {
  printf("params: %d %d \n", n, m);
  return n+m;
}

