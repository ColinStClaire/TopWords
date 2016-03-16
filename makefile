
PrintKeyVal: hash.o words.o
	gcc -g -o PrintKeyVal hash.o words.o

hash.o: hash.c
	gcc -g -Wall -pedantic -std=c99 -c hash.c hash.h

words.o: words.c
	gcc -g -Wall -pedantic -std=c99 -c words.c hash.h
