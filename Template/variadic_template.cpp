/*
VARIADIC TEMPLATE
-----------------

Variadic template aracı tek bir template oluşturarak, bu templatein parametre sayısı istenilen sayı kadar olmasını sağlıyor

SENTAKS
---------
template<typename ...Args>


... argümanı ile oluşturulan yapıya template type parameter pack adı veriliyor.
Bu paket içinde 0 veya daha fazla parametre olabilir. 

fonksiyon şablonları veya sınıf şablonları ile kullanılabilir. 

sizeof operatörü ile girilen paramtre sayısı compile time'da görülebilir.

SENTAKS
-------
sizeof...(Ts)


Pack expension kullanılan yerlerde fonksiyon için elipsis atomu (...) isimden sonra yazıyor.



VARIADIC FONKSİYONLARDA ARGÜMANLARA ERİŞMEK
---------------------------------------------
variadic fonksiyonlarda her bir parametreye ayrı ayrı ulaşmak için birden fazla teknik vardır. Bunlardan ilki template ile vaariadic parametre sayısı kadar ayrı fonksiyon yazdırmaktır. 
Bunların haricinde, fold expressions, static if deyimini yani if constexpr yapısı kullanarak yapılabilir. 

EKSILTME TEKNIGI
----------------
    template <typename T>
    void print(const T& r)
    {
        std::cout<<r<<"\n";
    }

    template<typename T, typename ...Ts>
    void print(const T& r, const Ts&... args)
    {
        print(r);
        print(args...); // burada birer birer eksiltilerek recusive yapı oluşturuluyor
    }
*/

#include<iostream>

template<typename ...Args>
class Myclass
{

};

template<typename ...Args>
void foo(Args... params) // pack expansion
{
constexpr auto a = sizeof...(params);
std::cout<<"a: "<<a<<"\n";

}

template<typename ...Args>
void bar(int, double,Args... params) // pack expansion
{

}


template<typename T, typename ...Args>
void baz(int, double,Args... params) // pack expansion
{

}

template <typename ...Ts>
void func(Ts&&... params) //universal reference
{

}


template<int ...n>
class Myclass2
{

};

template <typename T>
void print(const T& r)
{
    std::cout<<r<<"\n";
}

template<typename T, typename ...Ts>
void print(const T& r, const Ts&... args)
{
    print(r);
    print(args...); // burada birer birer eksiltilerek recusive yapı oluşturuluyor
}


template <typename T>
T sum (T a)
{
    return a; 
}

template <typename T, typename ...Ts>
T sum(T a, Ts... args)
{
    return sum(a) + sum(args...);
}

template <typename ...Ts>
void print_variadic(const Ts& ...args)
{
    //int temp[sizeof...(args)] = {(std::cout<< args<<" ", 0)... };

    (void)std::initializer_list<int> {(std::cout<< args<<" ", 0)... }; 
}

int main()
{
    Myclass<int> c1;
    Myclass<int,int> c2;
    Myclass<double, int> c3;
    Myclass<char, double,int> c4;

    foo();
    foo(1);
    foo(3.4,6);
    foo(5.7,"test",5,4.7);
    foo(6u,7.f,"test");
    /*
    OUTPUT
    ------
    a: 0
    a: 1
    a: 2
    a: 4
    a: 3
    */


    //bar fonksiyonu en az iki parametre ile çağrılabilir.
    bar(1,2.5);
    bar(1,2.5, "test");
    bar(1,2.5,3);
    bar(1,2.5,3,4.5,6,7,8);

    Myclass2<1,2,3,4,5,6,7> c5;
    Myclass2<1,2,7> c6;

    print(3,5,6.7,"hello","WORLD");
    /*
    OUTPUT
    ------
    3
    5
    6.7
    hello
    WORLD
    */

    std::cout<<"sum(3,5,7,3.14,5.116,6,7u,8.5f,6): "<<sum(3,5,7,3.14,5.116,6,7u,8.5f,6)<<"\n";
    //sum(3,5,7,3.14,5.116,6,7u,8.5f,6): 50


    print_variadic(3,5,6.7,"hello","WORLD");
    //3 5 6.7 hello WORLD 

    return 0;
}