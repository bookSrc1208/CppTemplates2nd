#include "stack5.h"
#include <iostream>
#include <vector>
namespace Temp2nd_5_6 {

void main1()
{
    Stack<int> iStack; // stack of ints
    Stack<float> fStack; // stack of floats
    // manipulate int stack
    iStack.push(1);
    iStack.push(2);
    std::cout << "iStack.top(): " << iStack.top() << std::endl ;
    // manipulate float stack:
    fStack.push(3.3);
    std::cout << "fStack.top(): " << fStack.top() << std::endl ;
    // assign stack of different type and manipulate again
    fStack = iStack;
    fStack.push(4.4);
    std::cout << "fStack.top(): " << fStack.top() << std::endl ;
    // stack for doubless using a vector as an internal container
    Stack<double, std::vector> vStack;
    vStack.push(5.5);
    vStack.push(6.6);
    std::cout << "vStack.top(): " << vStack.top() << std::endl ;
    vStack = fStack;
    std::cout << "vStack: ";
    while (! vStack.empty()) {
        std::cout << vStack.top() << ' ' ;
        vStack.pop();
    }
    std::cout << std::endl ;
}
}
