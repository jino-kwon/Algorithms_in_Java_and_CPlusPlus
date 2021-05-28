# 4. Huffman Coding

**Program Specs**:

The Huffman Coding Scheme is implemented -- from compute frequency to text compression / decompression.
1) Open the input text file and count the characters counts.
2) Construct a Huffman linked list based on the character counts.
3) Construct a Huffman binary tree (to be used for decoding later), and then construct a Huffman code array (for encoding).
4) Ask the user if they want to compress a text file (Y/N).

If yes,

5) Ask the user for the name of a text file to be compressed.
6) Compress the text file using the Huffman code table, and output the results.
7) The name of the compressed file is to be created at run-time.
8) To ensure the encoding algorithm works, the program will re-open the compressed file and perform the de-compression, using the Huffman binary tree.
9) The name of the de-compressed file is also to be created at run-time.
