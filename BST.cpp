#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
	
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
	
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
	
}

BSTNode *BST::find(string title, string author) {
	return NULL;
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
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