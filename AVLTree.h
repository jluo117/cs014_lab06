#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void insert(const string &str);
        int balanceFactor(Node *curr);
        void printBalanceFactors();
        void visualizeTree(const string &outputFilename);
        
    private:
        Node * root;
        void destroy(Node * curr);
        Node * findUnbalancedNode(Node * curr);
        void rotate(Node * curr);
        Node * rotateLeft(Node * curr);
        Node * rotateRight(Node * curr);
        void printBalanceFactors(Node *curr);
        void visualizeTree(ofstream &outFS, Node *curr);
        int height(Node * curr) const;
};

#endif