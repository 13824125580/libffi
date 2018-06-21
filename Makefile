all:
	gcc -g -fPIC -shared -o test_return.so test_return.c
	gcc -g -o test test.c -L./libs/lib -ldl ./libs/lib/libffi.so
