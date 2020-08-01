#ifndef FINAL_ASSIGNMENT
#define FINAL_ASSIGNMENT

#include <string>
#include <vector>

using namespace std;

// PURPOSE: Represent a version of the Covid-19 contact tracing graph
class ContactGraph
{
protected:
	// PURPOSE: Represent an individual in a specific area
	struct GraphNode
	{
		string id, name, date; // information about the individual and the date they were last tested
		bool status;		   //infection status
		unsigned int loc;			   //It's place in the insertion order

		// Default Constructor
		GraphNode(string new_id, bool new_status) : id(new_id), status(new_status), name(""), date("") {}
	};

	//PURPOSE: Represent the most recent contact between two individuals
	struct GraphEdge
	{
		GraphNode* ending_location;   //the two people who contacted each other
		unsigned int time; //The number of days between the contact and the day it was reported
		string loc;

		// GraphEdge(GraphNode *new_a, GraphNode *new_b, unsigned int new_time) : a(new_a), b(new_b), time(new_time) {}
	};

	//PURPOSE: store the contacts between the starting node and all of the other nodes
	struct GraphEdges
	{
		GraphNode* starting_loc;
		vector<GraphEdge*> connections;
	};

	// set of all nodes in graph
	vector<GraphNode*> nodes;

	// list of linked lists that specifies all edges that originate at each node
	vector<GraphEdges*> edges;

	// store the number of nodes and edges
	unsigned int num_nodes, num_edges;

public:
	// CONSTRUCTOR AND DESTRUCTOR

	// PURPOSE: Default/empty constructor
	ContactGraph();

	// PURPOSE: Explicit destructor of the class BinarySearchTree
	~ContactGraph();

	// ACCESSORS
	// PURPOSE: Returns the number of nodes in the tree
	unsigned int get_num_nodes() const;
	unsigned int get_num_edges() const;

	GraphNode* find_node(string person_id, int&loc);
	// PURPOSE: traverse the graph starting at person_id and count the distinct individuals 
	// who tested positive who are directly connected to the starting individual
	int count_virus_positive_contacts(string person_id);
};
#endif