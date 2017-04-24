#!/usr/bin/env python2.7

import os
import sys
import subprocess

print './search /etc'

os.system('strace -c -o search.txt ./search /etc 2&> /dev/null')
os.system('cat search.txt | tail -n 19 | head -n 17 | cut -c 35-40,51-67 | sort -g -r')

print '\nFind /etc'
os.system('strace -c -o search.txt find /etc 2&> /dev/null')
os.system('cat search.txt | tail -n 28 | head -n 26 | cut -c 35-40,51-67 | sort -g -r')

print '\n./search /etc -exec echo \{\}\;'
os.system('strace -c -o search.txt ./search /etc -exec echo \{\} \; 2&> /dev/null')
os.system('cat search.txt | tail -n 21 | head -n 19 | cut -c 35-40,51-67 | sort -g -r')

print '\nfind /etc -exec echo \{\} \;'
os.system('strace -c -o search.txt find /etc -exec echo \{\} \; 2&> /dev/null')
os.system('cat search.txt | tail -n 24 | head -n 12 | cut -c 35-40,51-67 | sort -g -r')

os.system('rm search.txt')

