import java.io.*;
import java.util.Scanner;

class Main
{
    public static void main(String[] args) {
        Scanner inFile1, inFile2;
        FileWriter outFile1, outFile2;
        try {
            inFile1 = new Scanner(new FileReader(args[0]));
            inFile2 = new Scanner(new FileReader(args[1]));
            outFile1 = new FileWriter(args[3]);
            outFile2 = new FileWriter(args[4]);

            int numNodes = inFile1.nextInt();
            int numProcs = inFile2.nextInt();
            numProcs = Integer.parseInt(args[2]);
            if (numProcs <= 0) {
                System.out.println("Need 1 or more processors!");
                System.exit(0);
            } else if (numProcs > numNodes) {
                numProcs = numNodes; // means unlimited processors
            }
            Schedule S = new Schedule(numNodes, numProcs);
            int currentTime = 0;
            int procUsed = 0;

            S.loadMatrix(inFile1);
            int totalJobTimes = S.loadJobTimeAry(inFile2);
            int[][] Table = new int[numProcs+1][totalJobTimes+1];
            S.Table = Table;
            S.printTable(outFile1, currentTime);
            
            S.setMatrix();
            S.printMatrix(outFile2); //for debugging

            while (!S.isGraphEmpty()) {
                int jobID = S.findOrphan();
                while (jobID > 0) {
                    Node newNode = new Node(jobID, S.jobTimeAry[jobID], null);
                    S.OpenInsert(newNode);
                    S.printOPEN(outFile2);
                    jobID = S.findOrphan();
                }

                int availProc = S.getNextProc(currentTime);
                while (availProc>0 && S.OPEN.next!=null && procUsed<numProcs) {
                    if (availProc >= 0){
                    procUsed++;
                    Node newJob = S.OPEN.next;
                    S.OPEN.next = S.OPEN.next.next;
                    S.putJobOnTable(availProc, currentTime, newJob.jobID, newJob.jobTime);
                    availProc = S.getNextProc(currentTime);
                    }
                }
                S.procUsed = procUsed;
                S.printTable(outFile1, currentTime);
                
                S.currentTime = currentTime;
                boolean hasCycle = S.checkCycle();
                if (hasCycle) {
                    System.out.println("There is a cycle in the graph!!!");
                    System.exit(0);
                }
                currentTime++;
                int proc = 1;
                while (proc <= numProcs) {
                    if (Table[proc][currentTime]<=0 && Table[proc][currentTime-1]>0) {
                        jobID = Table[proc][currentTime-1];
                        S.deleteJob(jobID);
                        procUsed--;
                    }
                    S.printMatrix(outFile2);
                    proc++;
                }
                S.procUsed = procUsed;
            }
            outFile1.write("\n*** Final Results:\n");
            S.printTable(outFile1, currentTime);

            // close all files
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