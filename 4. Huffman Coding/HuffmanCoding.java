import java.io.*;
import java.util.Scanner;

class HuffmanCoding
{
    class treeNode
    {
        public String chStr;
        public int frequency;
        public String code;
        public treeNode left;
        public treeNode right;
        public treeNode next;

        public treeNode(String chStr, int frequency, String code, treeNode left, treeNode right, treeNode next) {
            this.chStr = chStr;
            this.frequency = frequency;
            this.code = code;
            this.left = left;
            this.right = right;
            this.next = next;
        }
        public void printNode(treeNode T, FileWriter DebugFile) throws IOException {
            String s = "(chStr: " + T.chStr + ", frequency: " + T.frequency + ", code: " + T.code;
            if (T.next != null) {
                s += ", next: " + T.next.chStr; 
            } else {
                s += ", next: NULL";
            }
            if (T.left != null) {
                s += ", left: " + T.left.chStr; 
            } else {
               s += ", left: NULL";
            }
            if (T.right != null) {
               s += ", right: " + T.right.chStr; 
            } else {
               s += ", right: NULL";
            }
            s += ")-->\n";
            DebugFile.write(s);
        }
    }
    class linkedList
    {
        public void insertNewNode(treeNode listHead, treeNode newNode) {
            treeNode tmp = listHead;
            while (tmp.next != null && tmp.next.frequency < newNode.frequency) {
                tmp = tmp.next;
            }
            newNode.next = tmp.next;
            tmp.next = newNode;
        }
        public void printList(treeNode listHead, FileWriter DebugFile) throws IOException {
            treeNode tmp = listHead;
            DebugFile.write("listHead-->");
            while (tmp != null && tmp.next != null) {
                tmp.printNode(tmp, DebugFile);
                tmp = tmp.next;
            }
            tmp.printNode(tmp, DebugFile);
            DebugFile.write("----------    End    ----------\n");
        }
    }
    class BinaryTree
    {
        public  treeNode Root;
        public BinaryTree() {
            Root = null;
        }
        public boolean isLeaf(treeNode node) {
            return (node.left == null && node.right == null);
        }
        public void preOrderTraversal(treeNode T, FileWriter DebugFile) throws IOException {
            if (isLeaf(T)) {
                T.printNode(T, DebugFile);
            } else {
                T.printNode(T, DebugFile);
                this.preOrderTraversal(T.left, DebugFile);
                this.preOrderTraversal(T.right, DebugFile);
            }
        }
        public void inOrderTraversal(treeNode T, FileWriter DebugFile) throws IOException {
            if (isLeaf(T)) {
                T.printNode(T, DebugFile);
            } else {
                this.inOrderTraversal(T.left, DebugFile);
                T.printNode(T, DebugFile);
                this.inOrderTraversal(T.right, DebugFile);
            }
        }
        public void postOrderTraversal(treeNode T, FileWriter DebugFile) throws IOException {
            if (isLeaf(T)) {
                T.printNode(T, DebugFile);
            } else {
                this.postOrderTraversal(T.left, DebugFile);
                this.postOrderTraversal(T.right, DebugFile);
                T.printNode(T, DebugFile);
            }
        }
    }

    public int[] charCountAry = new int[256];
    public String[] charCode = new String[256];
    public treeNode HuffmanListHead = new treeNode("dummy",0,"",null,null,null);

