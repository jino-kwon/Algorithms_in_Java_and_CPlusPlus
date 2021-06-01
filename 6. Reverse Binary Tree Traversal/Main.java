import java.io.*;
import java.util.Scanner;

class Main
{
    public static void main(String[] args) {
        Scanner inFile;
        FileWriter treeFile, deBugFile;
        try {
            inFile = new Scanner(new FileReader(args[0]));
            treeFile = new FileWriter(args[1]);
            deBugFile = new FileWriter(args[2]);

            binTree B = new binTree();
            int num = B.readCheck(inFile);
            deBugFile.write("Number of data in the input file: " + num + "\n");
            if (num < 0) {
                deBugFile.write("Integers in the input file is not sorted");
                deBugFile.flush();
                System.exit(0);
            }
            inFile.close();
            inFile = new Scanner(new FileReader(args[0]));

            int[] inAry = new int[num];
            B.loadAry(inFile, inAry);
            B.printAry(inAry, deBugFile);

            treeNode root = B.BuildBinTree(inAry, 0, num-1);
            treeFile.write("*** Preorder Traversal: \n");
            B.preOrderTraversal(root, treeFile);
            treeFile.write("\n*** Inorder Traversal: \n");
            B.inOrderTraversal(root, treeFile);
            treeFile.write("\n*** Postorder Traversal: \n");
            B.postOrderTraversal(root, treeFile);
            
            // close all files
            treeFile.flush();
            deBugFile.flush();
            inFile.close();
            treeFile.close();
            deBugFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
