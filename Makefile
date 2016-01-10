GCC=gcc -Wall
EXE=main

all: set bitvector bwt wtree queue list
	${GCC} main.c -o ${EXE}

test: set.test bitvector.test bwt.test wtree.test queue.test list.test

wtree: wtree.c
	${GCC} -c wtree.c
wtree.test: wtree wtree_test.c
	${GCC} wtree_test.c -o runtest
	./runtest
	rm runtest

set: set.c
	${GCC} -c set.c
set.test: set set_test.c
	${GCC} set_test.c -o runtest
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

list: list.c
	${GCC} -c list.c
list.test: list list_test.c
	${GCC} list_test.c -o runtest
	./runtest
	rm runtest

queue: queue.c
	${GCC} -c queue.c
queue.test: queue queue_test.c
	${GCC} queue_test.c -o runtest
	./runtest
	rm runtest

clean:
	rm *.o
