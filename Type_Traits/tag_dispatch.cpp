#include<iostream>
#include<type_traits>

template<typename T>
void func_impl(T x, std::true_type)
{
    std::cout << "TAG Dispatch pointer turleri icin implementasyon\n";
}

template<typename T>
void func_impl(T x, std::false_type)
{
    std::cout << "TAG Dispatch pointer olmayan turler icin implementasyon\n";

}

template<typename T>
void func(T x)
{
    func_impl(x, typename std::is_pointer<T>::type());
}

int main()
{
    func(12);
    int* a;
    func(a);
    /*
    OUTPUT 
    -----
    TAG Dispatch pointer olmayan turler icin implementasyon
    TAG Dispatch pointer turleri icin implementasyon
    */

}