#include <iostream>
#include <vector>
#include <stack>
#include "final_assignment.hpp"

using namespace std;

// CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Default/empty constructor
ContactGraph::ContactGraph(){}

//Get the number of nodes in this graph
int ContactGraph::get_num_nodes()
{
	return nodes.size();
}

bool ContactGraph::does_edge_exist(string person1_id, string person2_id) {
	GraphNode* person1 = find_node(person1_id);
	GraphNode* person2 = find_node(person2_id);

	// If they are not in the graph return false
	if(person1==NULL||person2==NULL) return false;

	bool edge_exists = false;
	for(GraphEdge* edge: edges[person1->loc]->connections) {
		if(edge->ending_location==person2) edge_exists=true;
	}

	return edge_exists;
}
bool ContactGraph::insert(vector<string> node_id, vector<bool> node_status)
{
	if (node_id.size() == 0 || node_id.size() != node_status.size())
		return false;

	int start_loc = nodes.size();
	for (int i = 0; i < node_id.size(); i++)
	{
		GraphNode* current =new GraphNode(GraphNode(node_id[i], node_status[i], start_loc));
		nodes.push_back(current);
		edges.push_back(new GraphEdges(GraphEdges(current)));
		start_loc++;
	}
	return true;
}

bool ContactGraph::add_edge(string person1_id, string person2_id) {
	GraphNode* person1 = find_node(person1_id);
	GraphNode* person2 = find_node(person2_id);

	//If the people are not in the graph
	if(person1==NULL||person2==NULL) return false;

	//Go to person1's linked list and add a new connection to person2
	edges[person1->loc]->connections.push_back(new GraphEdge(person2));
	//Go to person2's linked list and add a new connection to person1
	edges[person2->loc]->connections.push_back(new GraphEdge(person1));
	
	return true;
}

ContactGraph::GraphNode* ContactGraph::find_node(string person_id)
{
	// base case
	if (person_id == "" || nodes.size() == 0)
		return NULL;
	//Look for the person in nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		if (person_id == nodes[i]->id)
			return nodes[i];
	}
	//if not found return null
	return NULL;
}
// PURPOSE: traverse the graph starting at person_id and count the distinct individuals
// who tested positive who are directly connected to the starting individual
int ContactGraph::count_virus_positive_contacts(string person_id)
{
	/*
	INPUT: graph, person_id
	OUTPUT: number of distinct individuals who tested positive for the virus and are connected (directly or indirectly)
			to the node at person_id

	*/
	//Get the starting node
	GraphNode *start = find_node(person_id);

	// If they are not in the graph
	if (start == NULL)
		return 0;

	//Init an array to remember the visited nodes, push start into vector
	vector<GraphNode *> visited, to_visit;
	to_visit.push_back(start);

	unsigned int num_positive_connections=0;

	return positive_contacts;
}
