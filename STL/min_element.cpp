/*
MIN_ELEMENT
------------

Girilen range için maksimum elementi bulmaya yarar

minimum Forward Iteratör kategorisinde iteratör ister

Sentaks
-------
ForwardIt min_element( ForwardIt first, ForwardIt last )

constexpr ForwardIt min_element( ForwardIt first, ForwardIt last,Compare comp );

comp  T, T parametreli bool return değerli bir fonksiyonun adresidir. Lambda ifadesi de kullanılabilir.

*/

#include<iostream>
#include<vector>
#include<algorithm>



bool f(int a, int b)
{

    std::cout << "a: " << a << " b: " << b << "\n";
    //her zaman koşula uyan elemanı b de tutuyor. 

    /*

    // Check if both a and b are even
    if ((a % 2 == 0) && (b % 2 == 0)) {
        // If both a and b are even, return the minimum of the two
        return a < b;
    }
    // If only a is even, return true
    else if (a % 2 == 0) {
        return true;
    }
    // If only b is even, return false
    else if (b % 2 == 0) {
        return false;
    }
    // If neither a nor b is even, return false
    else {
        return false;
    }

*/

    //return ((a % 2 == 0) && (b % 2 == 0) ? (a < b) : (a % 2 == 0));
    return (a<b && (a%2 == 0))||( a>b && b%2>0);

}

int main()
{
    std::vector<int> ivec = { 1,2,3,4,5,6,7 };

    auto min_element_iter = std::min_element(ivec.begin(), ivec.end());

    std::cout << "min_element: " << *min_element_iter << "\n";
    /*
    OUTPUT
    -----
    min_element: 1
    */


    auto min_element_iter_2 = std::min_element(ivec.begin(), ivec.end(), f);

    std::cout << "min_element of even: " << *min_element_iter_2 << "\n";
    /*
    OUTPUT
    -----
min_element of even: 2
    */

    return 0;

}