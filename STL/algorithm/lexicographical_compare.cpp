/*
LEXICOGRAPHICAL COMPARE
-----------------------

iKİ conrainer sıra ile karşılaştırıyor. İlk değerfarkında büyük olanı büyük kabul ediyor.
Eğer iki container'da karşılaştırma sırasında aynı ise sizeı büyük olan büyük kabul ediliyor. 
İki container içeriği aynı ise eşit kabul ediliyor.

SENTAKS
--------
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 );

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 );

1. range ikinci range'den küçükse true döner. 

*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<string>

int main()
{
    using namespace std;

    vector<int> v1 {1,2,3,4,5};
    list<int> l1 {2,2,3,4,5}; //0. indexi büyük
    cout<<lexicographical_compare(v1.begin(), v1.end(), l1.begin(), l1.end())<<"\n";

    vector<int> v2 {1,2,3,5,5}; //3. indexi büyük
    list<int> l2 {1,2,3,4,5};
    cout<<lexicographical_compare(v2.begin(), v2.end(), l2.begin(), l2.end())<<"\n";

    vector<int> v3 {1,2,3,4}; //size daha küçük
    list<int> l3 {1,2,3,4,5};
    cout<<lexicographical_compare(v3.begin(), v3.end(), l3.begin(), l3.end())<<"\n";



    string s1 = "MASA";
    string s2 = "masa"; //0. index 'm' ascii değeri daha büyük
    cout<<lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end())<<"\n";


    /*
    OUTPUT
    --------
    1
    0
    1
    1
    */

    return 0;
}