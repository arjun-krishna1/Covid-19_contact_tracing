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
        ContactGraph graph = ContactGraph();

        //Check insert
        vector<string> names = {"Nate", "Olivia", "Jess", "Shelley"};
        vector<bool> status = {1, 1, 0, 0};
        valid = graph.insert(names, status);
        valid = (graph.get_num_nodes() == 4);

        //Check search and validity of inserts
        ContactGraph::GraphNode *node = graph.find_node(names[3]);
        valid = node->id == names[3];

        //Check add edges functionality
        vector<vector<int>>edges={{0,1},{0,2},{1,3},{1,2},{2,3}};
        for( vector<int>edge : edges) graph.add_edge(names[edge[0]], names[edge[1]]);

        valid=graph.does_edge_exist(names[0], names[1]);
        valid=graph.does_edge_exist(names[2], names[3]);
        valid=!graph.does_edge_exist(names[0], names[3]);
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
