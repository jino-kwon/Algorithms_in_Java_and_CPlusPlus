import java.io.*;
import java.util.Scanner;

class Astar
{
  public int computeGstar(AstarNode node) {
    if (node.parent == null) return 1;
    return node.parent.gStar + 1;
  }
  public int computeHstar(AstarNode node, AstarNode goalNode) {
    int hStar = 0;
    for (int i=0; i<9; i++) {
      if (node.configuration[i]==0) continue;
      for (int j=0; j<9; j++) {
        if (node.configuration[i]==goalNode.configuration[j]) {
          hStar += (Math.abs(i/3 - j/3) + Math.abs(i%3 - j%3));
          break;
        }
      }
    }
    return hStar;
  }
  public void loadAry(Scanner inFile, int[] inAry) {
    int i = 0;
    while (inFile.hasNext()) {
      int data = inFile.nextInt();
      inAry[i] = data;
      i++;
    }
  }
  public boolean match(int[] configuration1, int[] configuration2) {
    for (int i=0; i<9; i++) {
      if (configuration1[i] != configuration2[i])
        return false;
    }
    return true;
  }
  public boolean isGoalNode(AstarNode node, AstarNode goalNode) {
    return match(node.configuration, goalNode.configuration);
  }
  public boolean containNode(AstarNode node, AstarNode nodeList) {
    AstarNode tmp = nodeList;
    while (tmp.next != null) {
      if (match(tmp.next.configuration, node.configuration) && node.fStar<tmp.next.fStar) {
        tmp.next = tmp.next.next;        
        return true;
      }
      tmp = tmp.next;
    }
    return false;
  }
  public void listInsert(AstarNode newNode, AstarNode NodeList) {
    AstarNode tmp = NodeList;
    while (tmp.next != null && tmp.next.fStar < newNode.fStar) {
      tmp = tmp.next;
    }
    newNode.next = tmp.next;
    tmp.next = newNode;
  }
  public AstarNode remove(AstarNode NodeList) {
    AstarNode nodeToDelete = NodeList.next;
    NodeList.next = NodeList.next.next;
    return nodeToDelete;
  }
  public AstarNode delete(AstarNode NodeList) {
    AstarNode nodeToDelete = NodeList.next;
    NodeList.next = NodeList.next.next;
    return nodeToDelete;
  }
  public boolean checkAncestors(AstarNode currentNode) {
    AstarNode tmp = currentNode.parent;
    while (tmp != null) {
      if (match(currentNode.configuration, tmp.configuration)) { return true; }
      tmp = tmp.parent;
    }
    return false;
  }
  public void constructHelper(AstarNode childList, AstarNode currentNode, int blankIdx, int idx) {
    AstarNode tmpNode = new AstarNode();
    tmpNode.configuration = currentNode.configuration.clone();
    tmpNode.swap(blankIdx, blankIdx+idx, tmpNode.configuration);
    tmpNode.parent = currentNode;
    if (!checkAncestors(tmpNode)) {
      listInsert(tmpNode, childList);
    }
  }
  public AstarNode constructChildList(AstarNode currentNode) {
    int blankIdx=-1;
    AstarNode childList = new AstarNode();
    for (int i=0; i<9; i++) {
      if (currentNode.configuration[i]==0) {
        blankIdx = i;
      }
    }
    if (blankIdx/3 < 2) {
      constructHelper(childList, currentNode, blankIdx, 3);
    }
    if (blankIdx/3 > 0) {
      constructHelper(childList, currentNode, blankIdx, -3);
    }
    if (blankIdx%3 < 2) {
      constructHelper(childList, currentNode, blankIdx, 1);
    }
    if (blankIdx%3 > 0) {
      constructHelper(childList, currentNode, blankIdx, -1);
    }
    return childList;
  }
  public void printList(AstarNode listHead, FileWriter outFile1) throws IOException {
    AstarNode tmp = listHead.next;
    int count = 1;
    while (tmp != null && tmp.next != null && count<30) {
      tmp.printNode(tmp, outFile1);
      tmp = tmp.next;
      count++;
    }
    if (tmp != null) {
      tmp.printNode(tmp, outFile1);
    }
    else {
      outFile1.write("NULL\n");
    }
    if (count == 30) {
      outFile1.write("Printed up to 30 loops!!!\n");
    }
    outFile1.flush();
  }
  public void printSolution(AstarNode node, FileWriter outFile2) throws IOException {
    AstarNode tmp = node;
    String[] solution = new String[30];
    int count = 0;
    while (tmp.parent != null) {
      String s = "";
      for (int i=0; i<9; i++) {
        if (i%3 == 2) {
          s += tmp.configuration[i] + "\n";
        } else {
          s += tmp.configuration[i] + " ";
        }
      }
      solution[count] = s;
      count++;
      tmp = tmp.parent;
    }
    String s = "";
    for (int i=0; i<9; i++) {
      if (i%3 == 2) {
        s += tmp.configuration[i] + "\n";
      } else {
        s += tmp.configuration[i] + " ";
      }
    }
    solution[count] = s;
    
    count = 0;
    for (int i=solution.length-1; i>=0; i--) {
      if (solution[i] != null) {
        outFile2.write("Move "+count+":\n");
        outFile2.write(solution[i]);
        outFile2.write("\n---------------------\n");
        count ++;
      }
    }

    outFile2.flush();
  }

}