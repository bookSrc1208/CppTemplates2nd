#include "temp2nd_21.h"
#include <iostream>
using namespace std;


namespace Temp2nd_21_4
{
struct DefaultPolicy1{
    static void print(){
        cout << "Default Policy1 print" << endl;
    }
};

struct DefaultPolicy2{
    static void print(){
        cout << "Default Policy2 print" << endl;
    }
};

struct DefaultPolicy3{
    static void print(){
        cout << "Default Policy3 print" << endl;
    }
};

struct MyPolicy1{  //for Policy1 we can choose from defualt DefaultPolicy1 and custom MyPolicy1
    static void print() {
        cout << "My Policy1 print" << endl;
    }
};

struct MyPolicy2{
    static void print() {
        cout << "My Policy2 print" << endl;
    }
};

struct MyPolicy3{
    static void print() {
        cout << "My Policy3 print" << endl;
    }
};

struct DefaultPolicies {
    typedef DefaultPolicy1 P1;
    typedef DefaultPolicy2 P2;
    typedef DefaultPolicy3 P3;
};

class DefaultSetter : virtual public DefaultPolicies {};

template <typename Policy>
struct Policy1_is : virtual public DefaultPolicies {
    typedef Policy P1;
};

template <typename Policy>
struct Policy2_is : virtual public DefaultPolicies {
    typedef Policy P2;
};

template <typename Policy>
struct Policy3_is : virtual public DefaultPolicies {
    typedef Policy P3;
};

template <class Base, int D>
struct Discriminator : public Base {};

template < class Setter1, class Setter2, class Setter3 >
class PolicySelector : public Discriminator<Setter1,1>,
        public Discriminator<Setter2,2>,
        public Discriminator<Setter3,3>
{};

template < class PolicySetter1 = DefaultSetter,
           class PolicySetter2 = DefaultSetter,
           class PolicySetter3 = DefaultSetter >
class BreadSlicer {
    typedef PolicySelector < PolicySetter1, PolicySetter2,
    PolicySetter3 >
    Policies;
public:
    static void print() {
        Policies::P1::print();  //Policy1 print
        Policies::P2::print();  //Policy2 print
        Policies::P3::print();  //Polciy3 print
    }
};

int test()
{
    cout <<  "using default" << endl;
    BreadSlicer<> bs1;
    bs1.print();
    cout << "using custom policy fo Policy2" << endl;
    BreadSlicer<Policy2_is<MyPolicy2> > bs2;
    bs2.print();
    cout << "using custom policy for Policy2 and Policy3" << endl;
    BreadSlicer<Policy3_is<MyPolicy3>, Policy2_is<MyPolicy2> > bs3;
    bs3.print();
    return 1;
}


};
