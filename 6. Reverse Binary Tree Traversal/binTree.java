import java.io.*;
import java.util.Scanner;

class binTree
{
    public int num;
    public int[] intAry;

    public binTree() {
        num = 0;
    };

    public int readCheck(Scanner inFile) {
        int max = 9999;
        int i;
        while (inFile.hasNext()) {
            i = inFile.nextInt();
            if (i < max) {
                num++;
                // System.out.println(i);
                max = i;
            } else {
                return -1;
            }
        }
        return num;
    }

    public void loadAry(Scanner inFile, int[] inAry) {
        int i=0;
        while (inFile.hasNext()) {
            int data = inFile.nextInt();
            inAry[i] = data;
            i++;
        }
    }

    public void printAry(int[] inAry, FileWriter outFile) throws IOException {
        outFile.write("\n*** Printing the inAry\n");
        for (int i=0; i<num; i++) {
            outFile.write(inAry[i] + " ");
            outFile.flush();
        }
    }

    public treeNode BuildBinTree(int[] inAry, int leftIdx, int rightIdx) {
        if (leftIdx >= rightIdx) return null;

        int mid = (leftIdx+rightIdx)/2;
        treeNode newNode = new treeNode(inAry[mid]);
        newNode.left = BuildBinTree(inAry, leftIdx, mid-1);
        newNode.right = BuildBinTree(inAry, mid+1, rightIdx);
        return newNode;
    }

    public boolean isLeaf(treeNode node) {
        return (node.left == null && node.right == null);
    }

    public void preOrderTraversal(treeNode T, FileWriter outFile) throws IOException {
        if (isLeaf(T)) {
            T.printNode(T, outFile);
        } else {
            T.printNode(T, outFile);
            this.preOrderTraversal(T.left, outFile);
            this.preOrderTraversal(T.right, outFile);
        }
    }
    public void inOrderTraversal(treeNode T, FileWriter outFile) throws IOException {
        if (isLeaf(T)) {
            T.printNode(T, outFile);
        } else {
            this.inOrderTraversal(T.left, outFile);
            T.printNode(T, outFile);
            this.inOrderTraversal(T.right, outFile);
        }
    }
    public void postOrderTraversal(treeNode T, FileWriter outFile) throws IOException {
        if (isLeaf(T)) {
            T.printNode(T, outFile);
        } else {
            this.postOrderTraversal(T.left, outFile);
            this.postOrderTraversal(T.right, outFile);
            T.printNode(T, outFile);
        }
    }
}
