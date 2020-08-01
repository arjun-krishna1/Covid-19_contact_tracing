#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree(): root(NULL), size(0) {}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	// (*this) = BinarySearchTree();
	//Delete this root
	delete root;
	//remove dangling pointer
	root = NULL;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	//If the tree is empty
	if(!root) return BinarySearchTree::TaskItem(-1, "N/A");

	else{
		//Start at the root
		TaskItem* curr = root;

		//Traverse to the right most node, which should have the maximum value
		while(curr->right) curr = curr->right;

		return *curr;
	}
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	//If the tree is empty
	if(!root) return BinarySearchTree::TaskItem(-1, "N/A");

	else{
		//Start at the root
		TaskItem* curr = root;

		//Traverse to the left most node, which should have the minimum value
		while(curr->left) curr = curr->left;

		return *curr;
	}
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {

	return height_helper(root);
}

unsigned int BinarySearchTree::height_helper(TaskItem* T) const {
	
	//If this tree is empty return 0
	if (!T) 
		return 0;

	//If there is only one node return 0
	if (!T->left && !T->right) 
		return 0;

	int left_height = 0;
	//If this tree is empty return 0
	if (T->left) 
		left_height = height_helper(T->left)+1;

	int right_height = 0;
	if (T->right) 
		right_height = height_helper(T->right)+1;

	int max_height = 0;
	if(right_height > left_height){
		max_height = right_height;
	} 
	else{
		max_height = left_height;
	}
	return  max_height;
}



// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	pre_order_print_helper(root);
	cout << endl;
}

// PURPOSE: Recursively print the values of the binary search tree in pre-order
void BinarySearchTree::pre_order_print_helper(BinarySearchTree::TaskItem* n) const {
	if(n){
		cout << n->priority << " ";

		if(n->left)
			pre_order_print_helper(n->left);

		if(n->right)
			pre_order_print_helper(n->right);
	}
}
// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
	
	//If the tree is empty
	if(root==NULL){
		return false;
	}
	
	TaskItem* curr = root;
	TaskItem* prev;

	//Iterate through the tree while we are not at a leaf node or at val
	while( curr!=NULL){
		//Move left
		if(val.priority > curr->priority){
			prev = curr;
			curr = curr->right;
		}
		//Move right
		else if(val.priority < curr->priority){
			prev = curr;
			curr = curr->left; 
		}

		else if(val==*curr)
			return true;
	}

	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth(BinarySearchTree::TaskItem* n) const {
	//Check if the tree is empty or only has one node
	bool empty_or_single_node = n==NULL;
	empty_or_single_node = empty_or_single_node || (n->left == NULL && n->right == NULL) ;

	if(empty_or_single_node)
		return 0;

	//Else 
	else{
		//Return the maximum depth of both of its branches
		int left_depth = n->left==NULL ? 0:(get_node_depth(n->left) + 1);
		int right_depth = n->right==NULL ? 0:(get_node_depth(n->right) + 1);
		return left_depth > right_depth? left_depth : right_depth;
	}
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val) {
	
	//Copy into dynamic memory	
	TaskItem* target = new TaskItem(val);
	
	//If the tree is empty
	if(root==NULL){
		root = target;
		size++;
		return true;
	}
	
	TaskItem* curr = root;
	TaskItem* prev;

	//Iterate through the tree while we are not at a leaf node or at a duplicate
	while( curr!=NULL && curr!=target){
		//If the value we want to insert is greater than the current node's value, move right
		if(target->priority > curr->priority){
			if(curr->right == NULL){
				curr->right =new  TaskItem(val);
				size++;
				
				delete target;
				target = NULL;
				return true;
			} else{
				prev = curr;
				curr = curr->right;
			}
		}
		//If the value we want to insert is less than the current node's value, move left
		else if(target->priority < curr->priority){
			if(curr->left == NULL){
				curr->left =new  TaskItem(val);
				size++;
				delete target;
				target = NULL;
				return true;
			} else{
				prev = curr;
				curr = curr->left;
			}
		}
		else if(target->priority == curr->priority){
			delete target;
			target = NULL;
			return false;
		}
	}
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
	//If val is not in this tree
	if(!exists(val)){
		return false;
	}
	//reduce the size
	size --;


	//Find val and it's parent
	TaskItem* current = root;
	TaskItem* prev = NULL;
	while(val.priority != current->priority){
		prev = current;
		if(val.priority < current->priority)
			current = current->left;

		else if(val.priority > current->priority)
			current = current->right;
	}
	//case 1: no children
	if(current->left == NULL && current->right ==NULL){
		//We are removing the root
		if(prev == NULL){
			delete root ;
			root = NULL;
		}
		else if(current == prev->left){
			delete prev->left;
			prev->left == NULL;
		}
		else if(current == prev->right){
			delete prev->right;
			prev->right = NULL;
		}
		return true;
	}

	//case 2: one child
	//child is right
	else if(current->left == NULL && current->right !=NULL){
		//We are removing the root
		if(prev == NULL){
			root = current->right;
		}
		else if(current == prev->left){
			prev->left = current->right;
		}
		else if(current == prev->right){
			prev->right = current->right;
		}
		return true;
	}

	//child is left
	else if(current->left != NULL && current->right ==NULL){
		//We are removing the root
		if(prev == NULL){
			root = current->left;
		}
		else if(current == prev->left){
			prev->left = current->left;
		}
		else if(current == prev->right){
			prev->right = current->left;
		}
		return true;
	}
	
	//case 3
	else if(current->left != NULL && current->right != NULL){
		
		//Find the predecessor
		TaskItem* pred = current->left;
		TaskItem* pred_parent = current;

		while(pred->right){
			pred_parent = pred;
			pred = pred->right;
		}
		
		
		//Swap the values
		if(*pred_parent == val){
			//Delete the predecessor
			pred_parent->left = pred_parent->left->left;
			// root->left = NULL;
			
		}

		else {
			pred_parent->right = pred_parent->right->left;
		}
		current->priority = pred->priority;
		return true;
	}
}

