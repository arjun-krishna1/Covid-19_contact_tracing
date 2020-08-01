#include <iostream>
#include <string>
#include "final_assignment.hpp"

using namespace std;

class ContactGraphTest
{
public:
	// PURPOSE: Tests if the new graph is valid
	bool test1()
	{
		//Nodes to insert

		ContactGraph graph = ContactGraph();
        vector<string>names = {"Nate", "Olivia", "Jess", "Shelley"};
        vector<bool>status = {1,1,0,0};
		graph.insert(names, status);
		cout << (graph.get_num_nodes()==4) << endl;
		return 1;
	}
};

int main()
{
    ContactGraphTest test;

    bool valid = test.test1();
    cout << valid << endl;
    cout << "Hello" << endl;
}
