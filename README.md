# TopWords

@filename words.c
@author Colin St. Claire, colinst.claire@gmail.com
@created 2/16/2016
@modified 3/11/2016
This is a C program to open a file,
read it's "words" and store them in a 
Hash Table (with seperate chaining). The
program then adds the desired amount of
words to an array, sorts them, and prints
the top X words and their associated counts.
If the desired amount is invalid, all words
will be printed.
	
To run:
$ make
$ ./PrintKeyVal -(# of desired words) firstFile secFile...
  
