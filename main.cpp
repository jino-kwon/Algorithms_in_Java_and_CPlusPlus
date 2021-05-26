#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class listNode
{
private:
    int data;
    listNode* next;

    friend class LLStack;
    friend class LLQueue;
    friend class RadixSort;
public:
//  constructor
    listNode(int n) {
        data = n;
        next = NULL;
    }
    void printNode(listNode* node, ofstream &outFile) {
        outFile << "(" + to_string(node->data) + ", " + to_string(node->next->data) + ")-->";        
    }
};

class LLStack
{
private:
    listNode* top;
    friend class RadixSort;
public:
//  constructor
    LLStack() {
        listNode* dummy = new listNode(-9999);
        dummy->next = NULL;
        top = dummy;
    }
    ~LLStack() {
        listNode* currentNode = top;
        while (currentNode) {
            listNode* nextNode = currentNode->next;
            currentNode = NULL;
            delete currentNode;
            currentNode = nextNode;
        }
	  }
    void push(listNode* newNode) {
        newNode->next = top->next;
        top->next = newNode;
    }
    listNode* pop() {
        if (isEmpty()) { return NULL; }
        else {
            listNode *oldTop = top->next;
            top->next = top->next->next;
            // Delete the preexisting connection
            oldTop->next = NULL;
            return oldTop;
        }
    }
    bool isEmpty() { return (top->next==NULL); }

    void printStack(ofstream &outFile1) {
        listNode* tmp = top;
        outFile1 << "Top-->";
        while (tmp->next != NULL) {
            tmp->printNode(tmp, outFile1);
            tmp = tmp->next;
        }
        outFile1<<"("+to_string(tmp->data)+", NULL)-->NULL\n";
    }
};

