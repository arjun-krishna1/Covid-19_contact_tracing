#include <iostream>
#include <vector>
#include <stack>
#include "final_assignment.hpp"

using namespace std;

// CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Default/empty constructor
ContactGraph::ContactGraph() {}

//Get the number of nodes in this graph
int ContactGraph::get_num_nodes()
{
	return nodes.size();
}

bool ContactGraph::does_edge_exist(string person1_id, string person2_id)
{
	GraphNode *person1 = find_node(person1_id);
	GraphNode *person2 = find_node(person2_id);

	// If they are not in the graph return false
	if (person1 == NULL || person2 == NULL)
		return false;

	bool edge_exists = false;
	for (GraphEdge *edge : edges[person1->loc]->connections)
	{
		if (edge->ending_location == person2)
			edge_exists = true;
	}

	return edge_exists;
}
bool ContactGraph::insert(vector<string> node_id, vector<bool> node_status)
{
	if (node_id.empty() || node_id.size() != node_status.size())
		return false;

	int start_loc = nodes.size();
	for (int i = 0; i < node_id.size(); i++)
	{
		GraphNode *current = new GraphNode(GraphNode(node_id[i], node_status[i], start_loc));
		nodes.push_back(current);
		edges.push_back(new GraphEdges(GraphEdges(current)));
		start_loc++;
	}
	return true;
}

bool ContactGraph::add_edge(string person1_id, string person2_id)
{
	GraphNode *person1 = find_node(person1_id);
	GraphNode *person2 = find_node(person2_id);

	//If the people are not in the graph
	if (person1 == NULL || person2 == NULL)
		return false;

	//Go to person1's linked list and add a new connection to person2
	edges[person1->loc]->connections.push_back(new GraphEdge(person2));
	//Go to person2's linked list and add a new connection to person1
	edges[person2->loc]->connections.push_back(new GraphEdge(person1));

	return true;
}

ContactGraph::GraphNode *ContactGraph::find_node(string person_id)
{
	// base case
	if (person_id == "" || nodes.empty())
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

bool ContactGraph::node_in_list(ContactGraph::GraphNode *current, vector<ContactGraph::GraphNode *> list)
{
	bool exists = false;
	for (ContactGraph::GraphNode *node : list)
	{
		if (node->id == current->id)
		{
			exists = true;
			break;
		}
	}
	return exists;
}
// PURPOSE: traverse the graph starting at person_id and return the nodes that are connected to its
vector<ContactGraph::GraphNode *> ContactGraph::traverse_graph(string person_id)
{
	//Get the node belonging to this ids
	GraphNode *start = find_node(person_id);

	// If the node isn't in the graph, return an empty vector
	if (start == NULL)
		return vector<ContactGraph::GraphNode *>();

	//Prepare variables for traversal
	vector<GraphNode *> visited_list, to_visit;
	to_visit.push_back(start);

	//Iterate while we have more nodes to visit
	while (!to_visit.empty())
	{
		//Visit the last node in to_visit
		ContactGraph::GraphNode *current = to_visit.back();
		to_visit.pop_back();
		visited_list.push_back(current);

		//Get the edges of current
		vector<ContactGraph::GraphEdge *> current_edges = edges[current->loc]->connections;

		//Add any unvisited nodes this node is connected to to to_visit
		for (GraphEdge *edge : current_edges)
		{
			bool visited = false;
			visited = node_in_list(edge->ending_location, visited_list);
			visited = node_in_list(edge->ending_location, to_visit) || visited;

			if (!visited)
				to_visit.push_back(edge->ending_location);
		}
	}
	//Return all of the nodes this node is connected to
	return visited_list;
}
// who tested positive who are directly connected to the starting individual
int ContactGraph::count_virus_positive_contacts(string person_id)
{
	/*
	INPUT: graph, person_id
	OUTPUT: number of distinct individuals who tested positive for the virus and are connected (directly or indirectly)
			to the node at person_id

	*/
	//Get the starting node
	ContactGraph::GraphNode *start = find_node(person_id);
	// If they are not in the graph
	if (start == NULL)
		return 0;

	//Get traversal of graph
	vector<ContactGraph::GraphNode *> traversal = traverse_graph(person_id);

	unsigned int num_positive_contacts = 0;

	//Skip the starting node itself
	for (int i = 1; i < traversal.size(); i++)
	{
		//If this person in the traversal is positive
		if (traversal[i]->status == true)
			num_positive_contacts++;
	}
	return num_positive_contacts;
}

int ContactGraph::find_largest_cluster_with_two_positive()
{
	int max_cluster_size = 0;
	//Iterate through each node in the graph
	for (ContactGraph::GraphNode *node : nodes)
	{
		//Get the number of positive nodes
		int num_positive = count_virus_positive_contacts(node->id);
		//Get number of people in this cluster
		int cluster_size = traverse_graph(node->id).size();
		if (num_positive >= 2 && cluster_size > max_cluster_size)
			max_cluster_size = cluster_size;
	}

	if(max_cluster_size >= 2) 
		return max_cluster_size;

	else
		return -1;
}
