#include <iostream>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include "graph.hpp"

using namespace std;

// CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Default/empty constructor
ContactGraph::ContactGraph() {}

//Get the number of nodes in this graph
int ContactGraph::get_num_nodes()
{
	return nodes.size();
}

//See if the two people have reported an interaction
bool ContactGraph::does_edge_exist(string person1_id, string person2_id)
{
	// Get their nodes
	GraphNode *person1 = find_node(person1_id);
	GraphNode *person2 = find_node(person2_id);

	// If they are not in the graph return false
	if (person1 == NULL || person2 == NULL)
		return false;

	// Else iterate through each edge and see if one of them is between these two
	bool edge_exists = false;
	for (GraphEdge *edge : edges[person1->loc]->connections)
	{
		if (edge->ending_location == person2)
			edge_exists = true;
	}

	return edge_exists;
}

// Search for any infected individuals
void ContactGraph::infect(string infect_id) {
	for(int i=0; i<ContactGraph::nodes.size(); i++) {
		//If found infect them and break
		if(nodes[i]->id==infect_id) {
			nodes[i]->status=1;
			break;
		}
	}
}

// Insert a new node into the graph given a set of strings and their infection status
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

// Insert a new node into the graph given a set of strings, their infection status and other info
// about them
bool ContactGraph::insert(vector<string> node_id, vector<string> node_name, vector<string> node_date, vector<bool> node_status)
{
	if (node_id.empty() || node_id.size() != node_status.size())
		return false;

	int start_loc = nodes.size();
	for (int i = 0; i < node_id.size(); i++)
	{
		GraphNode *current = new GraphNode(GraphNode(node_id[i], node_name[i], node_date[i], node_status[i], i + start_loc));
		nodes.push_back(current);
		edges.push_back(new GraphEdges(GraphEdges(current)));
	}
	return true;
}

// Add an interaction between two individuals in the graph
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

// See if a person is in this network
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

// See if a person is in a given list
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

// see how many covid-positive people this person has come in contact with
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

// find the largest cluster of connections with two covid positive people
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

	if (max_cluster_size >= 2)
		return max_cluster_size;

	else
		return -1;
}

//output the graph to a file
bool ContactGraph::store_graph(string file_name)
{
	//create file
	ofstream file;
	file.open(file_name);

	//file couldn't be opened
	if (!file.is_open())
		return false;

	file << "NODE INFORMATION\n";
	file << "FORMAT: ID,NAME,DATE,STATUS\n\n";
	//Write names of graphs in order
	for (GraphNode *node : nodes)
	{
		file << node->id << "," << node->name << "," << node->date << "," << node->status << endl;
	}

	file << "\nEDGE INFORMATION\n";
	file << "FORMAT: START\n{END,TIME}\nREPEAT FOR EACH END\n\n";
	for (int i = 0; i < edges.size(); i++)
	{
		file << edges[i]->starting_loc->id << endl;
		for (GraphEdge *edge : edges[i]->connections)
		{
			file << edge->ending_location->id<<endl; //<< "," << edge->time<< endl;
		}
		file << "\n";
	}
	file.close();
	return true;
}

// load a graph from a file
bool ContactGraph::load_graph(string file_name)
{
	string line;
	ifstream file(file_name);
	if (!file.is_open())
		return false;

	const int FIRST_BUFFER=3;
	//Skip format documentation
	for (int i=0; i<FIRST_BUFFER; i++) getline(file, line);

	vector<string> new_id, new_name, new_date;
	vector<bool> new_status;
	//Get node information
	while (getline(file, line) && line != "")
	{
		int num_list = 0;

		//Fill new_id

		vector<string> entries;
		int i = 0;
		for (int j = 0; j < 3; j++)
		{
			string entry = "";
			for (i = i; i < line.size() && line[i] != ','; i++)
			{
				entry += line[i];
			}
			i++;
			entries.push_back(entry);
		}

		new_id.push_back(entries[0]);
		new_name.push_back(entries[1]);
		new_date.push_back(entries[2]);
		bool status_entry = false;
		if (line[i] == '1')
			status_entry = true;

		new_status.push_back(status_entry);
	}

	insert(new_id, new_name, new_date, new_status);
	//Check insert

	//Skip human instructions
	const int SECOND_BUFFER=6;
	for (int i=0; i<SECOND_BUFFER; i++) getline(file, line);

	//Iterate through each node
	for (int i=0; i<new_id.size()&&getline(file, line); i++) {
		vector<ContactGraph::GraphNode*>end;
		//skip the name of the starting node and iterate through its edges
		while (line!=""&&getline(file, line)) {
			add_edge(ContactGraph::nodes[i]->id, line);
		}
	}

	file.close();
	return true;
}

// find a node with the same status in their cluster
ContactGraph::GraphNode* ContactGraph::find_same_status_node(ContactGraph::GraphNode* cluster) {
	//Get their cluster
	vector<ContactGraph::GraphNode*> traversal = traverse_graph(cluster->id);
	//They will have no friends
	if (traversal.size()<=1) return NULL;
	//Find uninfected node in this cluster
	for (GraphNode* node: traversal) {
		//Return this node if it has the same status as cluster and is not itself
		if (node->status==cluster->status && node->id!=cluster->id) return node;
	}

	//No uninfected nodes
	return NULL;
}

// find the least-risk of infection friend within a cluster
ContactGraph::GraphNode* ContactGraph::find_friend(ContactGraph::GraphNode* needs_friend) {
	//Get their cluster
	GraphNode* poss_friend=find_same_status_node(needs_friend);

	//If no uninfected nodes in this cluster find an uninfected node in the cluster 
	//with the least infections
	if (poss_friend!=NULL) return poss_friend;

	else {
		int min_positive=-1;

		for (ContactGraph::GraphNode* node:ContactGraph::nodes) {
			//If this node is not the node that needs a friend
			bool new_friend = node->id!=needs_friend->id;
			//If this node has the same status as the one that needs a friend and the above condiion
			new_friend=new_friend && node->status==needs_friend->status;
			
			int num_positive_cluster=count_virus_positive_contacts(node->id);
			//If this node has less positive nodes in its cluster and the above conditions
			new_friend = (min_positive==-1||num_positive_cluster<min_positive)&&new_friend;

			//Update min_positive
			min_positive = min_positive<num_positive_cluster?min_positive:num_positive_cluster;

			if(new_friend)	poss_friend=node;
		}
	}

	//If we found a negative node
	if(poss_friend!=NULL) return poss_friend;
	//No uninfected nodes
	//Return the first or second node
	return nodes[0]==needs_friend ? nodes[1]:nodes[0];
}