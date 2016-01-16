#!/bin/bash

make
make bwt.analysis
make wtree.analysis

get_mem() {
  filename=$1
  grep RSS $filename | cut -d ':' -f 2
}

get_time() {
  filename=$1
  grep User $filename | cut -d ':' -f 2
}

process() {
  bin=$1
  in=$2
  out=$3
  tmp=$( mktemp )
  ./measure -o $tmp 2>/dev/null $bin $in $out
  t=$( get_time $tmp )
  m=$( get_mem $tmp )
  echo "Time: $t"
  echo "Memory: $m"
  rm $tmp
}

COUNT=$( ls files/in* | wc -l )
for i in $( seq 1 $(( $COUNT - 1 )))
do
  in=files/in${i}
  size=$( cat $in | wc -c )
  echo "Test case $i, $(( $size - 1 )) characters"
  echo "Burrows-Wheeler transform"
  process ./bwt_analysis $in
  echo "Wavelet tree construction"
  process ./wtree_analysis $in
  echo "LPC"
  process ./lpc $in /dev/null
  echo
done
