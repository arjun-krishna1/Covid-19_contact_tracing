#include <iostream>
#include <string>
#include "final_assignment.hpp"

using namespace std;

// PURPOSE: Returns the test result
string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main() {
    ContactGraph();
    cout << "Hello" << endl;
}
