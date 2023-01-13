/*

NTH_ELEMENT
-----------

n. ögenin konumuna göre partittion yapıyor. n. eleman yerinde kalıyor. ondan öncekiler ondan küçük, sonrakiler büyük oluyor. ancak sıralı olmuyorlar. 

random access iteratör istiyor.

SENTAKS
-------

template< class RandomIt >
void nth_element( RandomIt first, RandomIt nth, RandomIt last );



*/

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void printContainer(std::string containerName, const T &container)
{
    std::cout << containerName << ": ";
    for (const auto &item : container)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

template <typename T>
T median( std::vector<T>  vec)
{
    std::nth_element(vec.begin(), vec.begin()+vec.size()/2 ,vec.end());
    return vec[vec.size()/2];
}

int main()
{
{
    std::vector<int> ivec = {10, 5, 19,2, 8, 76,15,26,11,4,5};
    printContainer("ivec",ivec);
    std::cout<<"nth element = "<<*(ivec.begin() + 4)<<"\n";
    std::nth_element(ivec.begin(),ivec.begin() + 4, ivec.end());
    printContainer("ivec",ivec);
    /*
    OUTPUT
    ------
    ivec: 10 5 19 2 8 76 15 26 11 4 5 
    nth element = 8
    ivec: 2 4 5 5 8 10 15 26 11 19 76 
    */
}


{
    std::vector<int> ivec = {10, 5, 19,2, 8, 76,15,26,11,4,5};
    printContainer("ivec",ivec);
    std::cout<<"nth element = "<<*(ivec.begin() + 5)<<"\n";
    std::nth_element(ivec.begin(),ivec.begin() + 5, ivec.end());
    printContainer("ivec",ivec);
    /*
    OUTPUT
    ------
    ivec: 10 5 19 2 8 76 15 26 11 4 5 
    nth element = 76
    ivec: 5 5 4 2 8 10 15 26 11 19 76 
    */
}

{
    std::vector<int> ivec = {10, 5, 19,2, 8, 76,15,26,11,4,5};
    printContainer("ivec",ivec);
    std::cout<<"median vector = "<<median<int>(ivec)<<"\n";
    /*
    OUTPUT
    ------
    ivec: 10 5 19 2 8 76 15 26 11 4 5 
    median vector = 10
    */
}


    return 0;
}