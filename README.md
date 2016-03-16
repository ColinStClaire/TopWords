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
	
	Example:
	./PrintKeyVal -20 sherlock.txt
	
	[0] key = the             val = 80030
  [1] key = of              val = 40025
  [2] key = and             val = 38313
  [3] key = to              val = 28766
  [4] key = in              val = 22050
  [5] key = a               val = 21153
  [6] key = that            val = 12512
  [7] key = he              val = 12401
  [8] key = was             val = 11410
  [9] key = it              val = 10681
  [10] key = his             val = 10034
  [11] key = is              val = 9774
  [12] key = with            val = 9740
  [13] key = as              val = 8064
  [14] key = i               val = 7687
  [15] key = had             val = 7383
  [16] key = for             val = 6941
  [17] key = at              val = 6791
  [18] key = by              val = 6738
  [19] key = on              val = 6643
  
  
  To run:
  $ make
  $ ./PrintKeyVal -(# of desired words) firstFile secFile...
  
