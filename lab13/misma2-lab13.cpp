
/* Name: Abeer Ismail
 * Date: 6/7/2023
 * CS211 Summer 2023
 * Creating a binary tree and adding in integers
 * */

#include "BSTNode.h"
#include <iostream>

using namespace std;

int main() {
    BSTNode* head = nullptr;

    int num;
    std::cout << "Enter integers (enter -999 to exit): "; //Safety case of -999, otherwhise it loops cins
    while (cin >> num && num != -999) {
        if (head == nullptr) {
            head = new BSTNode(num);
        } else {
            head->add(num);
        }
    }

//Most logic is done in bst.cpp

    cout << "BST nodes in order: ";
    if (head != nullptr) {
        head->print();
    }
    
    delete head; // Release memory allocated by the BST nodes

    return 0;
}
