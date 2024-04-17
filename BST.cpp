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
        } else {
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
                } else {
                    current = current->right;
                    if(current == NULL){
                        parent->right = newNode;
                        return;
                    }
                }
            }
        }
    }



    /*
    if(root == NULL){
        BSTNode* newNode = new BSTNode(title, author, yr, pub, isbn, rate);
        root = newNode;
        return;
    }
    if(author < root->book->author){
        root = root->left;
        insert(title, author, yr, pub, isbn, rate);
    }
    else if(author > root->book->author){
        root = root->right;
        insert(title, author, yr, pub, isbn, rate);
    }
    else if(author == root->book->author){
        if(title < root->book->title){
            root = root->left;
            insert(title, author, yr, pub, isbn, rate);
        } else {
            root = root->right;
            insert(title, author, yr, pub, isbn, rate);
        }
    }
}
*/
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
	/*
    if (!node) {
        return;
    }
    node->printNode();
    printTreePre(node->left);
    printTreePre(node->right);
    */
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
	return false;
}

bool BST::checkIn(string title, string author) {
	return false;
}

void BST::updateRating(string title, string author, float newRating) {
	
}


BSTNode *BST::removeNoKids(BSTNode *node) {
	return NULL;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
	return NULL;
}

BSTNode *BST::remove(string title, string author) {
	return NULL;
}

void BST::setHeight(BSTNode *node) {
	
}