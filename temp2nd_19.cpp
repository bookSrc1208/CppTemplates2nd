#include "temp2nd_19.h"
#include <type_traits>
#include <string>
#include <iostream>

namespace  Temp2nd_19
{
//19.3
template<typename T1, typename T2>
struct PlusResultT {
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};
template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;


void test(){
    //19.3
    PlusResultT<int,double>::Type p = 12;

}

}
namespace  Temp2nd_19_3_2
{
//退化
template<typename T>
void f(T)
{}

template<typename A>
void printParameterType(void (*)(A))
{
std::cout << "Parameter type: " << typeid(A).name() << '\n';
std::cout << "- is int: " <<std::is_same<A,int>::value << '\n';
std::cout << "- is const: " <<std::is_const<A>::value << '\n';
std::cout << "- is pointer: " <<std::is_pointer<A>::value << '\n';
}


template<typename T>
struct DecayT : std::remove_cv<T>
{using Type = typename std::remove_cv<T>::type;};

template<typename T>
struct DecayT<T[]> {
    using Type = T*;
};

template<typename T, std::size_t N>
struct DecayT<T[N]> {
    using Type = T*;
};

template<typename R, typename... Args>
struct DecayT<R(Args...)> {
    using Type = R (*)(Args...);
};

template<typename T>
void printDecayedType()
{
    using A = typename DecayT<T>::Type;
    std::cout << "Parameter type: " << typeid(A).name() << '\n';
    std::cout << "- is int: " << std::is_same<A,int>::value << '\n';
    std::cout << "- is const: " << std::is_const<A>::value << '\n';
    std::cout << "- is pointer: " << std::is_pointer<A>::value << '\n';
}
void test()
{
    printDecayedType<int>();
    printDecayedType<int const>();
    printDecayedType<int[7]>();
    printDecayedType<int(int)>();
}

}
namespace  Temp2nd_19_4_1
{
//19.4
template<typename T>
struct IsDefaultConstructibleT {
private:
    // test() trying substitute call of a default constructor for

    // ERROR: test() uses T directly:
    //template<typename, typename = decltype(T())>

    //T passed as U :
    template<typename U, typename = decltype(U())>
    static char test(void*);// test() fallback:
    template<typename>
    static long test(...);
public:
    static constexpr bool value =
            std::is_same<decltype(test<T>(nullptr)), char>::value;
};
struct S {
S() = delete;
};

void test1(){
    //19.4
    auto aa = IsDefaultConstructibleT<int>::value;
    auto ss = IsDefaultConstructibleT<S>::value;

}

//using Size1T = char(&)[1];
//using Size2T = char(&)[2];
//template<...> static Size1T test(int); // checking test()
//template<...> static Size2T test(...); // fallback
//enum { value = sizeof(test<...>(42)) == 1 };

}


#if 0
namespace  Temp2nd_19_4_3
{
// helper: checking validity of f (args…) for F f and Args… args:
template<typename F, typename... Args,
         typename = decltype(std::declval<F>() (std::declval<Args&&>()...))>
std::true_type isValidImpl(void*);
// fallback if helper SFINAE'd out:
template<typename F, typename... Args>
std::false_type isValidImpl(...);
// define a lambda that takes a lambda f and returns whether calling f with args is valid
inline constexpr
auto isValid = [](auto f) {
    return [](auto&&... args) {
        return decltype(isValidImpl<decltype(f),
                        decltype(args)&&...>(nullptr)){};
    };
};
// helper template to represent a type as a value
template<typename T>
struct TypeT {
    using Type = T;
};
// helper to wrap a type as a value
template<typename T>
constexpr auto type = TypeT<T>{};
// helper to unwrap a wrapped type in unevaluated context

template<typename T>
T valueT(TypeT<T>); // no definition needed

//constexpr auto isDefaultConstructible
//= isValid([](auto x) -> decltype((void)decltype(valueT(x))(){}));
constexpr auto isDefaultConstructible
= isValid([](auto x) -> decltype((void)decltype(valueT(x))()) {});

void test(){


}

}
#endif
namespace  Temp2nd_19_4_4
{

#if 0
template<typename T1, typename T2>
struct PlusResultT {
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};
template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;
#else
template<typename, typename, typename = std::void_t<>>
struct HasPlusT : std::false_type
{};
// partial specialization (may be SFINAE'd away):
template<typename T1, typename T2>
struct HasPlusT<T1, T2, std::void_t<decltype(std::declval<T1>() +std::declval<T2> ())>>: std::true_type
{};


template<typename T1, typename T2, bool = HasPlusT<T1, T2>::value>
struct PlusResultT { //primary template, used when HasPlusT yields true
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};
template<typename T1, typename T2>
struct PlusResultT<T1, T2, false> { //partial specialization, used otherwise
};
#endif


template<typename T>
class Array {
};
class A {
};
class B {
};

template<typename T1, typename T2>
Array<typename PlusResultT<T1, T2>::Type>
operator+ (Array<T1> const&, Array<T2> const&);

// overload + for concrete types:
Array<A> operator+(Array<A> const& arrayA, Array<B> const& arrayB){

    return Array<A>();
}

void addAB(Array<A> const& arrayA, Array<B> const& arrayB) {
    auto sum = arrayA + arrayB; // ERROR?: depends on whether the compiler
    // instantiates PlusResultT<A,B>
}

//void addAB(Array<A> arrayA, Array<B> arrayB) {
//    auto sum = arrayA + arrayB; // ERROR: fails in instantiation of
//    //PlusResultT<A, B>

//}

template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;

//template<>
//struct PlusResult<int,int>{

//}
}

