/*
TRANSFORM
==========

Bir rangedeki ögelerin bir fonksiyona gönderyor. Her öge için fonksiyondan elde edilen çıkışı bir range yazıyor.

Sentaks  (1. overload)
--------
OutIter transform(InIter beg, InIter end, OutIter destbeg, Ufunc f)


f fonksiyonu bir parametreli fonksiyondur. Bu fonksiyonun dönüş değeri destbeg iteratöründen başlayarak hedef container'a yazılır.


Sentaks  (1. overload)
--------
OutIter transform(InIter beg1, InIter end, InIter beg2, OutIter destbeg, Ufunc f)

f fonksiyonu iki parametreli fonksiyondur. beg1 ve beg2 iteratörleri ile parametrelerini alır. Bu fonksiyonun dönüş değeri destbeg iteratöründen başlayarak hedef container'a yazılır.



*/

#include<iostream>
#include<algorithm>
#include<vector>

template <typename T>
void printContainer(std::string containerName, const T& container)
{
    std::cout << containerName << ": ";
    for (const auto& item : container)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int square(int a)
{
    return a * a;
}

int main()
{
    std::vector<int> ivec1 = { 1,2,3,4,5,6,7 };
    std::vector<int> ivec2(ivec1.size());

    printContainer("ivec1", ivec1);
    printContainer("ivec2", ivec2);


    std::transform(ivec1.begin(), ivec1.end(), ivec2.begin(), square);

    printContainer("ivec1", ivec1);
    printContainer("ivec2", ivec2);

    /*
    OUTPUT
    -----
    ivec1: 1 2 3 4 5 6 7
    ivec2: 0 0 0 0 0 0 0
    ivec1: 1 2 3 4 5 6 7
    ivec2: 1 4 9 16 25 36 49
    */

    ivec2.clear();
    ivec2.resize(ivec1.size());

    printContainer("ivec1", ivec1);
    printContainer("ivec2", ivec2);


    std::transform(ivec1.begin(), ivec1.end(), ivec2.begin(), [](int a) {return a * a;});

    printContainer("ivec1", ivec1);
    printContainer("ivec2", ivec2);

    /*
   OUTPUT
   -----
   ivec1: 1 2 3 4 5 6 7
   ivec2: 0 0 0 0 0 0 0
   ivec1: 1 2 3 4 5 6 7
   ivec2: 1 4 9 16 25 36 49
   */


    printContainer("ivec1", ivec1);
    std::transform(ivec1.begin(), ivec1.end(), ivec1.begin(), [](int a) {return a * a;});
    printContainer("ivec1", ivec1);
    /*
    OUTPU
    -------
    ivec1: 1 2 3 4 5 6 7
    ivec1: 1 4 9 16 25 36 49
    */


    std::vector<int> ivec3 = { 1,2,3,4,5,6,7 };
    std::vector<int> ivec4 = { 10,20,30,40,50,60,70 };
    std::vector<int> ivec5(ivec3.size());

    printContainer("ivec3", ivec3);
    printContainer("ivec4", ivec4);
    printContainer("ivec5", ivec5);

    std::transform(ivec3.begin(), ivec3.end(), ivec4.begin(), ivec5.begin(), [](int a, int b) {return a + b;});

    printContainer("ivec3", ivec3);
    printContainer("ivec4", ivec4);
    printContainer("ivec5", ivec5);

    /*
    OUTPUT
    ------
    ivec3: 1 2 3 4 5 6 7
    ivec4: 10 20 30 40 50 60 70
    ivec5: 0 0 0 0 0 0 0
    ivec3: 1 2 3 4 5 6 7
    ivec4: 10 20 30 40 50 60 70
    ivec5: 11 22 33 44 55 66 77
    */

    return 0;
}