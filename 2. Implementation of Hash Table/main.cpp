#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class listNode {
private:
    string firstName;
    string lastName;
    listNode* next;
    friend class HashTable;
public:
//  default constructor
    listNode() {
        firstName = "dummyFirst";
        lastName = "dummyLast";
        next = NULL;
    }
//  constructor
    listNode(string first, string last) {
        firstName = first;
        lastName = last;
    }

    void printNode(ofstream &outFile) {
        outFile << "(" + this->firstName + " " + this->lastName + " " + this->next->firstName + ")-->";
    }
};

class HashTable {
private:
    char op;
    int bucketSize;
    listNode* hashTable;
public:
//  constructor => createHashTable
    HashTable(int bs) {
        bucketSize = bs;
        hashTable = new listNode[bs];
    }

    int Doit(string lastName) {
        unsigned int hashVal = 1;
        for (int i=0; i<lastName.length(); i++) {
           hashVal = hashVal*32 + (int)lastName[i];
        }
        return hashVal % bucketSize;
    }

    void informationProcessing(ifstream &inFile, ofstream &outFile2) {
        int index;
        string firstName;
        string lastName;
        // Step 2
        while (inFile >> op >> firstName >> lastName) {
            outFile2 << "---------------------------------------------------\n";
            outFile2 << "OP: " << op << " | First Name: " << firstName + " | Last Name: " + lastName + " | ";
        // Step 3
            index = Doit(lastName);
            outFile2 << "Index: " << index << endl;
            outFile2 << "***Current Hash Table:\n";
        // Step 4
            this->printList(index, outFile2);
        // Step 5
            if (op == '+')
                this->hashInsert(index, firstName, lastName, outFile2);
            else if (op == '-')
                this->hashDelete(index, firstName, lastName, outFile2);
            else if (op == '?')
                this->hashRetrieval(index, firstName, lastName, outFile2);
        }
    }

    listNode* findSpot(int index, string firstName, string lastName) {
        listNode* spot = &hashTable[index];
        while (spot->next != NULL && spot->next->lastName < lastName)
            spot = spot->next;

        while (spot->next != NULL && spot->next->lastName == lastName && spot->next->firstName < firstName)
            spot = spot->next;
        return spot;
    }

    void hashInsert(int index, string firstName, string lastName, ofstream &outFile2) {
        outFile2 << "***Performing hashInsert on " + firstName + " " + lastName << endl;
        listNode* spot = this->findSpot(index, firstName, lastName);

        if (spot->next != NULL && spot->next->lastName == lastName && spot->next->firstName == firstName) {
            outFile2 << "*** Warning, the record is already in the database!\n";
        } else {
            listNode* newNode = new listNode(firstName, lastName);
            newNode->next = spot->next;
            spot->next = newNode;
            this->printList(index, outFile2);
        }
    }

    void hashDelete(int index, string firstName, string lastName, ofstream &outFile2) {
        outFile2 << "***Performing hashDelete on " + firstName + " " + lastName << endl;
        listNode* spot = this->findSpot(index, firstName, lastName);

        if (spot->next != NULL && spot->next->lastName == lastName && spot->next->firstName == firstName) {
            listNode* junk = spot->next;
            spot->next = spot->next->next;
            junk->next = NULL;
            free(junk);
            this->printList(index, outFile2);
        } else
            outFile2 << "*** Warning, the record is not in the database!\n";
    }

    void hashRetrieval(int index, string firstName, string lastName, ofstream &outFile2) {
        outFile2 << "***Performing hashRetrieval on " + firstName + " " + lastName << endl;
        listNode* spot = this->findSpot(index, firstName, lastName);

        if (spot->next != NULL && spot->next->lastName == lastName && spot->next->firstName == firstName) {
            outFile2 << "Yes, the record is in the database!\n";
        } else
            outFile2 << "No, the record is not in the database!\n";
    }

    void printList(int index, ofstream &outFile) {
        listNode* tmp = &hashTable[index];
        outFile << "HashTable["+to_string(index)+"]: ";
        while (tmp->next != NULL) {
            tmp->printNode(outFile);
            tmp = tmp->next;
        }
        outFile << "(" + tmp->firstName + " " + tmp->lastName + " NULL)-->NULL\n";
    }

    void printHashTable(ofstream &outFile) {
        for (int idx=0; idx<bucketSize; idx++)
            this->printList(idx, outFile);
    }
};

int main(int argc, char* argv[])
{
    ifstream inFile;
    ofstream outFile1, outFile2;
    if (argc!=5) {
      cout<<"Invalid Number of Files"<<endl;
      return -1;
    }

    inFile.open(argv[1]);
    int bucketSize = atoi(argv[2]);
    outFile1.open(argv[3]);
    outFile2.open(argv[4]);

    HashTable H(bucketSize); // createHashTable
    H.informationProcessing(inFile, outFile2);
    H.printHashTable(outFile1);
//  close all files.
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}