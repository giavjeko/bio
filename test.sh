#!/bin/bash

make

COUNT=$( ls files/in* | wc -l )
for i in $( seq 1 $(( $COUNT - 1 )))
do
  in=files/in${i}
  out=files/out${i}
  tmp=tmp
  ./lpc $in $tmp
  diff -q $tmp $out
  if [ $? -eq 0 ]
  then
    echo "OK: Correct for $i"
  else
    echo "ERROR: Wrong for $i"
  fi
  rm $tmp
done
