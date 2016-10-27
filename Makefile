all:
	gcc -shared -o test_return.so test_return.c
	gcc -o test test.c -lffi -ldl
	./test
