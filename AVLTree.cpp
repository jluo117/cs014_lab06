//Ryan Ulep & Kristian Tram

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree() {
    root = 0;
}

AVLTree::~AVLTree() {
    destroy(root);
}

void AVLTree::destroy(Node * curr) {
    if (curr == 0) {
        return;
    }
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
}

void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n) {
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}

void AVLTree::insert(const string &str) {
    if (root == 0) {
        root = new Node(str);
        return;
    }
    
    Node * curr = root;
    Node * par = 0;
    
    while (curr != 0) {
        if (str < curr->data) {
            if (curr->left == 0) {
                par = curr;
                curr->left = new Node(str);
                curr->left->parent = par;
                curr = curr->left;
                break;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            if (curr->right == 0) {
                par = curr;
                curr->right = new Node(str);
                curr->right->parent = par;
                curr = curr->right;
                break;
            }
            else {
                curr = curr->right;
            }
        }
    }
    curr = findUnbalancedNode(curr);
    if (curr != 0) {
        rotate(curr);
    }
}

Node * AVLTree::findUnbalancedNode(Node * curr) {
    while (curr != 0) {
        if (balanceFactor(curr) == 2 || balanceFactor(curr) == -2) {
            return curr;
        }
        else {
            curr = curr->parent;
        }
    }
    return 0;
}

int AVLTree::balanceFactor(Node *curr) {
    // Height of the left minus height of the right
    return height(curr->left) - height(curr->right);
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *curr) {
    if (curr == 0) {
        return;
    }
    
    printBalanceFactors(curr->left);
    cout << curr->data << "(" << balanceFactor(curr) << ")" << ", ";
    printBalanceFactors(curr->right);
}

int AVLTree::height(Node * curr) const {
    if (curr == 0) {
        return -1;
    }

    int leftheight = height(curr->left);
    int rightheight = height(curr->right);

    if (leftheight >= rightheight) {
        return leftheight + 1;
    }
    else {
        return rightheight + 1;
    }
}

void AVLTree::rotate(Node* curr) {
    Node * temp = 0;
    bool tempLeft = false;
    
    if (curr->parent != 0) {
        temp = curr->parent;
        if (temp->left == curr) {
            tempLeft = true;
        }
    }
    
    if (balanceFactor(curr) == 2  && balanceFactor(curr->left) == 1) { // left left

        curr = rotateRight(curr);
        if (temp != 0) {
            if(tempLeft) {
                temp->left = curr;
                temp->left->parent = temp;
            }
            else {
                temp->right = curr;
                temp->right->parent = temp;
            }
        }
        else {
            root = curr;
            root->parent = 0;
        }
    }
    else if (balanceFactor(curr) == -2  && balanceFactor(curr->right) == -1) { // right right
        
        curr = rotateLeft(curr);
        if (temp != 0) {
            if(tempLeft) {
                temp->left = curr;
                temp->left->parent = temp;
            }
            else {
                temp->right = curr;
                temp->right->parent = temp;
            }
        }
        else {
            root = curr;
            root->parent = 0;
        }
    }
    else if (balanceFactor(curr) == 2  && balanceFactor(curr->left) == -1) { // left right
        
        curr = rotateLeft(curr->left);
        curr = rotateRight(curr);
        if (temp != 0) {
            if(tempLeft) {
                temp->left = curr;
                temp->left->parent = temp;
            }
            else {
                temp->right = curr;
                temp->right->parent = temp;
            }
        }
        else {
            root = curr;
            root->parent = 0;
        }
    }
    else { // right left

        curr = rotateRight(curr->right);
        curr = rotateLeft(curr);
        if (temp != 0) {
            if(tempLeft) {
                temp->left = curr;
                temp->left->parent = temp;
            }
            else {
                temp->right = curr;
                temp->right->parent = temp;
            }
        }
        else {
            root = curr;
            root->parent = 0;
        }
        
    }
}

Node * AVLTree::rotateLeft(Node * curr) {
    if (curr == 0) {
        return 0;
    }
    Node * B = curr->right;   // B must exist
    Node * C = B->left;  // B's left may be 0
    
    B->left = curr;
    curr->right = C;
    curr->parent = B;
    
    return B;  // Caller should update parent to point to this new subtree root node
}

Node * AVLTree::rotateRight(Node * curr) {
    if (curr == 0) {
        return 0;
    }
    Node * B = curr->left;   // B must exist
    Node * C = B->right;  // B's right may be 0
    
    B->right = curr;
    curr->left = C;
    curr->parent = B;
    
    return B;  // Caller should update parent to point to this new subtree root node
}

/* ******************************
Dear Ryan, 
I have finished the lab and passed the tests on Zybooks. You can look over what I have done if you wish.
If you want to submit to Zybooks you should remember to comment out or delete the cout and VisualizeTree statements.

Sincerely,
Kris
****************************** *