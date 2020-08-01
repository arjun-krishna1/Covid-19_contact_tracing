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
        bool valid = true;
        //Check insert functionality
        ContactGraph graph = ContactGraph();
        vector<string> names = {"Nate", "Olivia", "Jess", "Shelley"};
        vector<bool> status = {1, 1, 0, 0};
        graph.insert(names, status);
        valid = (graph.get_num_nodes() == 4);

        //Check search and inser functionality
        ContactGraph::GraphNode *node = graph.find_node(names[3]);

        cout << (node->id) << endl;

        valid = node->id == names[3];

        //Check add edges functionality
        graph.add_edge(names[0], names[1]);
        valid=graph.does_edge_exist(names[0], names[1]);
        return valid;
    }
};

int main()
{
    ContactGraphTest test;

    bool valid = test.test1();
    cout << valid << endl;
    cout << "Hello" << endl;
}
