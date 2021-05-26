# Implementation of Hash Table

**Program Specs**:

A hash table (an 1D array of ordered linked list) is implemented using B number of bucket.
The bucket size, B, information will be given via argv[2] in command line.
The input to your program is a text file contains a list of triplets {<op firstName lastName >} where op is either + or - or ?; + means insert, - means delete, and ? means information retrieval; firstName and lastName are character strings. lastName in the triplet is the key passes to the hash function to get the bucket index from the hash function for information storage and retrieval.
  
The input looks like the following:
I. Inputs: There will be two inputs to the program:
a) inFile (use argv[1]): A text file contains a list of triplets {<op firstName lastName.}
For example,
+ Longcheng Ochilov
+ Sweyaksha Webster
