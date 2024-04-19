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
                    setHeight(newNode);
                    return;
                }
            }
            else {
                current = current->right;
                if(current == NULL){
                    parent->right = newNode;
                    setHeight(newNode);
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
    BSTNode* parent = node->parent;
    if(parent == NULL){
        return NULL;
    }
    else {
        if (parent->left == node) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        setHeight(parent);
        return parent;
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
        return node->parent;
    }
}

BSTNode *BST::remove(string title, string author) {
    BSTNode* finder = find(title, author);
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
        if ((hold->parent != NULL) && (hold->parent->right != hold)) {
            hold->parent->left = hold->right;
            if (hold->right != NULL) {
                hold->right->parent = hold->parent;
            }
            hold->right = finder->right;
        }
        if (finder->parent != NULL) {
            if (finder->parent->left == finder) {
                finder->parent->left = hold;
            }
            else {
                finder->parent->right = hold;
            }
        }
        else {
            root = hold;
        }
        hold->parent = finder->parent;
        hold->left = finder->left;
        setHeight(hold);
        return finder;
    }
}

void BST::setHeight(BSTNode *node) {
    int height1 = 0;
    int height2 = 0;
    int height;
    BSTNode* hold = node->left;
    while (hold) {
        height1 = height1 + 1;
        hold = hold->left;
    }
    hold = node->right;
    while(hold) {
        height2 = height2 + 1;
        hold = hold->right;
    }
    if (height1 >= height2) {
        height = height1;
    }
    else {
        height = height2;
    }
    node->height = 1 + height;
}