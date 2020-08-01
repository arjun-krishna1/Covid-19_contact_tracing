#include <iostream>
#include <vector>
#include "final_assignment.hpp"

using namespace std;

// CONSTRUCTOR AND DESTRUCTOR

// PURPOSE: Default/empty constructor
ContactGraph::ContactGraph() {
	num_nodes=0;
	num_edges=0;
}

// PURPOSE: traverse the graph starting at person_id and count the distinct individuals 
// who tested positive who are directly connected to the starting individual
int ContactGraph::count_virus_positive_contacts(string person_id);