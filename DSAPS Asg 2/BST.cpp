#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}




void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);

}

// display

void BST::reverseInOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	reverseInOrderPrint2(cur->right);
	cur->item.print(cout);
	reverseInOrderPrint2(cur->left);
}

void BST::inOrderPrint2File(BTNode* cur, ofstream& outputFile) {

	if (cur == NULL) return;

	inOrderPrint2File(cur->left, outputFile);
	cur->item.print(outputFile);
	inOrderPrint2File(cur->right, outputFile);
}

void BST::reverseInOrderPrint2File(BTNode* cur, ofstream& outputFile) {

	if (cur == NULL) return;

	reverseInOrderPrint2File(cur->right, outputFile);
	cur->item.print(outputFile);
	reverseInOrderPrint2File(cur->left,outputFile);
}

bool BST::display(int order, int source) {
	if (root == NULL) {
		cout << "Tree is empty" << endl;
		return false;
	}

	ofstream outputFile;

	if (source == 2) {
		outputFile.open("student-info.txt");
		if (!outputFile.is_open()) {
			cout << "Failed to open output file." << endl;
			return false;
		}
	}

	if (order == 1) {
		if (source == 1) {
			inOrderPrint2(root);
		}
		else if (source == 2) {
			inOrderPrint2File(root, outputFile);
			outputFile.close();
		}
	}

	else if (order == 2) {
		if (source == 1) {
			reverseInOrderPrint2(root);
		}
		else if (source == 2) {
			reverseInOrderPrint2File(root, outputFile);
			outputFile.close();
		}
	}

	return true;
}

// print level nodes
bool BST::printLevelNodes() {
	if (root == NULL) {
		cout << "Tree is empty." << endl;
		return false;
	}

	Queue q;
	q.enqueue(root);

	int level = 1;
	int nodes = 1;  // Number of nodes in the current level

	while (!q.empty()) {
		cout << "Level " << level << " nodes: ";
		int nextLevelNodes = 0;

		for (int i = 0; i < nodes; i++) {
			BTNode* cur;
			q.dequeue(cur);

			cout << cur->item.id << " "; 

			if (cur->left != NULL) {
				q.enqueue(cur->left);
				nextLevelNodes++;
			}
			if (cur->right != NULL) {
				q.enqueue(cur->right);
				nextLevelNodes++;
			}
		}
		cout << endl;
		level++;
		nodes = nextLevelNodes;
	}
	return true;
}


bool BST::CloneSubtree(BST t1, type item) {
	Student stu;
	BTNode* tmp = new BTNode(stu);
	if (t1.empty()) {
		cout << "t1 is empty. ";
		return false;
	}

	if (!findNode(item, t1.root, *tmp)) {
		cout << "Can't find node with id " << item.id << endl;
		return false;
	}
	else {
		CloneSubtree2(tmp);
	}
	return true;
}

bool BST::findNode(type item, BTNode* cur, BTNode& tmp) {
	if (cur == NULL) {
		return false;
	}
	if (cur->item.compare2(item)) {
		tmp = *cur;
		return true;
	}
	if (findNode(item, cur->left, tmp))
		return true;
	return findNode(item, cur->right, tmp);
}

void BST::CloneSubtree2(BTNode* cur) {
	if (cur == NULL)
		return;
	insert(cur->item);
	CloneSubtree2(cur->left);
	CloneSubtree2(cur->right);
}

bool BST::deepestNodes() {
	Queue q;
	
	int maxLevel = -1;	//the level of tree without node is -1

	if (root == NULL){
		cout << "The tree is empty." << endl;
		return false;
	}
	findDeepest(root, 0, maxLevel, q);

	if (!q.empty()) {
		cout << "Deepest Nodes: ";
		for (int i = 0; i <= q.size(); i++) {
			BTNode* deepestNode;
			q.dequeue(deepestNode);
			cout << deepestNode->item.id;	//display the id of deepest node
			cout << " ";
		}
	}
	cout << endl;
	return true;
}

void BST::findDeepest(BTNode* root, int level, int& maxLevel, Queue &q) {
	BTNode* cur;
	if (root != NULL) {
		findDeepest(root->left, ++level, maxLevel, q);
		
		if (level > maxLevel) {	//if level of root greater than the current level
			while (!q.empty()) {
				q.dequeue(cur);		//remove the current deepest root so far
			}
			maxLevel = level;
		}

		if (level == maxLevel) {	//if the level of root same with the current level
			q.enqueue(root);		//insert the node as the deepest nodes.
		}
		
		findDeepest(root->right, level, maxLevel, q);
	}
}

bool BST::printPath() {
	// Check if the tree is empty
	if (root == NULL) {
		cout << "Tree is empty. There is no external path to print." << endl;
		return false; 
	}

	cout << "Below are the external paths for the tree:" << endl;
	cout << endl;

	printExternalPaths(root, ""); // 'root' is a pointer which acts as a starting point for transversing the tree
								  // '""' is an empty string (initial path) that will build upon to represent the path to the current node

	return true;
}

void BST::printExternalPaths(BTNode* node, string currentPath) {
	if (node == NULL) { // Stop recursion if the current node is NULL
		return;
	}

	// Append the current node's ID to the path
	if (!currentPath.empty()) {
		currentPath += " "; // Add a space separator between node IDs
	}
	currentPath += to_string(node->item.id); // Convert node ID to a string and append it to the currentPath sting

	// Check if the current node is an external node
	if (node->left == NULL && node->right == NULL) {
		cout << currentPath << endl;
	}
	else {
		// Recursively explore left and right subtrees
		printExternalPaths(node->left, currentPath);
		printExternalPaths(node->right, currentPath);
	}
}
