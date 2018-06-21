all:
	gcc -g -shared -o test_return.so test_return.c
	gcc -g -o test test.c -lffi -ldl
	./test