    public void computeCharCounts(Scanner inFile, int[] charCountAry) {
        while (inFile.hasNextLine()) {
            String line = inFile.nextLine();
            for (int i=0; i<line.length(); i++) {
                int ch = line.charAt(i);
                if (0 <= ch && ch <= 255) {
                  charCountAry[ch]++;
                }
            }
        }
    }
    public void printCountAry(int[] charCountAry, FileWriter DebugFile) throws IOException {
        DebugFile.write("\n*** Printing the chracter count array:\n");
        for (int i=0; i<charCountAry.length; i++) {
            if (charCountAry[i] > 0) {
                String s = (char)i + " : " + charCountAry[i] + "\n";
                DebugFile.write(s);
            }
        }
    }
    public void constructHuffmanLList(int[] charCountAry, FileWriter DebugFile) throws IOException {
        linkedList L = new linkedList();
        DebugFile.write("\n*** Constructing a Huffman Linked List:\n");
        for (int index=0; index<256; index++) {
            if (charCountAry[index]>0) {
                String chr = Character.toString(index);
                int prob = charCountAry[index];
                treeNode newNode = new treeNode(chr,prob,"",null,null,null);
                L.insertNewNode(HuffmanListHead, newNode);
                L.printList(HuffmanListHead, DebugFile);
            }
        }
    }
    public void constructHuffmanBinTree(treeNode listHead, FileWriter DebugFile) throws IOException {
        treeNode currentNode = listHead;
        currentNode = currentNode.next;
        linkedList L = new linkedList();
        while (currentNode.next != null) {
            String newChStr = currentNode.chStr+currentNode.next.chStr;
            int newProb = currentNode.frequency+currentNode.next.frequency;
            treeNode newLeft = currentNode;
            treeNode newRight = currentNode.next;
            treeNode newNext = null;
            treeNode newNode = new treeNode(newChStr,newProb,"",newLeft,newRight,newNext);
            L.insertNewNode(currentNode, newNode);
            currentNode = currentNode.next.next;
            listHead.next = currentNode;
            DebugFile.write("\n*** Constructing a Huffman Binary Tree:\n");
            L.printList(listHead, DebugFile);
        }
        DebugFile.write("\n*** Huffman Binary Tree is constructed:\n");
        L.printList(HuffmanListHead, DebugFile);
    }
    public void constructCharCode(treeNode T, String code) {
        BinaryTree Tree = new BinaryTree();
        if (Tree.isLeaf(T)) {
            T.code = code;
            int index = T.chStr.charAt(0);
            charCode[index] = code;
            // System.out.println(T.chStr+" |index: "+index+" |code: " +charCode[index]);
        } else {
            constructCharCode(T.left, code+"0");
            constructCharCode(T.right, code+"1");
        }
    }
    public void userInterface() throws IOException {
        String nameOrg;
        String nameCompress;
        String nameDeCompress;
        char yesNo;

        Scanner scan = new Scanner(System.in);
        System.out.println("Do you want to encode a file? (y/n)");
        yesNo = scan.nextLine().charAt(0);
        while (!(yesNo == 'N' || yesNo == 'n')) {
            System.out.println("What is the name of the file? (without .txt)");
            nameOrg = scan.nextLine();

            nameCompress = nameOrg+"_Compressed.txt";
            nameDeCompress = nameOrg+"_DeCompressed.txt";
            nameOrg = nameOrg+".txt";

            Scanner orgFile = new Scanner(new FileReader(nameOrg));
            FileWriter compFile = new FileWriter(nameCompress);
            FileWriter deCompFile = new FileWriter(nameDeCompress);
            Encode(orgFile, compFile);
            compFile.close();

            Scanner compfile = new Scanner(new FileReader(nameCompress));
            Decode(compfile, deCompFile);
            
            orgFile.close();
            compfile.close();
            deCompFile.close();

            System.out.println("Do you want to encode a file? (y/n)");
            yesNo = scan.nextLine().charAt(0);
        }
        scan.close();
    }
    public void Encode(Scanner inFile, FileWriter outFile) throws IOException {
        FileWriter deBugFile = new FileWriter("EncodeDebug.txt");
        while (inFile.hasNextLine()) {
            String line = inFile.nextLine();
            for (int i=0; i<line.length(); i++) {
                int index = line.charAt(i);
                String code = charCode[index] + "\n";
                String output = "index: "+index+"| code: "+code;
                deBugFile.write(output);
                outFile.write(code);
            }
        }
        outFile.flush();
        deBugFile.flush();
        deBugFile.close();
    }
    public void Decode(Scanner inFile, FileWriter outFile) throws IOException {
        BinaryTree Tree = new BinaryTree();
        treeNode Spot = HuffmanListHead.next;
        while (inFile.hasNextLine()) {
            if (Tree.isLeaf(Spot)) {
                outFile.write(Spot.chStr);
                Spot = HuffmanListHead.next;
            }
            String line = inFile.nextLine();
            for (int i=0; i<line.length(); i++) {
                char oneBit = line.charAt(i);
                if (oneBit == '0') { Spot = Spot.left; }
                else if (oneBit == '1') { Spot = Spot.right; }
                else {
                    outFile.write("Error! The compress file contains invalid character!\n");
                    return;
                }
            }
        }
        outFile.write(Spot.chStr+"\n");
        if (!Tree.isLeaf(Spot)) {
            outFile.write("Error: The compress file is corrupted!\n");
        }
        outFile.flush();
    }
    
}