#ifndef GRAPH
#define GRAPH

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
		unsigned int loc;	   //It's place in the insertion order

		// Default Constructor
		GraphNode(string new_id, bool new_status, unsigned int new_loc) : id(new_id), status(new_status), name(""), date(""), loc(new_loc) {}
		GraphNode(string new_id, string new_name, string new_date, bool new_status, unsigned int new_loc) : id(new_id), status(new_status), name(new_name), date(new_date), loc(new_loc) {}
	};

	//PURPOSE: Represent the most recent contact between two individuals
	struct GraphEdge
	{
		GraphNode *ending_location; //the two people who contacted each other
		unsigned int time;			//The number of days between the contact and the day it was reported
		string loc;

		GraphEdge(GraphNode *new_end) : ending_location(new_end) {}
	};

	//PURPOSE: store the contacts between the starting node and all of the other nodes
	struct GraphEdges
	{
		GraphNode *starting_loc;
		vector<GraphEdge *> connections;

		GraphEdges(GraphNode *new_node) : starting_loc(new_node) {}
	};

	friend class ContactGraphTest;
	// set of all nodes in graph
	vector<GraphNode *> nodes;

	// list of linked lists that specifies all edges that originate at each node
	vector<GraphEdges *> edges;

public:
	// CONSTRUCTOR AND DESTRUCTOR
	// PURPOSE: Default/empty constructor
	ContactGraph();

	//GETTER
	//Get the number of nodes in this graph
	int get_num_nodes();
	//Get the existence of an edge between these two nodes
	bool does_edge_exist(string person1, string person2);
	void infect(string person1_id);

	bool insert(vector<string> node_id, vector<bool> node_status);
	bool insert(vector<string> node_id, vector<string> node_name, vector<string> date, vector<bool> node_status);
	bool add_edge(string person1_id, string person2_id);
	// PURPOSE: Find a node given its id and find its o
	GraphNode *find_node(string person_id);

	bool node_in_list(GraphNode *current, vector<GraphNode *> list);

	vector<GraphNode *> traverse_graph(string person_id);

	// PURPOSE: traverse the graph starting at person_id and count the distinct individuals in their network who have tested positive
	int count_virus_positive_contacts(string person_id);

	//PURPOSE: find the
	int find_largest_cluster_with_two_positive();

	//File Interface
	bool store_graph(string file_name);
	bool load_graph(string file_name);

	GraphNode* find_same_status_node(ContactGraph::GraphNode* cluster);

	GraphNode* find_friend(ContactGraph::GraphNode* needs_friend);	
	
};
#endif