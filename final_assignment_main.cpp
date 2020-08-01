#include <iostream>
#include <string>
#include "lab3_tests.hpp"

using namespace std;

// PURPOSE: Returns the test result
string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main() {
    BinarySearchTreeTest bst_test;

    string bst_test_descriptions[10] = {
      "Test1: New tree is valid",
      "Test2: Test a tree with one node",
      "Test3: Insert, remove, and size on linear list formation with three elements",
      "Test4: Test removal of a node with one child",
      "Test5: Insert multiple elements and remove till nothing remains",
      "Test6: Test removal of root node when both children of root have two children",
      "Test7: Test depth with many inserts and some removes",
      "Test8: Lots of inserts and removes",
      "Test9: Perform single AVL rotations",
      "Test10: Perform double AVL rotations"
    };
    bool bst_test_results[10] = {0};
    
    
    bst_test_results[0] = bst_test.test1();
    
    
    bst_test_results[1] = bst_test.test2();
    
    
    bst_test_results[2] = bst_test.test3();
    
    bst_test_results[3] = bst_test.test4();

    bst_test_results[4] = bst_test.test5();
    bst_test_results[5] = bst_test.test6();
    bst_test_results[6] = bst_test.test7();
    bst_test_results[7] = bst_test.test8();
    bst_test_results[8] = bst_test.test9();
    bst_test_results[9] = bst_test.test10();

    // cout << "BINARY SEARCH TREE TESTING RESULTS \n";
    // cout << "********************************** \n";
    // int i = 4;

    for (int i = 0; i < 10; ++i) {
        cout << bst_test_descriptions[i] << 
            endl << get_status_str(bst_test_results[i]) << endl;
    }
    // cout << bst_test_results[0];
    cout << endl;
}
