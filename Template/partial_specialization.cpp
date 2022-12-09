/*
PARTIAL SPECIALIZATION
----------------------
Partial Specialization,
Explicit specialization'dan farklı olarak bir tür tipi için değil, belirli bir gruptaki tür tipleri için ayrı bir specialization partial specialization ile verilir.

Not: Function template ile partial specializationk kullanılamıyor sadece class template ile kullanılabiliyor.

SENTAKS
-------
template<typename T>
class MyClass{

}
template<typename T>
class MyClass<T*>{ // pointer türleri için bu specialization kullanılacak
	
}

partial specialization parametre sayısı ile primary template parametre sayısı eşit olmak zorunda değil. 
Partial specialization primary template parametre sayısından daha fazla olabilir. 

*/

#include<iostream>

template <typename T>
class MyClass
{
    public:
    MyClass()
    {
        std::cout<<"Primary template\n";
    }
};

template<typename T>
class MyClass<T*>
{
    public:
    MyClass()
    {
        std::cout<<"Pointer partial specialization\n";
    }
};

template<typename T>
class MyClass<T[]>
{
    public:
    MyClass()
    {
        std::cout<<"Array partial specialization\n";
    }
};

template<typename T, typename U>
class MyClass<std::pair<T,U>>
{
    public:
    MyClass()
    {
        std::cout<<"std:pair partial specialization\n";
    }
};


int main()
{
    MyClass<int> mi;
    MyClass<double> md;
    MyClass<char*> mcp;
    MyClass<char[]> mca;
    MyClass<std::pair<int,double>> mp;


    /*
    OUTPUT
    -------
    Primary template
    Primary template
    Pointer partial specialization
    Array partial specialization
    std:pair partial specialization

    */

    return 0;
}