/* Name: Abeer Ismail
* Date: 6/7/2023
* CS211 Summer 2023
* This is the logic for adding in nodes into a binary tree and seeing where the ints belong
*/
#include "BSTNode.h"
#include <iostream>

BSTNode::BSTNode(int d) { //Constructor using ints
    data = d;
    count = 1;
    left = nullptr;
    right = nullptr;
}

BSTNode::~BSTNode() { //Destructor to save memory at end
    if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }
}

void BSTNode::add(int d) { //This adds in the nodes and looks if it belongs in which position
    if (d == data) {
        count++;
    } else if (d < data) {
        if (left == nullptr) {
            left = new BSTNode(d);
        } else {
            left->add(d);
        }
    } else {
        if (right == nullptr) {
            right = new BSTNode(d);
        } else {
            right->add(d);
        }
    }
}

void BSTNode::print() { //Simple print function
    if (left != nullptr) {
        left->print();
    }
    std::cout << data << " ";
    if (right != nullptr) {
        right->print();
    }
}
