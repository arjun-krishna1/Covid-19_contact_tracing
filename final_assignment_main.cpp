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
        vector<string> names ={ "Nate", "Olivia", "Jess", "Shelley" };
        vector<bool> status ={ 1, 1, 0, 0 };
        valid = graph.insert(names, status) && valid;
        valid = (graph.get_num_nodes() == 4) && valid;

        //Check search and validity of inserts
        ContactGraph::GraphNode *node = graph.find_node(names[3]);
        valid = node->id == names[3] && valid;

        //Check add edges functionality
        vector<vector<int>> edges ={ { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 2 }, { 2, 3 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        valid = graph.does_edge_exist(names[0], names[1]) && valid;
        valid = graph.does_edge_exist(names[2], names[3]) && valid;
        valid = !graph.does_edge_exist(names[0], names[3]) && valid;
        return valid;
    }

    //PURPOSE: Check count_virus_positive_contacts function
    bool test2()
    {
        //Initialize graph and variables
        bool valid = true;
        ContactGraph graph = ContactGraph();

        //Insert nodes into graph
        vector<string> names ={ "Nate", "Olivia", "Jess", "Shelley" };
        vector<bool> status ={ 1, 1, 0, 0 };
        valid = graph.insert(names, status);

        //Create edges in between nodes
        vector<vector<int>> edges ={ { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 2 }, { 2, 3 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Check count_virus_positive_contacts with person_id corresponding to a positive node
        int expected_positive_contacts=1;
        int positive_contacts=graph.count_virus_positive_contacts(names[0]);
        valid = expected_positive_contacts==positive_contacts && valid;

        //Check count_virus_positive_contacts with person_id corresponding to a negative node
        expected_positive_contacts=2;
        positive_contacts=graph.count_virus_positive_contacts(names[2]);
        valid=expected_positive_contacts==positive_contacts && valid;

        //Insert more nodes into graph
        names ={ "Andy", "Kelsey", "Mike", "Maria", "Darryl" };
        status ={ 0, 0, 1, 1, 1 };
        valid = graph.insert(names, status);

        //Create edges between new nodes
        edges ={ { 0, 1 }, { 0, 2 }, { 0, 4 }, { 1, 3 }, { 2, 3 }, { 3, 4 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Check count_virus_positive_contacts with two clusters and a negative node
        expected_positive_contacts=3;
        positive_contacts=graph.count_virus_positive_contacts(names[0]);
        valid = expected_positive_contacts==positive_contacts && valid;

        //Check count_virus_positive_contacts with two clusters and a positive node
        expected_positive_contacts=2;
        positive_contacts=graph.count_virus_positive_contacts(names[2]);
        valid=expected_positive_contacts==positive_contacts && valid;

        //Insert more nodes into a third cluster
        //Insert more nodes into graph
        names ={ "Arjun", "Igor", "Amitav" };
        status ={ 0, 0, 0 };
        valid = graph.insert(names, status);

        //Create edges between new nodes
        edges ={ { 0, 1 }, { 0, 2 }, { 1, 2 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Check count_virus_positive with three clusters on a node within a cluster with no positive nodes
        expected_positive_contacts=0;
        positive_contacts=graph.count_virus_positive_contacts(names[0]);
        valid=expected_positive_contacts==positive_contacts && valid;

        return valid;
    }

    //PURPOSE: test largest cluster with multiple virus-positive contacts
    bool test3() {
        //Initialize graph and variables
        bool valid = true;
        ContactGraph graph = ContactGraph();

        //Insert nodes into graph
        vector<string> names ={ "Nate", "Olivia", "Jess", "Shelley" };
        vector<bool> status ={ 0, 0, 1, 0 };
        valid = graph.insert(names, status);

        //Create edges between nodes
        vector<vector<int>> edges ={ { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 2 }, { 2, 3 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Test with a cluster with less than two positive nodes
        int expected_cluster_size = -1;
        int cluster_size = graph.find_largest_cluster_with_two_positive();
        valid = expected_cluster_size==cluster_size && valid;

        //Insert new nodes into graph
        names ={ "Andy", "Kelsey", "Mike", "Maria", "Darryl" };
        status ={ 0, 0, 1, 1, 1 };
        valid = graph.insert(names, status);

        //Create edges between nodes
        edges ={ { 0, 1 }, { 0, 2 }, { 0, 4 }, { 1, 3 }, { 2, 3 }, { 3, 4 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Test with two clusters where only one has more than two positive nodes
        expected_cluster_size = 5;
        cluster_size = graph.find_largest_cluster_with_two_positive();
        valid = expected_cluster_size==cluster_size && valid;

        //Insert new nodes into graph
        names ={ "Arjun", "Igor", "Amitav" };
        status ={ 1, 1, 1 };
        valid = graph.insert(names, status);

        //Create edges between nodes
        edges ={ { 0, 1 }, { 0, 2 }, { 1, 2 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Test with three clusters where two clusters have more than two positive nodes
        expected_cluster_size = 5;
        cluster_size = graph.find_largest_cluster_with_two_positive();
        valid = expected_cluster_size==cluster_size && valid;
        return valid;
    }

    //PURPOSE: test file reading and writing
    bool test4() {
        //Create graph
        ContactGraph graph = ContactGraph();

        //Insert nodes into graph
        vector<string> names ={ "Nate", "Olivia", "Jess", "Shelley" };
        vector<bool> status ={ 1, 1, 0, 0 };
        graph.insert(names, status);

        //Create edges in between nodes
        vector<vector<int>> edges ={ { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 2 }, { 2, 3 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);


        //Write to file
        string name = "network.txt";
        bool success = graph.store_graph(name);

        //Load from file
        vector<ContactGraph::GraphNode*>traversal = graph.traverse_graph("Nate");
        graph = ContactGraph();
        success = success&&graph.load_graph(name);

        //Check if the nodes have been inserted properly
        success = success&&graph.nodes.size()==names.size();
        // success = success&&graph.nodes[3]->id=s=names[0];
        // success = success&&graph.nodes[3]->loc==3;

        //Check if the loaded graph is the same as the stored graph
        return success;
    }
    //PURPOSE: test friend_finder function for SuperBonus
    bool test5() {
        //Create graph
        ContactGraph graph = ContactGraph();

        //Insert nodes into graph
        vector<string> names ={ "Nate", "Olivia", "Jess", "Shelley" };
        vector<bool> status ={ 1, 1, 0, 0 };
        graph.insert(names, status);

        //Create edges in between nodes
        vector<vector<int>> edges ={ { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 2 }, { 2, 3 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Insert new cluster into graph
        names ={ "Andy", "Kelsey", "Mike", "Maria", "Darryl" };
        status ={ 0, 0, 1, 1, 1 };
        graph.insert(names, status);

        //Create edges between nodes
        edges ={ { 0, 1 }, { 0, 2 }, { 0, 4 }, { 1, 3 }, { 2, 3 }, { 3, 4 } };
        for (vector<int> edge : edges)
            graph.add_edge(names[edge[0]], names[edge[1]]);

        //Node is uninfected and there are uninfected nodes in cluster, node_friend should be uninfected
        ContactGraph::GraphNode* shelley = graph.find_node("Shelley");
        ContactGraph::GraphNode* node_friend = graph.find_friend(shelley);

        bool right_friend = node_friend->status==0;

        //Node is infected and there are uninfected nodes in cluster, 
        //node_friend should be infected
        graph.infect("Shelley");
        node_friend = graph.find_friend(shelley);
        right_friend = node_friend->status==1;

        //Node is uninfected, only uninfected nodes in other cluster, node_friend should be uninfected node in other cluster
        node_friend = graph.find_friend(graph.find_node("Jess"));
        right_friend = right_friend && node_friend!=NULL;
        right_friend = right_friend && node_friend->status==0;
         
        //All nodes are infected, node_friend should be infected
        for(ContactGraph::GraphNode* node: graph.nodes) graph.infect(node->id);
        node_friend = graph.find_friend(shelley);
        right_friend = right_friend && node_friend!=NULL;
        right_friend = right_friend && node_friend->status==1;

        return right_friend;
    }
};

int main()
{
    ContactGraphTest test;

    bool valid = test.test1();
    valid = test.test2() && valid;
    valid = test.test3() && valid;
    valid = test.test4() && valid;
    valid = test.test5() && valid;
    cout << valid << endl;

}
