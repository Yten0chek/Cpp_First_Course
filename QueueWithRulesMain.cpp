#include <iostream>

#include "Queue.h"

bool stack(int a, int b) { return false; } //Работает как стек

bool forMore(int a, int b) { return a < b; } //Сортировка по возрастанию

bool forLess(int a, int b) { return a > b; } //Сортировка по убываниию

int main()
{
    Queue<int> Al;

    Al.SetRule(forMore);
    
    Al.push(1);
    Al.push(4);
    Al.push(2);
    Al.push(3);
    Al.push(8);

    while (!Al.empty())
        std::cout << Al.pop() << " ";
}

