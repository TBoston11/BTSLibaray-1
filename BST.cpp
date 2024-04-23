//Connor Lockwood and Thomas Boston

#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
    //creating the start of the BST, with a NULL root
	root = NULL;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
    //setting the root of a new tree to the passed in value
	root = new BSTNode(title, author, yr, pub, isbn, rate);
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode* newNode = new BSTNode(title, author, yr, pub, isbn, rate); // new node to be inserted
    if(root == NULL){ //if tree is empty
        root = newNode;
    }
    else {
        BSTNode* current = root; //start at root
        BSTNode* parent = NULL; //parent start at NULL because current is root
        while(true){
            parent = current;
            if(author < current->book->author || (author == current->book->author && title < current->book->title)){
                //if the book needs to be on the left subtree, continuously runs until in right spot
                current = current->left;
                if(current == NULL){ //correct spot
                    parent->left = newNode;
                    newNode->parent = parent;
                    setHeight(newNode);
                    return;
                }
            }
            else {
                current = current->right;
                if(current == NULL){ //correct spot
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
    //find starting at root
    return find(title, author, root);
}


BSTNode *BST::find(string title, string author, BSTNode *start) {
    if (start == NULL) { //empty tree
        return NULL;
    }
    int autComp = author.compare(start->book->author); //comparing author
    int titleComp = title.compare(start->book->title); //comparing title
    if (autComp == 0 && titleComp == 0) {
        return start;
    }
    if (autComp < 0 || (autComp == 0 && titleComp < 0)) {
        return find(title, author, start->left); //recursively run left subtree
    }
    else {
        return find(title, author, start->right); //recursively run right subtree
    }
}

void BST::printTreeIO(bool debug) {
    //printing tree in order
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
    //In Order: Left, Print, Right
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
    if (!node) { //If node does not exist
        return;
    }
    //Pre Order: Print, Left Right
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
    //Post Order: Left, Right, Print
    printTreePost(node->left, debug);
    printTreePost(node->right, debug);
    node->printNode(debug);
}

void BST::clearTree() {
    //Clears the tree
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
        //Runs Clear Tree
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(BSTNode *node) {
    //Function to clear the tree
	if (node == NULL) { //Empty
		return;
	}
	else {
        //Recursively clears left then right subtrees
		clearTree(node->left);
		node->left = NULL;
		clearTree(node->right);
		node->right = NULL;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    //Checking out a book
    BSTNode* node = find(title, author);
    while (node != NULL) {
        //Will run until finds first book that isnt already checked out
        if (node->book->checked_out == false) {
            node->book->checked_out = true; //checks out the book
            return true; //returns it ran successfully
        }
        node = find(title, author, node->right); //finds next copy of book, if multiple exist
    }
    return false; //in case no book could be checked out
}

bool BST::checkIn(string title, string author) {
    //Checking in a book
    BSTNode* node = find(title, author);
    while (node != NULL) {
        //Checks in the first book that needs to be checked in
        if (node->book->checked_out == true) {
            node->book->checked_out = false; //checks in the book
            return true; //returns that it ran successfully
        }
        node = find(title, author, node->right); //finds next copy, if multiple exist
    }
    return false; //in case it could not check in a book
}


void BST::updateRating(string title, string author, float newRating) {
    BSTNode* bookPoint = find(title, author); //finds the book that needs to be updated
    while(bookPoint != NULL) {
        //runs until every book that needs updating has been updated
            bookPoint->book->rating = newRating; //updates books rating
            bookPoint = find(title, author, bookPoint->right); //checks for copy of book
    }
    return;
}


BSTNode *BST::removeNoKids(BSTNode *node) {
    //Removing a node when it has no children
    if (node == root) { //if node we are removing is root
        root = NULL;
        return node;
    }

    BSTNode* parent = node->parent;
    if(parent != NULL){ //Removing node and reassigning parents child pointer
        if (parent->left == node) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        setHeight(root);
    }
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    BSTNode* child;
    if (leftFlag) { //If node is on the left
        child = node->left;
    }
    else { //If node is on the right
        child = node->right;
    }
    if ((node->parent == NULL) || (node == root)) { //If node is root
        root = child; //setting the root to child
        child->parent = NULL; //updating root's parent
    }
    else {
        if (node->parent->left == node) { //If node is on left of parent
            node->parent->left = child;
            child->parent = node->parent;
        }
        else { //If node is on right of parent
            node->parent->right = child;
            child->parent = node->parent;
        }
    }
    setHeight(root);

    return node;
}

BSTNode *BST::remove(string title, string author) {
    BSTNode* finder = find(title, author, root);
    if (finder == NULL) { //If node was not found
        return NULL;
    }

    //No Kids
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
        //replaces node with right child
        BSTNode *hold = finder->right;
        while (hold->left != NULL) { //Finds left node to set as new left child of new parent
            hold = hold->left;
        }
        //If the leftmost node is not the child of the node we are removing
        if (hold->parent != finder) {
            hold->parent->left = hold->right;
            if (hold->right != NULL) {
                hold->right->parent = hold->parent;
            }
            hold->right = finder->right;
            finder->right->parent = hold;
        }
        //if the node we are removing is the root
        if (finder->parent == NULL || finder == root) {
            root = hold;
            hold->parent = NULL;
        }
        else {
            //set removed nodes left child's parent to the new parent and update connections
            if (finder->parent->left == finder) {
                finder->parent->left = hold;
            }
            else {
                finder->parent->right = hold;
            }
            hold->parent = finder->parent;
        }
        hold->left = finder->left;
        finder->left->parent = hold;
        setHeight(root); //Update heights
        //So no pointer errors
        finder->left = NULL;
        finder->right = NULL;
        finder->parent = NULL;
        return finder;
    }
}

void BST::setHeight(BSTNode *node) {
    //Sets the height of nodes, from the bottom up to the root, starting
    node->height = 0; //resets height to 0
    if (node->left != NULL) { //If node has left child, recursively call on left children
        setHeight(node->left);
    }
    if (node->right != NULL) { //Recursively call on right children
        setHeight(node->right);
    }
    if ((node->left == NULL) && (node->right == NULL)) { //check if node is a leaf
        BSTNode* hold = node;
        int val = 1;
        while (hold != NULL) { //runs while hold is real values
            if (hold->height > val) { //end function when heights are set correctly
                return;
            }
            hold->height = val;
            val = val + 1;
            hold = hold->parent;
            //previous three lines reassign height of hold node, increment val by 1, and move to hold nodes parent up the tree
        }
    }
}