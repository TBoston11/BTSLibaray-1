//Connor Lockwood and Thomas Boston

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
                    newNode->parent = parent;
                    setHeight(newNode);
                    return;
                }
            }
            else {
                current = current->right;
                if(current == NULL){
                    parent->right = newNode;
                    newNode->parent = parent;
                    setHeight(newNode);
                    return;
                }
            }
        }
    }
}

BSTNode* BST::find(string title, string author) {
    return find(title, author, root);
}


BSTNode *BST::find(string title, string author, BSTNode *start) {
    if (start == NULL) {
        return NULL;
    }
    int autComp = author.compare(start->book->author);
    int titleComp = title.compare(start->book->title);
    if (autComp == 0 && titleComp == 0) {
        return start;
    }
    if (autComp < 0 || (autComp == 0 && titleComp < 0)) {
        return find(title, author, start->left);
    }
    else {
        return find(title, author, start->right);
    }
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
    BSTNode* hold = find(title, author, root);
    if (hold == NULL) {
        return false;
    }
    else {
        if (hold->book->checked_out) {
            return false;
        }
        else {
            hold->book->checked_out = true;
            return true;
        }
    }
}

bool BST::checkIn(string title, string author) {
    BSTNode* hold = find(title, author, root);
    if (hold == NULL) {
        return false;
    }
    else {
        if (!hold->book->checked_out) {
            return false;
        }
        else {
            hold->book->checked_out = false;
            return true;
        }
    }
}

void BST::updateRating(string title, string author, float newRating) {
    BSTNode* bookPoint = find(title, author);
    if (bookPoint != NULL) {
            bookPoint->book->rating = newRating;
            if(bookPoint->right != NULL && bookPoint->right->book->title == bookPoint->book->title){
                bookPoint->right->book->rating = newRating;
        }
    }
    return;
}


BSTNode *BST::removeNoKids(BSTNode *node) {
    if (node == root) {
        root = NULL;
        setHeight(node);
        return node;
    }
    BSTNode* parent = node->parent;
    if(parent == NULL){
        return node;
    }
    else {
        if (parent->left == node) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        setHeight(parent);
        return node;
    }
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    BSTNode* child;
    if (leftFlag) {
        child = node->left;
    }
    else {
        child = node->right;
    }
    if (node->parent == NULL) {
        return child;
    }
    else {
        if (node->parent->left == node) {
            node->parent->left = child;
        }
        else {
            node->parent->right = child;
        }
        if (child != NULL) {
            child->parent = node->parent;
        }
        setHeight(node->parent);
        setHeight(child);
        return node;
    }
}

BSTNode *BST::remove(string title, string author) {
    BSTNode* finder = find(title, author, root);
    //No Kids
    if (finder == NULL) {
        return NULL;
    }
    if(finder->left == NULL && finder->right == NULL){
        return removeNoKids(finder);
    }
    //One Kid
    else if(finder->left != NULL && finder->right == NULL){
        return removeOneKid(finder, true);
    }
    else if(finder->left == NULL && finder->right != NULL){
        return removeOneKid(finder, false);
    }
    //Two Kids
    else {
        BSTNode *hold = finder->right;
        while (hold->left != NULL) {
            hold = hold->left;
        }
        if (hold->parent != finder) {
            hold->parent->left = hold->right;
            if (hold->right != NULL) {
                hold->right->parent = hold->parent;
            }
            hold->right = finder->right;
        }
        if (finder->parent == NULL) {
            root = hold;
        }
        else {
            if (finder->parent->left == finder) {
                finder->parent->left = hold;
            }
            else {
                finder->parent->right = hold;
            }
        }
        if (hold->parent != NULL) {
            hold->parent = finder->parent;
        }
        hold->left = finder->left;
        setHeight(hold);
        BSTNode* parent = hold->parent;
        while (parent != NULL) {
            int left = -1;
            int right = -1;
            if (parent->left != NULL) {
                left = parent->left->height;
            }
            if (parent->right != NULL) {
                right = parent->right->height;
            }
            parent->height = max(left, right) + 1;
            parent = parent->parent;
        }
        finder->left = NULL;
        finder->right = NULL;
        finder->parent = NULL;
        return finder;
    }
}

void BST::setHeight(BSTNode *node) {
    BSTNode* hold = node;
    int val = 1;
    while (hold != NULL) {
        if (hold->height > val) {
            return;
        }
        hold->height = val;
        val++;
        hold = hold->parent;
    }
}