# 6. (REVIEW) Reverse Binary Tree Traversal

**Program Specs:**

You will be given a text file that contains a list of sorted positive integers (in descending order. ) You are to write a program to create a balance binary tree from the input sorted list. A node in the binary tree has three members: (data, left, right), where data is (int), left and right are (node) The data in the root of the binary tree is at the mid-point of the input list. The left child of the root is the mid-point of the left half of the input list and the right child of the root is the mid-point of the right half of the input list. So for, recursively, until there is only one integer remains in the half, i.e., left equal to right. After the tree is build, your program will perform pre-order, in-order and post-order traversals from the root and output the three traversals to outFile1. All debugging statement will be in a separate file, deBugFile. See specs below