namespace  Temp2nd_19_5
{
void aux1(void);
template<typename FROM, typename TO>
struct IsConvertibleHelper {
private:
    // test() trying to call the helper aux(TO) for a FROM passed as F :
    static void aux(TO);
    template<typename F,
             typename = decltype(aux(std::declval<F>()))>
    static std::true_type test(void*);
    // test() fallback:
    template<typename>
    static std::false_type test(...);
public:
    using Type = decltype(test<FROM>(nullptr));
};
template<typename FROM, typename TO>
struct IsConvertibleT : IsConvertibleHelper<FROM, TO>::Type {
};


template<typename FROM, typename TO>
using IsConvertible = typename IsConvertibleT<FROM, TO>::Type;
template<typename FROM, typename TO>
constexpr bool isConvertible = IsConvertibleT<FROM, TO>::value;

void test(){
    auto ii = IsConvertibleT<int, int>::value; //yields true
    auto is = IsConvertibleT<int, std::string>::value; //yields false
    auto cs = IsConvertibleT<char const*, std::string>::value; //yields true
    auto sc = IsConvertibleT<std::string, char const*>::value; //yields false

    //auto vv = IsConvertibleT<int, void>::value; //yields false

}
}

namespace  Temp2nd_19_5_2
{
template<typename FROM, typename TO, bool = std::is_void<TO>::value ||
         std::is_array<TO>::value || std::is_function<TO>::value>
struct IsConvertibleHelper {
    using Type = std::integral_constant<bool, std::is_void<TO>::value &&
    std::is_void<FROM>::value>;
};

template<typename FROM, typename TO>
struct IsConvertibleHelper<FROM,TO,false> {
private:
    // test() trying to call the helper aux(TO) for a FROM passed as F :
    static void aux(TO);
    template<typename F,
             typename = decltype(aux(std::declval<F>()))>
    static std::true_type test(void*);
    // test() fallback:
    template<typename>
    static std::false_type test(...);
public:
    using Type = decltype(test<FROM>(nullptr));
};
template<typename FROM, typename TO>
struct IsConvertibleT : IsConvertibleHelper<FROM, TO>::Type {
};
template<typename FROM, typename TO>
using IsConvertible = typename IsConvertibleT<FROM, TO>::Type;
template<typename FROM, typename TO>
constexpr bool isConvertible = IsConvertibleT<FROM, TO>::value;

void test(){
    auto ii = IsConvertibleT<int, int>::value; //yields true
    auto is = IsConvertibleT<int, std::string>::value; //yields false
    auto cs = IsConvertibleT<char const*, std::string>::value; //yields true
    auto sc = IsConvertibleT<std::string, char const*>::value; //yields false

    auto vv = IsConvertibleT<void, void>::value; //yields false
    auto iv = IsConvertibleT<int, void>::value; //yields false

}

}

namespace  Temp2nd_19_8_4
{
template<typename T, typename = std::void_t<>>
struct IsClassT : std::false_type { //primary template: by default noclass
};
template<typename T>
struct IsClassT<T, std::void_t<int T::*>> // classes can have pointer-to-member
: std::true_type {
};

struct StA{

};
union UB{
    double a;
};
enum EC{
    E1,E2
};

void test(){
    int a;

    bool b1 = IsClassT<int>::value;
    bool b2 = IsClassT<StA>::value;
    bool b3 = IsClassT<UB>::value;
    bool b4 = IsClassT<EC>::value;

    bool b11 = std::is_class<int>::value;
    bool b12 = std::is_class<StA>::value;
    bool b13 = std::is_class<UB>::value;
    bool b14 = std::is_class<EC>::value;

}
void test2(){

    bool b11 = std::is_union<int>::value;
    bool b12 = std::is_union<StA>::value;
    bool b13 = std::is_union<UB>::value;
    bool b14 = std::is_union<EC>::value;

}

 class CC;
  int CC;
}




