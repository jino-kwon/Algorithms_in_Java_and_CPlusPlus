#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class image
{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int power2Size;
    int** imageArray;

//  constructor
    image(int nr, int nc, int min, int max) {
        numRows = nr;
        numCols = nc;
        minVal = min;
        maxVal = max;
    }
    int computePower2() {
        int size = max(numRows,numCols);
        int power2 = 2;
        while (size > power2) {
            power2 *= 2;
        }
        power2Size = power2;
        return power2;
    }
    void loadImage(ifstream &inFile, int** imgAry) {
        int data;
        int col = 0;
        int row = 0;
        while (inFile >> data) {
            if (col == power2Size-1) {
                imgAry[row][col] = data;
                row += 1;
                col = 0;
            } else {
                imgAry[row][col] = data;
                col += 1;
            }
        }
    }
    void zero2DAry(int** imgAry) {
        for (int i=0; i<power2Size; i++) {
            for (int j=0; j<power2Size; j++) {
                imgAry[i][j] = 0;
            }
        }
    }
};

class QtTreeNode
{
public:
    int color; // 0, 1 or 5
    int upperR;
    int upperC;
    int size;
    QtTreeNode* NWkid = NULL;
    QtTreeNode* NEkid = NULL;
    QtTreeNode* SWkid = NULL;
    QtTreeNode* SEkid = NULL;

//  constructor
    QtTreeNode(int upR, int upC, int s, QtTreeNode* nwKid, QtTreeNode* neKid, QtTreeNode* swKid, QtTreeNode* seKid) {
        upperR = upR;
        upperC = upC;
        size = s;
        NWkid = nwKid;
        NEkid = neKid;
        SWkid = swKid;
        SEkid = seKid;
    }
    void printQtNode(QtTreeNode* node, ofstream &outFile) {
        outFile << "(color: " << node->color << ", upperR: " << node->upperR << ", upperC: " << node->upperC << ", NWkid's color: " << node->NWkid->color << ", NEkid's color: " << node->NEkid->color << ", SWkid's color: " << node->SWkid->color << ", SEkid's color: " << node->SEkid->color << ")-->" << endl;       
    }
};

class QuadTree
{
public:
    QtTreeNode* QtRoot;

    QtTreeNode* buildQuadTree(int** imgAry, int upR, int upC, int size, ofstream &outFile) {
        QtTreeNode newQtNode(upR, upC, size, NULL, NULL, NULL, NULL);
        QtTreeNode* newQtNodePtr = &newQtNode;
        outFile << "New Node: ";
        newQtNodePtr->printQtNode(newQtNodePtr, outFile);
        if (size == 1) {
            newQtNodePtr->color = imgAry[upR][upC];
        } else {
            int halfSize = size/2;
            newQtNode.NWkid = buildQuadTree(imgAry, upR, upC, halfSize, outFile);
            newQtNode.NEkid = buildQuadTree(imgAry, upR, upC+halfSize, halfSize, outFile);
            newQtNode.SWkid = buildQuadTree(imgAry, upR+halfSize, upC, halfSize, outFile);
            newQtNode.SEkid = buildQuadTree(imgAry, upR+halfSize, upC+halfSize, halfSize, outFile);
            int sumColor = newQtNode.NWkid->color + newQtNode.NEkid->color + newQtNode.SWkid->color + newQtNode.SEkid->color;

            if (sumColor == 0) { //newQtNode is a leaf node
                newQtNode.color = 0;
                newQtNode.NWkid = NULL;
                newQtNode.NEkid = NULL;
                newQtNode.SWkid = NULL;
                newQtNode.SEkid = NULL;
            } else if (sumColor == 4) { //all kids are 1
                newQtNode.color = 1;
                newQtNode.NWkid = NULL;
                newQtNode.NEkid = NULL;
                newQtNode.SWkid = NULL;
                newQtNode.SEkid = NULL;
            } else {
                newQtNode.color = 5;
            }
        }
        return newQtNodePtr;
    }
    bool isLeaf(QtTreeNode* Qt) {
        return (Qt->NWkid == NULL && Qt->NEkid == NULL && Qt->SWkid == NULL && Qt->SEkid == NULL);
    }
    void preOrder(QtTreeNode* Qt, ofstream &outFile1) {
        if (isLeaf(Qt)) {
            Qt->printQtNode(Qt, outFile1);
        } else {
            Qt->printQtNode(Qt, outFile1);
            preOrder(Qt->NWkid, outFile1);
            preOrder(Qt->NEkid, outFile1);
            preOrder(Qt->SWkid, outFile1);
            preOrder(Qt->SEkid, outFile1);
        }
    }
    void postOrder(QtTreeNode* Qt, ofstream &outFile1) {
        if (isLeaf(Qt)) {
            Qt->printQtNode(Qt, outFile1);
        } else {
            postOrder(Qt->NWkid, outFile1);
            postOrder(Qt->NEkid, outFile1);
            postOrder(Qt->SWkid, outFile1);
            postOrder(Qt->SEkid, outFile1);
            Qt->printQtNode(Qt, outFile1);
        }
    }
};

