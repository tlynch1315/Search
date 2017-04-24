Project 01 - README
===================

Members
-------

- Will Fritz (wfritz@nd.edu)
- Tommy Lynch (tlynch2)

Responses
---------

1) We handled parsing command line options by using strcmp because there are many different options and the options are strings. This allowed us to better understand our own code as well. WE parsed each flag like we usually do in these assignments (while(argind < argc ...) Then we used srtcmp to see if the arg was the same as the many different options. We used this to populate the settings struct

2) we walkd directories by testing if the given path is a directory, and if it is not then the error is displayed.  If it is a directory, the directory is then read using readdir. lstat, is then used on the readdir() object to populate a stat struct. After this, the program checks if the name of the read file is '.'. If it is then if the root is not filtered out, execute is called on the root. After checking for '.', the programs checks if the file is '..'. If it is then continue is used to skip this file. Finally, if the files are not '.' or '..' then a new path was made from the current file being read. This path was made by combing the root and the name of the file being read using sprintf. THen, if the file is a directory, the program recursively calls search on the new path. IF the file is not a directory, then execute is called on the file if it is not filtered out. Finally, the directory is closed.

3) we decided to print it or not based on the settings.  If the print setting is true, then it is printed.  If not, then it is not printed. THis was done in the execute.c file. We began by chekcing ig exec_argc flag was used, then we forked from the parent. Then, if settings was set to print, the path was printed. 

4. Search uses a lot more system calls than find does. Find, also uses a few of the same system calls as serach, but ultimately find uses a pretty unique combination of system calls. Also, find does not uses lstat at all, when search utilizez multiple times

5. The trace of find bigger than search when checking /etc without any flags. However, whhen -exec echo \{\}\ is added as a flag, the trace of find becomes much smaller than the trace of search

PS Results of script are appended to this README
Contributions
-------------
Will: utilities.c search.c Makefile 
Tommy: main.c execute.c syscalls.py
Collaborated on: filter.c README and debugging


./search /etc
  8043 lstat
   698 getdents
   391 open
   351 close
    26 write
    24 stat
     9 mmap
     4 brk
     3 mprotect
     3 fstat
     1 read
     1 munmap
     1 ioctl
     1 fcntl
     1 execve
     1 arch_prctl
     1 access
Find /etc
   792 open
   715 newfstatat
   712 close
   703 fchdir
   698 getdents
   359 fstat
   106 write
    25 mmap
    24 stat
    13 mprotect
    10 read
     5 brk
     4 munmap
     3 ioctl
     2 rt_sigaction
     2 futex
     1 uname
     1 statfs
     1 set_tid_address
     1 set_robust_list
     1 rt_sigprocmask
     1 getrlimit
     1 fcntl
     1 execve
     1 arch_prctl
     1 access
./search /etc -exec echo \{\}\;
  8043 lstat
  3673 wait4
  3673 clone
   698 getdents
   391 open
   351 close
    24 stat
     8 mmap
     4 brk
     3 mprotect
     2 fstat
     1 read
     1 munmap
     1 fcntl
     1 execve
     1 arch_prctl
     1 access
 calls syscall
------ ----------------
find /etc -exec echo \{\} \;
    72 open
    26 mmap
    24 stat
    13 mprotect
    13 close
    12 write
    11 fstat
    10 read
     3 munmap
     3 brk
     2 rt_sigaction
     1 rt_sigprocmask
