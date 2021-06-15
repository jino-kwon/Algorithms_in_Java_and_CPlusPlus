import java.io.*;
import java.util.Scanner;

class Main
{
  public static void main(String[] argv) {
    Scanner inFile1, inFile2;
    FileWriter outFile1, outFile2;
    try {
      // inFile1 = new Scanner(new FileReader(argv[0]));
      inFile1 = new Scanner(new FileReader("Data1.txt"));
      // inFile2 = new Scanner(new FileReader(argv[1]));
      inFile2 = new Scanner(new FileReader("Data2.txt"));
      // outFile1 = new FileWriter(args[2]);
      outFile1 = new FileWriter("DeBug.txt");
      // outFile2 = new FileWriter(args[3]);
      outFile2 = new FileWriter("Output.txt");

      AstarNode OpenList = new AstarNode();
      AstarNode CloseList = new AstarNode();
      
      Astar A = new Astar();
      int[] initialConfiguration = new int[9];
      A.loadAry(inFile1, initialConfiguration);
      int[] goalConfiguration = new int[9];
      A.loadAry(inFile2, goalConfiguration);

      AstarNode startNode = new AstarNode(); 
      startNode.configuration = initialConfiguration;
      AstarNode goalNode = new AstarNode();
      goalNode.configuration = goalConfiguration;

      startNode.gStar = 0;
      startNode.hStar = A.computeHstar(startNode, goalNode);
      startNode.fStar = startNode.gStar + startNode.hStar;
      A.listInsert(startNode, OpenList);

      outFile1.write("------------Initial State------------\n");
      outFile1.write("\n*** This is Open List:\n");
      A.printList(OpenList, outFile1);
      outFile1.write("\n*** This is Close List:\n");
      A.printList(CloseList, outFile1);
      outFile1.write("-------------------------------------\n");

      AstarNode currentNode;
      do {
        currentNode = A.remove(OpenList);
        if (A.isGoalNode(currentNode, goalNode)) {
          A.printSolution(currentNode, outFile2);
          System.exit(0);
        }
        // Since currentNode is NOT a goal node, put in a CloseList
        currentNode.next = CloseList.next;
        CloseList.next = currentNode;

        AstarNode childList = A.constructChildList(currentNode);
        while (childList.next != null) {
          AstarNode child = A.remove(childList);
          child.gStar = A.computeGstar(child);
          child.hStar = A.computeHstar(child, goalNode);
          child.fStar = child.gStar + child.hStar;

          // A.listInsert(child, OpenList);
          
          if (!A.containNode(child, OpenList) && !A.containNode(child, CloseList)) {
            A.listInsert(child, OpenList);
          } else if (A.containNode(child, OpenList)) {
            A.listInsert(child, OpenList);
          } else if (A.containNode(child, CloseList)) {
            A.listInsert(child, OpenList);
          }

          outFile1.write("\n*** This is Open List:\n");
          A.printList(OpenList, outFile1);
          outFile1.write("\n*** This is Close List:\n");
          A.printList(CloseList, outFile1);
          outFile1.write("\n-------------------------------------\n");
        }
      } while (OpenList.next != null && !A.isGoalNode(currentNode, goalNode));

      if (OpenList.next == null && !A.isGoalNode(currentNode, goalNode)) {
        outFile2.write("\nno solution can be found in the search!\n");
      }

      outFile1.flush();
      outFile2.flush();
      inFile1.close();
      inFile2.close();
      outFile1.close();
      outFile2.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}