void AVLTree::singleRightRotation(TaskItem* P, TaskItem* parent ){
	TaskItem* Q = P->left;
	//If root
	if(P == root)
		root = Q;

	//Swap P with Q
	else if(parent && P == parent->right){
		parent->right = Q;
	}
	else if(parent && P == parent->left){
		parent->left = Q;
	}

	TaskItem* temp = Q->right;
	Q->right = P;
	P->left = temp;
}

void AVLTree::singleLeftRotation(TaskItem* P, TaskItem* parent){
	TaskItem* Q = P->right;
	if(P==root)
		root = Q;
	//Swap P with Q
	if(parent && P == parent->right){
		parent->right = Q;
	}
	else if(parent && P == parent->left){
		parent->left = Q;
	}
	

	TaskItem* temp = Q->left;
	Q->left = P;
	P->right = temp;
}

void AVLTree::updateNodeBalance(TaskItem* T ){
	
	if(T != NULL) {
		
		int l_height = 0;
		if(T->left)
			l_height = height_helper(T->left)+1;
		// print();
		int r_height = 0;
		if(T->right)
			r_height = height_helper(T->right)+1;
		
		T->avlBalance = l_height - r_height;

		updateNodeBalance(T->left);
		updateNodeBalance(T->right);
	}
}
void AVLTree::balanceAVLTree(TaskItem* T, TaskItem* parent){
	
	if(T){
		updateNodeBalance(root);	
		
		//balance the rest of the tree
		balanceAVLTree(T->left, T);
		balanceAVLTree(T->right, T);
		
		
		//Double Left right rotation
		if(T->avlBalance > 1 && T->left && T->left->avlBalance < 0){
			
			singleLeftRotation(T->left, T);
			singleRightRotation(T, parent);
		}
		//Double right left rotation
		else if(T->avlBalance < -1 && T->right && T->right->avlBalance > 0){
			
			singleRightRotation(T->right, T);
			singleLeftRotation(T, parent);
		}
		else if(T->avlBalance > 1){
			
			//Single right rotation
			singleRightRotation(T, parent);
		}

		else if(T->avlBalance < -1){
			
			//Single left rotation
			singleLeftRotation(T, parent);
		}
		
		
		//Update node balance
		updateNodeBalance(root);
	}
}

// PURPOSE: Inserts the value into the tree while keeping the tree balanced
// returns true if successful; returns false if val already exists
bool AVLTree::insert(BinarySearchTree::TaskItem val) {
	bool success = BinarySearchTree::insert(val);

	updateNodeBalance(root);
	balanceAVLTree(root, nullptr);
	

	return success;
}


