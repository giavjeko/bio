GCC=gcc -Wall
EXE=main

all: bitvector.o wavelet_tree.o main.o
	${GCC} bitvector.o wavelet_tree.o main.o -o ${EXE}

bitvector.o: bitvector.c
	${GCC} -c bitvector.c
bitvector.test: bitvector.o bitvector_test.c
	${GCC} bitvector_test.c -o runtest
	./runtest
	rm runtest

wavelet_tree.o: wavelet_tree.c
	${GCC} -c wavelet_tree.c

main.o: main.c
	${GCC} -c main.c

clean:
	rm *.o ${EXE}