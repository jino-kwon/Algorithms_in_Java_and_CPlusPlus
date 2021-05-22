#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class listNode
{
    friend class LLStack;
    friend class LLQueue;
    friend class LLlist;
public:
    int data;
    listNode* next;

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
public:
//  constructor
    LLStack() {
        listNode* dummy = new listNode(-9999);
        dummy->next = NULL;
        top = dummy;
    }
    void push(listNode* newNode) {
        newNode->next = top->next;
        top->next = newNode;
    }
    listNode* pop() {
        if (isEmpty()) { return NULL; }
        else {
            listNode *newTop = top->next;
            top->next = top->next->next;
            // Delete the preexisting connection
            newTop->next = NULL;
            return newTop;
        }
    }
    bool isEmpty() { return (top==NULL); }

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
public:
//  constructor
    LLQueue() {
        listNode* dummy = new listNode(-9999);
        dummy->next = NULL;
        head = dummy;
        tail = dummy;
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
        // when there's more than one node in the queue
        if (tmp->next != NULL) { head->next = head->next->next; }
        // when there's only one node in the queue
        else { tail = head; }
        return tmp;
    }
    bool isEmpty() { return (head==tail); }
    void printQ(ofstream &outFile2) {
        listNode* tmp = head;
        outFile2 << "Front-->";
        while (tmp->next != NULL) {
            tmp->printNode(tmp, outFile2);
            tmp = tmp->next;
        }
        outFile2<<"("+to_string(tmp->data)+", NULL)-->NULL\n";
    }
};

class LLlist
{
private:
    listNode* listHead;
public:
//  constructor
    LLlist() {
        listNode* dummy = new listNode(-9999);
        dummy->next = NULL;
        listHead = dummy;
    }
    void listInsert(listNode* newNode) {
        listNode* tmp = listHead;
        while (tmp->next != NULL && tmp->next->data < newNode->data) {
            tmp = tmp->next;
        }
        if (tmp->data == newNode->data) { tmp = tmp->next; }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }   
    listNode* deleteOneNode(int data) {
        listNode* tmp = listHead;
        while (tmp->next != NULL && tmp->next->data < data)
            tmp = tmp->next;
        // return null if empty list or no mathching value exists
        if (tmp->next == NULL || tmp->next->data != data)
            return NULL;
        // when the nodeToDelete is at the beginning or the end
        listNode* nodeToDelete = tmp->next;
        if (tmp->next->next == NULL) {
            tmp->next = NULL;
        } else {
            tmp->next = tmp->next->next;
        }
        return nodeToDelete;
    }
    void printList(ofstream &outFile3) {
        listNode* tmp = listHead;
        outFile3 << "listHead-->";
        while (tmp->next != NULL) {
            tmp->printNode(tmp, outFile3);
            tmp = tmp->next;
        }
        outFile3<<"("+to_string(tmp->data)+", NULL)-->NULL\n";
    }
};

void buildStack(ifstream &inFile, ofstream &outFile1) {
    LLStack* S = new LLStack();
    char op;
    int data;
    
    while (inFile >> op >> data) {
        if (op == '+') {
            listNode* newNode = new listNode(data);
            S->push(newNode);
            outFile1 << "Push "+to_string(data)+":  ";
        }
        else if (op == '-') {
            listNode* junk = S->pop();
            if (junk != NULL) {
                outFile1 << "Pop  :  ";
                free(junk);
            } else {
                outFile1 << "the Stack is empty\n";
                continue;
            }
        }
        S->printStack(outFile1);
    }
}

void buildQueue(ifstream &inFile, ofstream &outFile2) {
    LLQueue* Q = new LLQueue();
    char op;
    int data;
    
    while (inFile >> op >> data) {
        if (op == '+') {
            listNode* newNode = new listNode(data);
            Q->insertQ(newNode);
            outFile2 << "Insert "+to_string(data)+":  ";
        }
        else if (op == '-') {
            listNode* junk = Q->deleteQ();
            if (junk != NULL) {
                outFile2 << "Delete  :  ";
                free(junk);
            } else {
                outFile2 << "the Queue is empty\n";
                continue;
            }
        }
        Q->printQ(outFile2);
    }
}

void buildList(ifstream &inFile, ofstream &outFile3) {
    LLlist* listHead = new LLlist();
    char op;
    int data;
    
    while (inFile >> op >> data) {
        if (op == '+') {
            listNode* newNode = new listNode(data);
            listHead->listInsert(newNode);
            outFile3 << "Insert "+to_string(data)+":  ";
        }
        else if (op == '-') {
            listNode* junk = listHead->deleteOneNode(data);
            if (junk != NULL) {
                outFile3 << "Delete "+to_string(data)+":  ";
                free(junk);
            } else {
                outFile3 << "the data is not in the list\n";
                continue;
            }
        }
        listHead->printList(outFile3);
    }
}

int main(int argc, char* argv[])
{
    ifstream inFile;
    ofstream outFile1, outFile2, outFile3;
    
    if (argc!=5) {
      cout<<"Invalid Number of Files"<<endl;
      return -1;
    }
    
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    outFile3.open(argv[4]);    
    buildStack(inFile, outFile1);

    inFile.close();
    inFile.open(argv[1]);
    buildQueue(inFile, outFile2);

    inFile.close();
    inFile.open(argv[1]);
    buildList(inFile, outFile3);
//  close all files.
    inFile.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
    return 0;
}
