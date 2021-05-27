import java.io.*;
import java.util.Scanner;

class Main
{
    public static void main(String[] argv) {
        Scanner inFile;
        FileWriter DebugFile;
        try {
            // String nameInFile = argv[0];
            String nameInFile = "data.txt";
            // inFile = new Scanner(new FileReader(argv[0]));
            inFile = new Scanner(new FileReader("data.txt"));
            String nameDebugFile = nameInFile + "_DeBug.txt";
            DebugFile = new FileWriter(nameDebugFile);

            HuffmanCoding H = new HuffmanCoding();
            HuffmanCoding.BinaryTree myTree = H.new BinaryTree();
            
            H.computeCharCounts(inFile, H.charCountAry);
            H.printCountAry(H.charCountAry, DebugFile);
            H.constructHuffmanLList(H.charCountAry, DebugFile);
            H.constructHuffmanBinTree(H.HuffmanListHead, DebugFile);
            H.constructCharCode(H.HuffmanListHead.next, "");
            DebugFile.write("\n*** Preorder Traversal\n");
            myTree.preOrderTraversal(H.HuffmanListHead.next, DebugFile);
            DebugFile.write("\n*** Inorder Traversal\n");
            myTree.inOrderTraversal(H.HuffmanListHead.next, DebugFile);
            DebugFile.write("\n*** Postorder Traversal\n");
            myTree.postOrderTraversal(H.HuffmanListHead.next, DebugFile);
            H.userInterface();

            DebugFile.flush();
            inFile.close();
            DebugFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}