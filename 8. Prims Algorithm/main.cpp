#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class uEdge
{
friend class PrimMST;

public:
  int Ni; // an integer 1 to N
  int Nj; // an integer 1 to N
  int cost; // a positive integer
  uEdge* next;
    
  uEdge(int i, int j, int c){
    Ni = i;
    Nj = j;
    cost = c;
    next = NULL;
  }	
  ~uEdge() {
    delete next;
  }
  void printEdge(uEdge* edge, ostream &deBugFile) {
    deBugFile << "\n*** newEdge: (" << edge->Ni << ", " << edge->Nj << ", " << edge->cost << ", " << edge->next->Ni << ")\n";
  }
};

class PrimMST
{		
public:
  int numNodes;
  int nodeInSetA;
  int* whichSet; // a 1-D integer array, size of numNodes +1, dynamically allocated.
  // to indicate which set each node belongs to (1 for setA or 2 for setB).
  int totalMSTCost;
  uEdge* edgelistHead;
  uEdge* MSTlistHead;

  PrimMST(int n, int a) {
    numNodes = n;
    nodeInSetA = a;
    whichSet = new int[numNodes+1];
    for (int i=1; i<=numNodes; i++) whichSet[i]=2; //initialize with 2
    whichSet[nodeInSetA] = 1; //nodeInSetA is in '1'
    edgelistHead = new uEdge(0, 0, 0);
    MSTlistHead = new uEdge(0, 0, 0);
    totalMSTCost = 0;
  }
  void listInsert(uEdge* edge) {
    uEdge* tmp = edgelistHead;
    while (tmp->next != NULL && tmp->next->cost < edge->cost) {
      tmp = tmp->next;
    }
    edge->next = tmp->next;
    tmp->next = edge;
  }
  uEdge* removeEdge() {
    uEdge* ePrev = edgelistHead;
    uEdge* e = edgelistHead->next;
    while (e != NULL) {
      if (whichSet[e->Ni]!=whichSet[e->Nj] && (whichSet[e->Ni]==1 || whichSet[e->Nj]==1)) {
        break;
      }
      ePrev = e;
      e = e->next;
    }
    if (e==NULL) return NULL;
    else ePrev->next = ePrev->next->next;
    return e;
  }
  void addEdge(uEdge* edge) {
    uEdge* tmp = MSTlistHead;
    edge->next = tmp->next;
    tmp->next = edge;
  }
  void printSet(ostream &outFile) {
    for (int i=1; i<=numNodes; i++) {
      outFile << "node " << i << " : " << whichSet[i] << endl;
    }
  }
  void printEdgeList(ostream &outFile) {
    outFile << "edgelistHead-->";
    uEdge* tmp = edgelistHead;
    while (tmp->next != NULL) {
      outFile << "(" << tmp->Ni << ", " << tmp->Nj << ", " << tmp->cost << ", " << tmp->next->Ni << ")-->";
      tmp = tmp->next;
    }
    outFile << "(" << tmp->Ni << ", " << tmp->Nj << ", " << tmp->cost << ", NULL)-->NULL\n";
  }
  void printMSTList(ostream &outFile) {
    outFile << "MSTlistHead-->";
    uEdge* tmp = MSTlistHead;
    while (tmp->next != NULL) {
      outFile << "(" << tmp->Ni << ", " << tmp->Nj << ", " << tmp->cost << ", " << tmp->next->Ni << ")-->";
      tmp = tmp->next;
    }
    outFile << "(" << tmp->Ni << ", " << tmp->Nj << ", " << tmp->cost << ", NULL)-->NULL\n";
  }
  bool setBisEmpty() {
    for (int i=1; i<numNodes; i++) {
      if (whichSet[i] != 1) return false;
    }
    return true;
  }
  void updateMST(uEdge* newEdge) {
    addEdge(newEdge);
    totalMSTCost += newEdge->cost;
    if (whichSet[newEdge->Ni] == 1) whichSet[newEdge->Nj] = 1;
    else whichSet[newEdge->Ni] = 1;
  }
};

int main(int argc, char* argv[])
{
  ifstream inFile;
  ofstream MSTfile, deBugFile;

//   inFile.open("PrimsMST_Data.txt");
  inFile.open(argv[1]);
//   MSTfile.open("MSTfile.txt");
  MSTfile.open(argv[3]);
//   deBugFile.open("deBugFile.txt");
  deBugFile.open(argv[4]);
  int numNodes;
  inFile >> numNodes;

  int nodeInSetA = atoi(argv[2]);

  PrimMST P(numNodes, nodeInSetA);
  deBugFile << "*** Printing the whichSet:\n";
  P.printSet(deBugFile);

  string Ni, Nj, edgeCost;
  while (inFile >> Ni >> Nj >> edgeCost) {
    uEdge* newEdge = new uEdge(stoi(Ni), stoi(Nj), stoi(edgeCost));
    P.listInsert(newEdge);
    deBugFile << "\n*** Printing Edge List:\n";
    P.printEdgeList(deBugFile);
  }

  while (!P.setBisEmpty()) {
    uEdge* nextEdge = P.removeEdge();
    nextEdge->printEdge(nextEdge, deBugFile);

    P.updateMST(nextEdge);
    deBugFile << "\n*** Printing the whichSet:\n";
    P.printSet(deBugFile);
    deBugFile << "\n*** Printing Edge List:\n";
    P.printEdgeList(deBugFile);
    deBugFile << "\n*** Printing MST List:\n";
    P.printMSTList(deBugFile);
  }

  MSTfile << "*** Prim's MST of the input graph, G is: ***\n";
  MSTfile << "Num of Nodes: " << numNodes << endl;
  P.printMSTList(MSTfile);
  MSTfile << "*** MST total cost = " << P.totalMSTCost;

  inFile.close();
  MSTfile.close();
  deBugFile.close();
  return 0;
}