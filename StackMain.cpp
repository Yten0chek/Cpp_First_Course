#include <iostream>
#include "Stack.h"

int main()
{
    Stack<int> MyStack;
    MyStack.push(12);
    MyStack.push(13);
    MyStack.push(14);
    while (!MyStack.empty()) {
        std::cout << MyStack.top() << " Size now is " << MyStack.size() << std::endl;
        MyStack.pop();
    }
}
