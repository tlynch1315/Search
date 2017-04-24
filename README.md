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

3) we decided to print it or not based on the settings.  If the print setting is true, then it is printed.  If not, then it is not printed.

Contributions
-------------
