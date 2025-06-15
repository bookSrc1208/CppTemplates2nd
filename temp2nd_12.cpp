#include "temp2nd_12.h"

namespace temp2nd_12
{




};

namespace temp2nd_12_3_3
{
template<char const *str>
class Message {

};
extern char const hello[] = "Hello Wolrd!";
char const hello11[] = "Hello World!";
void foo()
{
    static char const hello17[] = "Hello World!";
    Message<hello> msg03; // OK in all versions
    Message<hello11> msg11; // OK since C++11
    Message<hello17> msg17; // OK since C++17
    //Message<hello17> msg17; // OK since C++17
}

template<typename T, T nontypeParam>
class C;
struct Base {
    int i;
} base;
 Base base2();

struct Derived : public Base {
} derived;
//C<Base*, &derived>* err1; // ERROR: derived-to-base conversions are not considered
//C<int&, base.i>* err2; // ERROR: fields of variables aren't considered to be variables
//C<int&, base2.i>* err2; // ERROR: fields of variables aren't considered to be variables

//int a[10];
//C<int*, &a[0]>* err3; // ERROR: addresses of array elements aren't acceptable either

};


namespace temp2nd_12_5_2
{
template<typename T1, typename T2>
void combine(T1, T2);

class Mixer {
    friend void combine<>(int&, int&); // OK: T1 = int&, T2 = int&
    friend void combine<int, int>(int, int); // OK: T1 = int, T2 = int
    friend void combine<char>(char, int); // OK: T1 = char, T2 = int
    //friend void combine<char>(char&, int); // ERROR: doesn't match combine()
    //template
    //friend void combine<>(long, long) {} // ERROR: definition not allowed!
};

void multiply(void*); // ordinary function

template<typename T>
void multiply(T) // function template
{

}
class Comrades {
    friend void multiply(int) { } // defines a new function ::multiply(int)
    friend void temp2nd_12_5_2::multiply(void*); //refers to the ordinary function above,
    // not the the multiply<void*> instance
    friend void temp2nd_12_5_2::multiply(int); // refers to an instance of the template
    friend void temp2nd_12_5_2::multiply<double*>(double*); // qualified names can also have angle brackets,
    // but a template must be visible
    //friend void temp2nd_12_5_2::error() { } // ERROR: a qualified friend cannot be a definition
};

}
