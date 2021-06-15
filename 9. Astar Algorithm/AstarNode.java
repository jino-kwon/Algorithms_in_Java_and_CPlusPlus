import java.io.*;

class AstarNode
{
  public int[] configuration;
  public int gStar;
  public int hStar;
  public int fStar;
  public AstarNode parent;
  public AstarNode next;

  public AstarNode() {
    fStar = -999;
  }

  public void swap(int i, int j, int[] array) {
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
  }

  public void printNode(AstarNode A, FileWriter outFile) throws IOException {
    String s = "( " + A.fStar + " :: ";

    for (int i=0; i<9; i++)
      s += A.configuration[i] + " ";
      
    s += ":: ";

    if (A.parent != null) {
      for (int i=0; i<9; i++)
      s += A.parent.configuration[i] + " ";
    } else {
      s += "NULL ";
    }
    s += ")-->\n";
    outFile.write(s);
    outFile.flush();
  }
}



  
