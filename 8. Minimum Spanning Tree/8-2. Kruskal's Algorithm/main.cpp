#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class uEdge
{
friend class KruskalMST;

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

class KruskalMST
{		
public:
  int numNodes;
  int nodeInSetA;
  int* whichSet; // a 1-D integer array, size of numNodes +1, dynamically allocated.
  int totalMSTCost;
  uEdge* edgelistHead;
  uEdge* MSTlistHead;

  KruskalMST(int n) {
    numNodes = n;
    whichSet = new int[numNodes+1];
    edgelistHead = new uEdge(0, 0, 0);
    MSTlistHead = new uEdge(0, 0, 0);
    totalMSTCost = 0;
  }
  void initSets() {
    for (int i=1; i<=numNodes; i++) {
      whichSet[i]=i;
    }
  }
  void listInsert(uEdge* edge) {
    uEdge* tmp = edgelistHead;
    while (tmp->next != NULL && tmp->next->cost < edge->cost) {
      tmp = tmp->next;
    }
    edge->next = tmp->next;
    tmp->next = edge;
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
  uEdge* removeEdge() {
    uEdge* ePrev = edgelistHead;
    uEdge* e = edgelistHead->next;
    while (e != NULL) {
      if (whichSet[e->Ni]!=whichSet[e->Nj]) {
        break;
      }
      ePrev = e;
      e = e->next;
    }
    if (e==NULL) return NULL;
    else ePrev->next = ePrev->next->next;
    return e;
  }
  void merge2sets(uEdge* edge) {
    int x = whichSet[edge->Ni];
    int y = whichSet[edge->Nj];
    for (int i = 1; i <= numNodes; i++) {
      if (whichSet[i] == x || whichSet[i] == y) {
        if (x < y) {
          whichSet[i] = x;
        }
        else {
          whichSet[i] = y;
        }
      }
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
  bool oneSet() {
    for (int i=1; i<=numNodes-1; i++) {
      if (whichSet[i] != whichSet[i+1]) return false;
    }
    return true;
  }
  void printMST(ostream &outFile) {
    uEdge* tmp = MSTlistHead->next;
    outFile << numNodes << endl;
    while (tmp->next != NULL) {
      outFile << tmp->Ni << " " << tmp->Nj << " " << tmp->cost << endl;
      tmp = tmp->next;
    }
    outFile << tmp->Ni << " " << tmp->Nj << " " << tmp->cost << endl;
  }

};

int main(int argc, char* argv[])
{
  ifstream inFile;
  ofstream MSTfile, deBugFile;

  // inFile.open("Q61_Data.txt");
  inFile.open(argv[1]);
  // MSTfile.open("MSTfile.txt");
  MSTfile.open(argv[2]);
  // deBugFile.open("deBugFile.txt");
  deBugFile.open(argv[3]);
  int numNodes;
  inFile >> numNodes;

  KruskalMST P(numNodes);
  P.initSets();

  deBugFile << "*** Printing the whichSet:\n";
  P.printSet(deBugFile);

  string Ni, Nj, edgeCost;
  while (inFile >> Ni >> Nj >> edgeCost) {
    uEdge* newEdge = new uEdge(stoi(Ni), stoi(Nj), stoi(edgeCost));
    P.listInsert(newEdge);
  }
  deBugFile << "\n*** Printing Edge List:\n";
  P.printEdgeList(deBugFile);

  while (!P.oneSet()) {
    deBugFile << "\n=======================================\n";
    uEdge* newEdge = P.removeEdge();
    newEdge->printEdge(newEdge, deBugFile);
    P.addEdge(newEdge);
    P.totalMSTCost += newEdge->cost;
    cout << newEdge->Ni << "-->" << newEdge->Nj << endl;
    P.merge2sets(newEdge);

    deBugFile << "\n*** Printing the whichSet:\n";
    P.printSet(deBugFile);
    deBugFile << "\n*** Printing Edge List:\n";
    P.printEdgeList(deBugFile);
    deBugFile << "\n*** Printing MST List:\n";
    P.printMSTList(deBugFile);
  }

  MSTfile << "*** Kruskal's MST of the input graph is given below: ***\n";
  P.printMST(MSTfile);
  MSTfile << "\n*** The total cost of a Kruskal\'s MST is " << P.totalMSTCost;

  inFile.close();
  MSTfile.close();
  deBugFile.close();
  return 0;
}