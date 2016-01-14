#!/usr/bin/env python2

def cpl(a, b):
  l = min(len(a), len(b))
  for i in xrange(l):
    if a[i] != b[i]:
      return i
  return l

string = raw_input()
l = len(string)
sa = [string[i:] for i in xrange(l)]
sa.sort()
print -1
for i in xrange(l - 1):
  print cpl(sa[i], sa[i + 1])
print -1
