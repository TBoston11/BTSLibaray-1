#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
	root = NULL;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
	root = new BSTNode(title, author, yr, pub, isbn, rate);
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode* newNode = new BSTNode(title, author, yr, pub, isbn, rate);
    if(root == NULL){
        root = newNode;
    }
    else {
        BSTNode* current = root;
        BSTNode* parent = NULL;
        while(true){
            parent = current;
            if(author < current->book->author || (author == current->book->author && title < current->book->title)){
                current = current->left;
                if(current == NULL){
                    parent->left = newNode;
                    return;
                }
            }
            else {
                current = current->right;
                if(current == NULL){
                    parent->right = newNode;
                    return;
                }
            }
        }
    }
}

BSTNode *BST::find(string title, string author) {
    BSTNode* current = root;
    while (current != NULL) {
        if (author == current->book->author && title == current->book->title) {
            return current;
        }
        if(author < current->book->author){
            current = current->left;
        }
        else if(author > current->book->author){
            current = current->right;
        }
        else if(author == current->book->author) {
            if (title < current->book->title) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return NULL;
}


BSTNode *BST::find(string title, string author, BSTNode *start) {
    BSTNode* current = start;
    while (current != NULL) {
        if (author == current->book->author && title == current->book->title) {
            return current;
        }
        if(author < current->book->author){
            current = current->left;
        }
        else if(author > current->book->author){
            current = current->right;
        }
        else if(author == current->book->author) {
            if (title < current->book->title) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return NULL;
}

void BST::printTreeIO(bool debug) {
    if (root == NULL) {
        cout << "Empty Tree" << endl;
    }
    else {
        cout << endl << "Printing In-Order:" << endl;
        printTreeIO(root, debug);
    }
}

void BST::printTreeIO(BSTNode *node, bool debug) {
    if (!node) {
        return;
    }
    printTreeIO(node->left, debug);
    node->printNode(debug);
    printTreeIO(node->right, debug);
}

void BST::printTreePre(bool debug) {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root, debug);
	}
}

void BST::printTreePre(BSTNode *node, bool debug) {
    if (!node) {
        return;
    }
    node->printNode(debug);
    printTreePre(node->left, debug);
    printTreePre(node->right, debug);
}

void BST::printTreePost(bool debug) {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root, debug);
	}
}

void BST::printTreePost(BSTNode *node, bool debug) {
    if (!node) {
        return;
    }
    printTreePost(node->left, debug);
    printTreePost(node->right, debug);
    node->printNode(debug);
}

void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(BSTNode *node) {
	if (node == NULL) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = NULL;
		clearTree(node->right);
		node->right = NULL;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    if (find(title, author) != NULL) {
        if (find(title, author)->book->checked_out == true) {
            return false;
        }
        else {
            return find(title, author)->book->checked_out = true;
        }
    }
    return false;
}

bool BST::checkIn(string title, string author) {
    if (find(title, author) != NULL) {
        if (find(title, author)->book->checked_out == false) {
            return false;
        }
        else {
            return find(title, author)->book->checked_out = true;
        }
    }
	return false;
}

void BST::updateRating(string title, string author, float newRating) {
	if (find(title, author) != NULL) {
        find(title, author)->book->rating = newRating;
    }
    return;
}


BSTNode *BST::removeNoKids(BSTNode *node) {
    if(node->parent->left == node){
        node->parent->left = NULL;
    } else {
        node->parent->right = NULL;
    }
    delete node;
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    if(leftFlag){
        if(node->parent->left == node){
            node->parent->left = node->left;
        } else {
            node->parent->right = node->left;
        }
    } else {
        if(node->parent->left == node){
            node->parent->left = node->right;
        } else {
            node->parent->right = node->right;
        }
    }
    delete node;
    return node;
}

BSTNode *BST::remove(string title, string author) {
	return NULL;
}

void BST::setHeight(BSTNode *node) {
	
}