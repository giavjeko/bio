GCC=gcc -Wall
EXE=main

all: bitvector.o wavelet_tree.o main.o
	${GCC} bitvector.o wavelet_tree.o main.o -o ${EXE}

wtree.o: wtree.c
	${GCC} -c wtree.c
wtree.test: wtree.o wtree_test.c
	${GCC} wtree_test.c -o runtest
	./runtest
	rm runtest

vector.o: vector.c
	${GCC} -c vector.c
vector.test: vector.o vector_test.c
	${GCC} vector_test.c -o runtest
	./runtest
	rm runtest

bitvector.o: bitvector.c
	${GCC} -c bitvector.c
bitvector.test: bitvector.o bitvector_test.c
	${GCC} bitvector_test.c -o runtest
	./runtest
	rm runtest

bwt.o: bwt.c
	${GCC} -c bwt.c
bwt.test: bwt.o bwt_test.c
	${GCC} bwt_test.c -o runtest
	./runtest
	rm runtest

wavelet_tree.o: wavelet_tree.c
	${GCC} -c wavelet_tree.c

main.o: main.c
	${GCC} -c main.c

clean:
	rm *.o ${EXE}
