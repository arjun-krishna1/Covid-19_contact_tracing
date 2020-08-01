#include <iostream>
#include <vector>
#include <stack>
#include "final_assignment.hpp"

using namespace std;

// CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Default/empty constructor
ContactGraph::ContactGraph() {
	num_nodes=0;
	num_edges=0;
}

ContactGraph::GraphNode* ContactGraph::find_node(string person_id) {
	// base case
	if(person_id==""||nodes.size()==0) return NULL;
	//Look for the person in nodes
	for(int i = 0; i < nodes.size();i++) {
		if(person_id==nodes[i]->id) return nodes[i];
	}
	//if not found return null
	return NULL;
}
// PURPOSE: traverse the graph starting at person_id and count the distinct individuals 
// who tested positive who are directly connected to the starting individual
int ContactGraph::count_virus_positive_contacts(string person_id) {
	/*
	INPUT: graph, person_id
	OUTPUT: number of distinct individuals who tested positive for the virus and are connected (directly or indirectly)
			to the node at person_id

	*/
	//Get the starting node
	GraphNode* start = find_node(person_id);

	// If they are not in the graph 
	if(start==NULL) return 0;

	//Init an array to remember the visited nodes, push start into vector
	vector<GraphNode*> visited;
	visited.push_back(start);

	
	
	//Get all of the nodes start is connected to
	vector<GraphNode*>to_visit;
	to_visit.push_back(start);
	//Iterate while there are nodes to visit
	while(!to_visit.empty()) {
		//Remove a node, current, from to_visit and mark it as visited
		GraphNode* current = to_visit.back();
		visited.push_back(current);

		// Get current's adjacency set
		vector<GraphEdge*> connections = edges[current->loc]->connections;

		//Iterate through connections and insert any unvisited nodes to to_visit
		for(GraphEdge* edge:connections) {
			GraphNode* ending_location = edge->ending_location;
			bool un_visited=true;
			//Check if this node is unvisited
			for(GraphNode* node:visited) {
				if(node==ending_location) un_visited=false;
			}

			//If we have not visited it yet addd it to to_visit
			if(un_visited) to_visit.push_back(ending_location);
		}
	}

	int positive_contacts;
	for(GraphNode* node:visited) {
		if(node->status==true && !(node==start))
			positive_contacts++;
	}

	return positive_contacts;
}