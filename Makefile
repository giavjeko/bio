GCC=gcc -Wall
EXE=main

all: vector bitvector bwt wtree
#	${GCC} bitvector wavelet_tree main -o ${EXE}

test: vector.test bitvector.test bwt.test wtree.test

wtree: wtree.c
	${GCC} -c wtree.c
wtree.test: wtree wtree_test.c
	${GCC} wtree_test.c -o runtest
	./runtest
	rm runtest

vector: vector.c
	${GCC} -c vector.c
vector.test: vector vector_test.c
	${GCC} vector_test.c -o runtest
	./runtest
	rm runtest

bitvector: bitvector.c
	${GCC} -c bitvector.c
bitvector.test: bitvector bitvector_test.c
	${GCC} bitvector_test.c -o runtest
	./runtest
	rm runtest

bwt: bwt.c
	${GCC} -c bwt.c
bwt.test: bwt bwt_test.c
	${GCC} bwt_test.c -o runtest
	./runtest
	rm runtest

clean:
	rm *.o
