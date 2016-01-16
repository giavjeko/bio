GCC=gcc -Wall
EXE=lpc

all: io set bitvector bwt wtree queue list
	${GCC} lpc.c -o ${EXE}

test: set.test bitvector.test bwt.test wtree.test queue.test list.test

io: io.c
	${GCC} -c io.c

wtree: wtree.c
	${GCC} -c wtree.c
wtree.test: wtree wtree_test.c
	${GCC} wtree_test.c -o runtest
	./runtest
	rm runtest
wtree.analysis: io wtree wtree_analysis.c
	${GCC} wtree_analysis.c -o wtree_analysis

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
bwt.analysis: io bwt bwt_analysis.c
	${GCC} bwt_analysis.c -o bwt_analysis

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

gen: gen.c
	${GCC} gen.c -o gen

clean:
	rm -f *.o ${EXE} gen
