import java.io.*;
import java.util.Scanner;

class Schedule
{
    public int numNodes;
    public int numProcs;
    public int procUsed; // number of processors used so far; initialized to 0.
    public int currentTime; // initialize to 0.
    public int totalJobTime; // the total job times of nodes in the graph
    public int[] jobTimeAry; // an 1D array to store the job time of each node in the graph; to be dynamically allocated, size of numNodes +1; initialied to 0.
    public Node OPEN;

    public int[][] adjMatrix;
    public int[][] Table;

    public Schedule(int numNodes, int numProcs) {
        this.numNodes = numNodes;
        this.numProcs = numProcs;
        this.procUsed = 0;
        this.totalJobTime = 0;
        this.jobTimeAry = new int[numNodes+1];
        this.adjMatrix = new int[numNodes+1][numNodes+1];
        this.OPEN = new Node(9999,-1,null);
    }
    public void loadMatrix(Scanner inFile) {
        while (inFile.hasNext()) {
            int i = inFile.nextInt();
            int j = inFile.nextInt();
            adjMatrix[i][j]++;
        }
    }
    public int loadJobTimeAry(Scanner inFile) {
        while (inFile.hasNext()) {
            int jobID = inFile.nextInt();
            int time = inFile.nextInt();
            jobTimeAry[jobID] = time;
            totalJobTime += time;
        }
        return totalJobTime;
    }
    public void setMatrix() {
        int dependentCount;
        int parentCount;

        for (int i=1; i<=numNodes; i++) {
            dependentCount = 0;
            for (int j=1; j<=numNodes; j++) {
                dependentCount += adjMatrix[i][j];
            }
            adjMatrix[i][0] = dependentCount;
        }
        for (int j=1; j<=numNodes; j++) {
            parentCount = 0;
            for (int i=1; i<=numNodes; i++) {
                parentCount += adjMatrix[i][j];
            }
            adjMatrix[0][j] = parentCount;
        }
        for (int i=1; i<=numNodes; i++) {
            adjMatrix[i][i] = 1;
        }
        adjMatrix[0][0] = numNodes;
    }
    public void printMatrix(FileWriter outFile) throws IOException {
        outFile.write("*** Printing the adjMatrix:\n");
        for (int i=0; i<=numNodes; i++) {
            for (int j=0; j<=numNodes; j++) {
                if (j==numNodes) {
                    outFile.write(adjMatrix[i][j]+"\n");
                } else {
                    if (adjMatrix[i][j]<10) outFile.write(adjMatrix[i][j]+" | ");
                    else outFile.write(adjMatrix[i][j]+"| ");
                }
            }
            outFile.write("---------------------------------------------------------\n");
        }
    }
    public int findOrphan() {
        for (int j=1; j<=numNodes; j++) {
            if (adjMatrix[0][j]==0 && adjMatrix[j][j]==1) {
                // now node j is marked
                adjMatrix[j][j] = 2;
                return j;
            }
        }
        return -1;
    }
    public void OpenInsert(Node newNode) {
        Node tmp = OPEN;
        while (tmp.next != null && adjMatrix[tmp.next.jobID][0] > adjMatrix[newNode.jobID][0]) {
            tmp = tmp.next;
        }
        newNode.next = tmp.next;
        tmp.next = newNode;
    }
    public void printOPEN(FileWriter outFile) throws IOException {
        Node tmp = OPEN.next;
        outFile.write("\n*** Printing the OPEN linked list:\n");
        outFile.write("OPEN-->");
        while (tmp != null && tmp.next != null) {
            outFile.write("(jobID: "+tmp.jobID+" | jobTime: "+tmp.jobTime+")-->");
            tmp = tmp.next;
        }
        outFile.write("(jobID: "+tmp.jobID+" | jobTime: "+tmp.jobTime+")");
        outFile.flush();
    }
    public int getNextProc(int currentTime) {
        for (int i=1; i<=numProcs; i++) {
            if (Table[i][currentTime]==0) return i;
        }
        return -1;
    }
    public void putJobOnTable(int availProc, int currentTime, int jobID, int jobTime) {
        int Time = currentTime;
        int EndTime = Time+jobTime;
        while (Time<EndTime) {
            Table[availProc][Time] = jobID;
            Time++;
        }
    }
    public void printTable(FileWriter outFile, int currentTime) throws IOException {
        outFile.write("*** Print Current Table:\n");
        outFile.write("=============================================================\n");
        outFile.write("ProcUsed: "+procUsed+" | currentTime: "+currentTime+"\n");
        String s1="     | ";
        for (int i=0; i<=currentTime; i++) {
            if (i<10) s1 += i + "  | ";
            else s1 += i + " | ";
        }
        for (int i=1; i<=numProcs; i++) {
            s1 +=("\n------------------------------------------------------------\n");
            if (i<10) s1 += "P("+i+") | ";
            else s1 += "P("+i+")| ";
            for (int j=0; j<=currentTime; j++) {
                if (Table[i][j]==0) s1 += "-  | ";
                else {
                    if (Table[i][j]<10) s1 += Table[i][j] + "  | ";
                    else s1 += Table[i][j] + " | ";
                }
            }
        }
        outFile.write(s1+"\n\n");
        outFile.flush();
    }
    public boolean checkCycle() {
        return (OPEN.next==null && !isGraphEmpty() && procUsed==0);
    }
    public boolean isGraphEmpty() {
        return (adjMatrix[0][0]==0);
    }
    public void deleteJob(int jobID) {
        adjMatrix[jobID][jobID] = 0;
        adjMatrix[0][0]--;
        int j = 1;
        while (j<=numNodes) {
            if (adjMatrix[jobID][j]>0) {
                adjMatrix[0][j]--;
            }
            j++;
        }
    }
}