int main(int argc, char* argv[])
{
    ifstream inFile;
    ofstream outFile1, outFile2;
    
    // if (argc!=4) {
    //   cout<<"Invalid Number of Files"<<endl;
    //   return -1;
    // }

    inFile.open("img0.txt");
    outFile1.open("output1.txt");
    outFile2.open("output2.txt");
    string numRows, numCols, minVal, maxVal;
    inFile >> numRows;
    inFile >> numCols;
    inFile >> minVal;
    inFile >> maxVal;
    image I(stoi(numRows), stoi(numCols), stoi(minVal), stoi(maxVal));
    int power2Size = I.computePower2();
    outFile2 << "*** power2Size is " << power2Size << endl;

    int** imgAry; //dynamically allocate the array size of power2Size by power2Size
    imgAry = new int*[power2Size];
    for (int i=0; i<power2Size; i++) {
        imgAry[i] = new int[power2Size];
    }
    I.zero2DAry(imgAry);
    I.loadImage(inFile, imgAry);
    outFile2 << "*** imgAry:" << endl;
    for (int i=0; i<power2Size; i++) {
        for (int j=0; j<power2Size; j++) {
            outFile2 << imgAry[i][j] << " ";
            if (j==power2Size-1) {
                outFile2 << endl;
            }
        }
    }

    QuadTree QT;
    QtTreeNode* QtRoot;
    outFile2 << "*** Build a quad tree:" << endl;
    QtRoot = QT.buildQuadTree(imgAry, 0, 0, power2Size, outFile2);

    // outFile1 << "*** PreOrder Traversal: " << endl;
    // QT.preOrder(QtRoot, outFile1);
    // outFile1 << "*** PostOrder Traversal: " << endl;
    // QT.postOrder(QtRoot, outFile1);

    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

// class LLStack
// {
// private:
//     listNode* top;
//     friend class RadixSort;
// public:
// //  constructor
//     LLStack() {
//         listNode* dummy = new listNode(-9999);
//         dummy->next = NULL;
//         top = dummy;
//     }
//     ~LLStack() {
//         listNode* currentNode = top;
//         while (currentNode) {
//             listNode* nextNode = currentNode->next;
//             currentNode = NULL;
//             delete currentNode;
//             currentNode = nextNode;
//         }
// 	  }
//     void push(listNode* newNode) {
//         newNode->next = top->next;
//         top->next = newNode;
//     }
//     listNode* pop() {
//         if (isEmpty()) { return NULL; }
//         else {
//             listNode *oldTop = top->next;
//             top->next = top->next->next;
//             // Delete the preexisting connection
//             oldTop->next = NULL;
//             return oldTop;
//         }
//     }
//     bool isEmpty() { return (top->next==NULL); }

//     void printStack(ofstream &outFile1) {
//         listNode* tmp = top;
//         outFile1 << "Top-->";
//         while (tmp->next != NULL) {
//             tmp->printNode(tmp, outFile1);
//             tmp = tmp->next;
//         }
//         outFile1<<"("+to_string(tmp->data)+", NULL)-->NULL\n";
//     }
// };

// class LLQueue
// {
// private:
//     listNode* head;
//     listNode* tail;
//     friend class RadixSort;
// public:
// //  constructor
//     LLQueue() {
//         listNode* dummy = new listNode(-9999);
//         dummy->next = NULL;
//         head = dummy;
//         tail = dummy;
//     }
//     ~LLQueue() {
//         listNode* currentNode = head;
//         while (currentNode) {
//             listNode* nextNode = currentNode->next;
//             currentNode = NULL;
//             delete currentNode;
//             currentNode = nextNode;
//         }
// 	  }
//     void insertQ(listNode* newNode) {
//         newNode->next=NULL;
//         if (isEmpty()) {
//             head->next = newNode;
//         } else {
//             tail->next = newNode;
//         }
//         tail = newNode;
//     }
//     listNode* deleteQ() {
//         if (isEmpty()) { return NULL; }
        
//         listNode* tmp = head->next;
//         head->next = head->next->next;
//         if (tmp->next == NULL) { tail=head; }
//         return tmp;
//     }
//     bool isEmpty() { return (head==tail); }

//     void printQueue(int whichTable, int index, ofstream &outFile2) {
//         listNode* tmp = head;
//         outFile2 << "Table["+to_string(whichTable)+"]["+to_string(index)+"]: ";
//         while (tmp->next != NULL) {
//             tmp->printNode(tmp, outFile2);
//             tmp = tmp->next;
//         }
//         outFile2<<"("+to_string(tmp->data)+", NULL)-->NULL\n";
//     }

//     void printData(int whichTable, int index, int offSet, ofstream &outFile1) {
//         listNode* tmp = head;
//         while (tmp != NULL) {
//             if (tmp->data != -9999) {
//                 outFile1 << tmp->data - offSet << endl;
//             }
//             tmp = tmp->next;
//         }
//     }
//     int peek() { return tail->data; } // for debugging
// };

// class RadixSort
// {
// private:
//     int tableSize = 10;
//     LLQueue* hashTable[2][10];
//     int currentTable; //either 0 or 1
//     int previousTable; //either 0 or 1
//     int currentQueue;
//     int numDigits;
//     int offSet; // the absolute value of the largest negative integer
//     int currentPosition; // The current digit position
// public:
//     // constructor: create hashTable[2][tableSize]
//     RadixSort() {
//         for (int i=0; i<2; i++) {
//             for (int j=0; j<tableSize; j++) {
//                 hashTable[i][j] = new LLQueue();
//             }
//         }
//     }
//     ~RadixSort() {
//         for (int i=0; i<2; i++) {
//             for (int j=0; j<tableSize; j++) {
//                 delete hashTable[i][j];
//             }
//         }
//     }
//     void firstReading(ifstream &inFile, ofstream &outFile2) {
//         outFile2 << "*** Performing firstReading" << endl;
//         int negativeNum = 0;
//         int positiveNum = 0;
//         int data;
//         // Step 1,2
//         while (inFile >> data) {
//             if (data < negativeNum) negativeNum = data;
//             if (data > positiveNum) positiveNum = data;
//         }
//         // Step 3
//         if (negativeNum < 0) offSet = abs(negativeNum);
//         else offSet = 0;
//         // Step 4
//         positiveNum = positiveNum + offSet;
//         numDigits = this->getLength(positiveNum);
//         outFile2 << "Positive Number: " + to_string(positiveNum) + " | Negative Number: " + to_string(negativeNum) + " | Offset: " + to_string(offSet) + " | Number of Digits: " + to_string(numDigits) << endl << endl;
//     }

//     LLStack loadStack(ifstream &inFile, ofstream &outFile2) {
//         outFile2 << "*** Performing loadStack" << endl;
//         LLStack S;
//         int data;
//         while (inFile >> data) {
//             data += offSet;
//             listNode* newNode = new listNode(data);
//             S.push(newNode);
//         }
//         return S;
//     }

//     void RSort(LLStack &S, ofstream &outFile1, ofstream &outFile2) {
//         outFile2 << "*** Performing RSort" << endl;
//         // Step 1
//         currentPosition = 0;
//         currentTable = 0;
//         // Step 2: moveStack
//         outFile2 << "*** Performing moveStack" << endl;
//         this->moveStack(S, currentPosition, currentTable);
//         // Step 3: printStack
//         outFile2 << "*** Current Position: " + to_string(currentPosition) + " | Table Number: " + to_string(currentTable) << endl;
//         this->printTable(currentTable, outFile2);
//         // Step 4
//         currentPosition++;
//         currentTable = 1;
//         previousTable = 0;
//         currentQueue = 0;
//         while (currentPosition<numDigits) {
//             // Steps 5~8: moving all queues from current table.
//             while (currentQueue <= tableSize-1) {
//                 // Step 5, 6: moving nodes from previous table to current table
//                 while (!hashTable[previousTable][currentQueue]->isEmpty()) {
//                     listNode* newNode = hashTable[previousTable][currentQueue]->deleteQ();
//                     int hashIndex = this->getDigit(newNode->data, currentPosition);
//                     hashTable[currentTable][hashIndex]->insertQ(newNode);
//                 }
//                 // Step 7
//                 currentQueue++;
//             }
//             // Step 9: printTable(currentTable, outFile2)
//             outFile2 << "\n*** Current Position: " + to_string(currentPosition) + " | Table Number: " + to_string(currentTable) << endl;
//             this->printTable(currentTable, outFile2);
//             // Step 10
//             previousTable = currentTable;
//             currentTable = (currentTable+1)%2;
//             currentQueue = 0;
//             currentPosition++;
//         }
//         // Step 12: printSortedData (previousTable, outFile1)
//         this->printSortedData(previousTable, outFile1);
//     }

//     void moveStack(LLStack &S, int currentPosition, int currentTable) {
//         while (!S.isEmpty()) {
//             listNode* newNode = S.pop();
//             int hashIndex = this->getDigit(newNode->data, currentPosition);
//             hashTable[currentTable][hashIndex]->insertQ(newNode);
//         }
//     }
//     // Determines and returns the length of a given data.
//     int getLength(int data) {
//         string tmp = to_string(data);
//         return tmp.length();
//     }

//     int getDigit(int data, int currentPosition) {
//         string str = to_string(data);
//         // turn the data into a zero-padded string
//         string dataStr = string(numDigits-str.length(), '0')+str;
//         // string indexing is from left to right. BUT,
//         // the currentPosition should count from right to left.
//         int digit = dataStr.at(numDigits-1-currentPosition)-'0';
//         return digit;
//     }

//     void printTable(int whichTable, ofstream &outFile2) {
//         for (int index=0; index<tableSize; index++) {
//             LLQueue* tmp = hashTable[whichTable][index];
//             if (!tmp->isEmpty())
//                 tmp->printQueue(whichTable, index, outFile2);
//         }
//     }
//     // for the final output to outFile1
//     void printSortedData(int whichTable, ofstream &outFile1) {
//         for (int index=0; index<tableSize; index++) {
//             LLQueue* tmp = hashTable[whichTable][index];
//             if (!tmp->isEmpty())
//                 tmp->printData(whichTable, index, offSet, outFile1);
//         }
//     }
// };

// int main(int argc, char* argv[])
// {
//     ifstream inFile;
//     ofstream outFile1, outFile2, outFile3;
    
//     // if (argc!=4) {
//     //   cout<<"Invalid Number of Files"<<endl;
//     //   return -1;
//     // }
    
//     inFile.open("Data2.txt");
//     outFile1.open("output1.txt");
//     outFile2.open("output2.txt");
//     RadixSort R;
//     R.firstReading(inFile, outFile2);
//     inFile.close();

//     inFile.open("Data2.txt");
//     LLStack S = R.loadStack(inFile, outFile2);
//     S.printStack(outFile2); //for debugging purposes
//     R.RSort(S, outFile1, outFile2);

//     inFile.close();
//     outFile1.close();
//     outFile2.close();
//     return 0;
// }

