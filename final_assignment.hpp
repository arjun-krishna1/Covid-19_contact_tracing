#ifndef LAB3_BINARY_SEARCH_TREE_HPP
#define LAB3_BINARY_SEARCH_TREE_HPP

#include <string>

using namespace std;

// PURPOSE: Represent a version of the Covid-19 contact tracing graph
class ContactTracing {
protected:
	// PURPOSE: Models a single Task Item as a Tree Node
	struct TaskItem {
		int priority, avlBalance; // normal priority values are greater than zero
		string description; // task description
		TaskItem(int new_priority, string new_desc) :
			priority(new_priority), avlBalance(0),
			description(new_desc), left(NULL), right(NULL) {}
		TaskItem* left;    // pointer to the left node
		TaskItem* right;   // pointer to the right node
		bool operator==(const TaskItem& rhs) {
			bool are_equal = priority == rhs.priority;
			// uncomment the next line if needed for the AVL implementation
			/* are_equal = are_equal && avlBalance == rhs.avlBalance; */
			return are_equal && description == rhs.description;
		}
	};

	friend class BinarySearchTreeTest;

	// pointer to the root node of the tree	
	TaskItem* root;

	// number of nodes in the tree
	unsigned int size;

public:
	// CONSTRUCTOR AND DESTRUCTOR

	// PURPOSE: Default/empty constructor
	BinarySearchTree();

	// PURPOSE: Explicit destructor of the class BinarySearchTree
	~BinarySearchTree();

	// ACCESSORS  
	// PURPOSE: Returns the number of nodes in the tree
	unsigned int get_size() const;

	// PURPOSE: Returns the maximum value of a node in the tree
	// if the tree is empty, it returns (-1, "N/A")
	TaskItem max() const;

	// PURPOSE: Returns the minimum value of a node in the tree
	// if the tree is empty, it returns (-1, "N/A")
	TaskItem min() const;

	// PURPOSE: Returns the tree height
	unsigned int height() const;
	unsigned int height_helper(TaskItem* root) const;

	//PURPOSE: Recursive helper for the height function
	// unsigned int height_helper(const TaskItem *r, unsigned int h){

	// PURPOSE: Prints the contents of the tree; format not specified
	void print() const;

	//PURPOSE: Use recursion to print tree in pre-order
	void pre_order_print_helper(TaskItem *r ) const;
	// PURPOSE: Returns true if a node with the value val exists in the tree	
	// otherwise, returns false
	bool exists(TaskItem val) const;

	// PURPOSE: Optional helper function that returns a pointer to the root node
	TaskItem* get_root_node();

	// PURPOSE: Optional helper function that returns the root node pointer address
	TaskItem** get_root_node_address();

	// PURPOSE: Optional helper function that gets the maximum depth for a given node
	int get_node_depth(TaskItem* n) const;

	// MUTATORS

	// PURPOSE: Inserts the value val into the tree if it is unique
	// returns true if successful; returns false if val already exists
	bool insert(TaskItem val);

	// PURPOSE: Removes the node with the value val from the tree
	// returns true if successful; returns false otherwise
	bool remove(TaskItem val);
};

class AVLTree : public BinarySearchTree {
	// Define additional functions and attributes that you need below	

public:
	// PURPOSE: Overrides the BST insert function to keep the tree balanced
	bool insert(TaskItem val);
	// PURPOSE: Update the avl balance of all of the nodes
	void updateNodeBalance(TaskItem* root);
	// PURPOSE: Check if all the tree is balanced, if not conduct the necessary rotations to balance it
	void balanceAVLTree(TaskItem* T, TaskItem* T_parent);
	// PURPOSE: Rotate the tree right around T
	void singleRightRotation(TaskItem* T, TaskItem* T_parent);
	// PURPOSE: Rotate the tree left around T
	void singleLeftRotation(TaskItem* T, TaskItem* T_parent);
};
#endif