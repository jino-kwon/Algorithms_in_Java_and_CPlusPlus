import java.io.*;

class treeNode
{
    public int data;
    public treeNode left;
    public treeNode right;

    public treeNode(int d) {
        this.data = d;
    }

    public void printNode(treeNode T, FileWriter outFile) throws IOException {
        String s = "(Node: " + T.data + ", ";
        if (T.left != null) {
            s += "Left: " + T.left.data; 
        } else {
            s += "Left: NULL";
        }
        if (T.right != null) {
            s += ", Right: " + T.right.data; 
        } else {
            s += ", Right: NULL";
        }
        s += ")-->\n";
        outFile.write(s);
    }
}
