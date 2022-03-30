// AVLTreeProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AVLTree.h"

using namespace std;

int main()
{
    AVLTree x = AVLTree();

    x.insertNode(10);
    x.insertNode(20);
    x.insertNode(30);
    x.insertNode(40);
    x.insertNode(50);
    x.printAVLpreOrder();
}
