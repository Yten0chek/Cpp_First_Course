#include <iostream>
#include <fstream>
#include "Tree.h"

int main()
{
    Tree tree;
    std::ifstream rf("text.txt");

    tree.readFile(rf);

    tree.PrintTree();
    std::cout << std::endl;
}