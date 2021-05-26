# Implementation of Hash Table

**Program Specs**:

A hash table (an 1D array of ordered linked list) is implemented using B number of bucket.
The bucket size, B, information will be given via argv[2] in command line.
The input file is a text file containing a list of triplets {<op firstName lastName >} where op is either + or - or ?; + means insert, - means remove, and ? means information retrieval; firstName and lastName are character strings. The lastName in the triplet is the key passed to the hash function to get the bucket index for information storage/retrieval.

The input file will look like the following:
* + John Doe
* - Jane Doe
  .
  .
  .