class LLQueue
{
private:
    listNode* head;
    listNode* tail;
    friend class RadixSort;
public:
//  constructor
    LLQueue() {
        listNode* dummy = new listNode(-9999);
        dummy->next = NULL;
        head = dummy;
        tail = dummy;
    }
    ~LLQueue() {
        listNode* currentNode = head;
        while (currentNode) {
            listNode* nextNode = currentNode->next;
            currentNode = NULL;
            delete currentNode;
            currentNode = nextNode;
        }
	  }
    void insertQ(listNode* newNode) {
        newNode->next=NULL;
        if (isEmpty()) {
            head->next = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    listNode* deleteQ() {
        if (isEmpty()) { return NULL; }
        
        listNode* tmp = head->next;
        head->next = head->next->next;
        if (tmp->next == NULL) { tail=head; }
        return tmp;
    }
    bool isEmpty() { return (head==tail); }

    void printQueue(int whichTable, int index, ofstream &outFile2) {
        listNode* tmp = head;
        outFile2 << "Table["+to_string(whichTable)+"]["+to_string(index)+"]: ";
        while (tmp->next != NULL) {
            tmp->printNode(tmp, outFile2);
            tmp = tmp->next;
        }
        outFile2<<"("+to_string(tmp->data)+", NULL)-->NULL\n";
    }

    void printData(int whichTable, int index, int offSet, ofstream &outFile1) {
        listNode* tmp = head;
        while (tmp != NULL) {
            if (tmp->data != -9999) {
                outFile1 << tmp->data - offSet << endl;
            }
            tmp = tmp->next;
        }
    }
    int peek() { return tail->data; } // for debugging
};

class RadixSort
{
private:
    int tableSize = 10;
    LLQueue* hashTable[2][10];
    int currentTable; //either 0 or 1
    int previousTable; //either 0 or 1
    int currentQueue;
    int numDigits;
    int offSet; // the absolute value of the largest negative integer
    int currentPosition; // The current digit position
public:
    // constructor: create hashTable[2][tableSize]
    RadixSort() {
        for (int i=0; i<2; i++) {
            for (int j=0; j<tableSize; j++) {
                hashTable[i][j] = new LLQueue();
            }
        }
    }
    ~RadixSort() {
        for (int i=0; i<2; i++) {
            for (int j=0; j<tableSize; j++) {
                delete hashTable[i][j];
            }
        }
    }
    void firstReading(ifstream &inFile, ofstream &outFile2) {
        outFile2 << "*** Performing firstReading" << endl;
        int negativeNum = 0;
        int positiveNum = 0;
        int data;
        // Step 1,2
        while (inFile >> data) {
            if (data < negativeNum) negativeNum = data;
            if (data > positiveNum) positiveNum = data;
        }
        // Step 3
        if (negativeNum < 0) offSet = abs(negativeNum);
        else offSet = 0;
        // Step 4
        positiveNum = positiveNum + offSet;
        numDigits = this->getLength(positiveNum);
        outFile2 << "Positive Number: " + to_string(positiveNum) + " | Negative Number: " + to_string(negativeNum) + " | Offset: " + to_string(offSet) + " | Number of Digits: " + to_string(numDigits) << endl << endl;
    }

    LLStack loadStack(ifstream &inFile, ofstream &outFile2) {
        outFile2 << "*** Performing loadStack" << endl;
        LLStack S;
        int data;
        while (inFile >> data) {
            data += offSet;
            listNode* newNode = new listNode(data);
            S.push(newNode);
        }
        return S;
    }

    void RSort(LLStack &S, ofstream &outFile1, ofstream &outFile2) {
        outFile2 << "*** Performing RSort" << endl;
        // Step 1
        currentPosition = 0;
        currentTable = 0;
        // Step 2: moveStack
        outFile2 << "*** Performing moveStack" << endl;
        this->moveStack(S, currentPosition, currentTable);
        // Step 3: printStack
        outFile2 << "*** Current Position: " + to_string(currentPosition) + " | Table Number: " + to_string(currentTable) << endl;
        this->printTable(currentTable, outFile2);
        // Step 4
        currentPosition++;
        currentTable = 1;
        previousTable = 0;
        currentQueue = 0;
        while (currentPosition<numDigits) {
            // Steps 5~8: moving all queues from current table.
            while (currentQueue <= tableSize-1) {
                // Step 5, 6: moving nodes from previous table to current table
                while (!hashTable[previousTable][currentQueue]->isEmpty()) {
                    listNode* newNode = hashTable[previousTable][currentQueue]->deleteQ();
                    int hashIndex = this->getDigit(newNode->data, currentPosition);
                    hashTable[currentTable][hashIndex]->insertQ(newNode);
                }
                // Step 7
                currentQueue++;
            }
            // Step 9: printTable(currentTable, outFile2)
            outFile2 << "\n*** Current Position: " + to_string(currentPosition) + " | Table Number: " + to_string(currentTable) << endl;
            this->printTable(currentTable, outFile2);
            // Step 10
            previousTable = currentTable;
            currentTable = (currentTable+1)%2;
            currentQueue = 0;
            currentPosition++;
        }
        // Step 12: printSortedData (previousTable, outFile1)
        this->printSortedData(previousTable, outFile1);
    }

    void moveStack(LLStack &S, int currentPosition, int currentTable) {
        while (!S.isEmpty()) {
            listNode* newNode = S.pop();
            int hashIndex = this->getDigit(newNode->data, currentPosition);
            hashTable[currentTable][hashIndex]->insertQ(newNode);
        }
    }
    // Determines and returns the length of a given data.
    int getLength(int data) {
        string tmp = to_string(data);
        return tmp.length();
    }

    int getDigit(int data, int currentPosition) {
        string str = to_string(data);
        // turn the data into a zero-padded string
        string dataStr = string(numDigits-str.length(), '0')+str;
        // string indexing is from left to right. BUT,
        // the currentPosition should count from right to left.
        int digit = dataStr.at(numDigits-1-currentPosition)-'0';
        return digit;
    }

    void printTable(int whichTable, ofstream &outFile2) {
        for (int index=0; index<tableSize; index++) {
            LLQueue* tmp = hashTable[whichTable][index];
            if (!tmp->isEmpty())
                tmp->printQueue(whichTable, index, outFile2);
        }
    }
    // for the final output to outFile1
    void printSortedData(int whichTable, ofstream &outFile1) {
        for (int index=0; index<tableSize; index++) {
            LLQueue* tmp = hashTable[whichTable][index];
            if (!tmp->isEmpty())
                tmp->printData(whichTable, index, offSet, outFile1);
        }
    }
};

int main(int argc, char* argv[])
{
    ifstream inFile;
    ofstream outFile1, outFile2;
    
    if (argc!=4) {
      cout<<"Invalid Number of Files"<<endl;
      return -1;
    }
    
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    RadixSort R;
    R.firstReading(inFile, outFile2);
    inFile.close();

    inFile.open(argv[1]);
    LLStack S = R.loadStack(inFile, outFile2);
    S.printStack(outFile2); //for debugging purposes
    R.RSort(S, outFile1, outFile2);

    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

