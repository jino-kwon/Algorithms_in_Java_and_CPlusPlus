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
        string line;
        while (inFile >> data) {
            if (col == numCols-1) {
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
    int color=-1; // 0, 1 or 5
    int upperR;
    int upperC;
    int size;
    QtTreeNode* NWkid = NULL;
    QtTreeNode* NEkid = NULL;
    QtTreeNode* SWkid = NULL;
    QtTreeNode* SEkid = NULL;

//  constructor
    QtTreeNode(int c, int upR, int upC, int s, QtTreeNode* nwKid, QtTreeNode* neKid, QtTreeNode* swKid, QtTreeNode* seKid) {
        color = c;
        upperR = upR;
        upperC = upC;
        size = s;
        NWkid = nwKid;
        NEkid = neKid;
        SWkid = swKid;
        SEkid = seKid;
    }
    void printQtNode(QtTreeNode* node, ofstream &outFile) {
        string NWcolor;
        string NEcolor;
        string SWcolor;
        string SEcolor;

        if (node->NWkid == NULL) {
            NWcolor = "-1";
        } else {
            NWcolor = to_string(node->NWkid->color);
        }
        if (node->NEkid == NULL) {
            NEcolor = "-1";
        } else {
            NEcolor = to_string(node->NEkid->color);
        }
        if (node->SWkid == NULL) {
            SWcolor = "-1";
        } else {
            SWcolor = to_string(node->SWkid->color);
        }
        if (node->SEkid == NULL) {
            SEcolor = "-1";
        } else {
            SEcolor = to_string(node->SEkid->color);
        }

        outFile << "(color: " + to_string(node->color) + ", upperR: " + to_string(node->upperR) + ", upperC: " + to_string(node->upperC) + ", NWkid's color: " + NWcolor + ", NEkid's color: " + NEcolor + ", SWkid's color: " + SWcolor + ", SEkid's color: " + SEcolor + ")-->"
         << endl;       
    }
};

class QuadTree
{
public:
    QtTreeNode* QtRoot;

    QtTreeNode* buildQuadTree(int** imgAry, int upR, int upC, int size, ofstream &outFile) {
        QtTreeNode* newQtNode = new QtTreeNode(-1, upR, upC, size, NULL, NULL, NULL, NULL);
        outFile << "New Node: ";
        newQtNode->printQtNode(newQtNode, outFile);
        if (size == 1) {
            newQtNode->color = imgAry[upR][upC];
        } else {
            int halfSize = size/2;
            newQtNode->NWkid = buildQuadTree(imgAry, upR, upC, halfSize, outFile);
            newQtNode->NEkid = buildQuadTree(imgAry, upR, upC+halfSize, halfSize, outFile);
            newQtNode->SWkid = buildQuadTree(imgAry, upR+halfSize, upC, halfSize, outFile);
            newQtNode->SEkid = buildQuadTree(imgAry, upR+halfSize, upC+halfSize, halfSize, outFile);
            int sumColor = newQtNode->NWkid->color + newQtNode->NEkid->color + newQtNode->SWkid->color + newQtNode->SEkid->color;

            if (sumColor == 0) { //newQtNode is a leaf node
                newQtNode->color = 0;
                newQtNode->NWkid = NULL;
                newQtNode->NEkid = NULL;
                newQtNode->SWkid = NULL;
                newQtNode->SEkid = NULL;
            } else if (sumColor == 4) { //all kids are 1
                newQtNode->color = 1;
                newQtNode->NWkid = NULL;
                newQtNode->NEkid = NULL;
                newQtNode->SWkid = NULL;
                newQtNode->SEkid = NULL;
            } else {
                newQtNode->color = 5;
            }
        }
        return newQtNode;
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

    inFile.open("img2.txt");
    // inFile.open(argv[1]);
    outFile1.open("img2_output1.txt");
    outFile2.open("img2_output2.txt");
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
    outFile2 << "\n*** Build a quad tree:" << endl;
    QtRoot = QT.buildQuadTree(imgAry, 0, 0, power2Size, outFile2);

    outFile1 << "*** PreOrder Traversal: " << endl;
    QT.preOrder(QtRoot, outFile1);
    outFile1 << "------------ END ------------" << endl << endl;
    outFile1 << "*** PostOrder Traversal: " << endl;
    QT.postOrder(QtRoot, outFile1);
    outFile1 << "------------ END ------------";

    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}