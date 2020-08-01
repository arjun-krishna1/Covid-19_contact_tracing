#include <iostream>
#include <string>
#include "final_assignment.hpp"

using namespace std;

class ContactGraphTest {
    public:
        // PURPOSE: Tests if the new graph is valid
        bool test1() {
            ContactGraph graph = ContactGraph();
            bool valid;
            valid = graph.nodes.size()==0;
            return valid;
        }
};


int main() {
    ContactGraphTest test;

    bool valid = test.test1();
    cout << "Hello" << endl;
}
