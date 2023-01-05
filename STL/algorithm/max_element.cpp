/*
MAX_ELEMENT
------------

Girilen range için maksimum elementi bulmaya yarar

minimum Forward Iteratör kategorisinde iteratör ister

Sentaks
-------
ForwardIt max_element( ForwardIt first, ForwardIt last )

ForwardIt max_element( ForwardIt first, ForwardIt last,Compare comp );

comp  T, T parametreli bool return değerli bir fonksiyonun adresidir. Lambda ifadesi de kullanılabilir.

*/

#include<iostream>
#include<vector>
#include<algorithm>

bool f(int a, int b)
{
        std::cout<<"a: "<<a<<" b: "<<b<<"\n";
    //false gelince b değişiyor, a aynı kalıyor


        if (a % 2 == 0 && b % 2 == 0)
        {
            return b > a;
        }
        else if(b > a)
        {
            return b%2 == 0;
        }
        
    return false;

}

int main()
{
    std::vector<int> ivec = {9,11,12,9,1,2,3,4,5,16,7,6,14,13,1};

    auto max_element_iter = std::max_element(ivec.begin(), ivec.end());

    std::cout<<"max_element: "<<*max_element_iter<<"\n";
    /*
    OUTPUT
    -----
    max_element: 7
    */

   auto max_element_iter_2 = std::max_element(ivec.begin(), ivec.end(),f);

    std::cout<<"max_element of even: "<<*max_element_iter_2<<"\n";
    /*
    OUTPUT
    -----
    max_element: 1
    */

    return 0;

}