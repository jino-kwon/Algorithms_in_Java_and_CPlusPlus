# 4. Huffman Coding

**Program Specs**:

The Huffman Coding Scheme is implemented -- from compute frequency to text compression / decompression.
1) Open the input text file and count the characters counts.
2) Construct a Huffman linked list based on the character counts.
3) Construct a Huffman binary tree (to be used for decoding later), and then construct a Huffman code array (for encoding).
4) Ask the user if they want to compress a text file (Y/N).

If yes,

5) Ask the user for the name of a text file to be compressed.
6) Open the text file to be compressed.
7) Call the encoding method to perform compression on the text file using the Huffman code table, and output the results.
10) The name of the compressed file is to be created at run-time, using the original file name with an extension “_Compressed.txt”. For example, if the name of the file is “test1”, the name of the compressed file should be “test1_Compressed.txt”. (This can be done simply using string concatenation.)
11) Close the compressed file.
12) To make sure your encoding method works correctly, your program will re-open the compressed file (after it is closed) and call Decode(...) method to perform the de-compression, using the Huffman binary tree. Your program outputs the de-compressed result to a de-compressed text file.
13) The name of the de-compressed file is to be created at run-time, using the original file name with an extension “_deCompressed.txt”. For example, if the name of the original text is “test1”, then the name of the de-compressed file should be “test1_deCompressed.txt”.
