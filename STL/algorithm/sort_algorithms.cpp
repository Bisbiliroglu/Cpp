/*
SORT ALGORITHMS
===============

sort
----

Random access iteratör istiyor.
default argümanını kullanılırsa sıralama için less kullanıyor..

SENTAKS
-------
sort(beg, end, b_predic = less);


partial_sort
-----------
Random access iteratör istiyor.
n tane ögenin sıralanması gerektiğinde kullanılıyor. n öge istenen durum için sorta göre daha performanslı çalışıyorç

SENTAKS
------
partial_sort(beg, end, n, b_predic = less);

ilk n öge sıralanacka sonrakilerin sıralanma garantisi yok.


stable_sort ve unstable_sort
-----------
Sıralamada aynı anahtara sahip değerler, sıralamadan önce izafi konumunu koruyorsa stable sort oluyor.
Stable sort durumunda üst üste iki sıralama yapıldığı zaman iki sıralamanın da özelliklerini korur.
Örnek olarak conteiner içerisinde hem isim hem yaş olduğu düşünülürse.
Önce isme göre  ardından yaşana göre sıralama yapıldığı zaman; Aynı yaşta olan kişilerin isimleri de alfabetik sıralı olarak kalır.


stl içerisindeki sort algoritması stable değildir. Stable yapmak için std::stable_sort isimli algoritma vardır.

sort algoritmalarını stable yapmak ekstra maliyet getirmektedir.


stable_sort
-----------
Random access iteratör istiyor.
default argümanını kullanılırsa sıralama için less kullanıyor..

SENTAKS
-------
stable_sort(beg, end, b_predic = less);

is_sorted
---------
iteratörleri girilen conainerın sıralı olup olmadığı bilgisini verir.

SENTEKAS
--------
bool is_sorted(beg, end, b_predic = less);


is_sorted_until
---------------
bir container'ın sırasının nerede bozulduğu bilgisini veriyor. geri dönüş değeri olarak iteratör veriyor. geri dönüş değeri end ise tüm conteiner sıralı anlamına geliyor.

SENTEKAS
--------
iter is_sorted_until(beg, end, b_predic = less);

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

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

int main()
{

    std::vector<int> ivec{10, 25, 12, 14, 6, 18, 3, 165};
    printContainer("ivec", ivec);
    sort(ivec.begin(), ivec.end());
    printContainer("ivec", ivec);
    sort(ivec.begin(), ivec.end(), std::greater{});
    printContainer("ivec", ivec);

    /*
    OUTPUT
    ------
    ivec: 10 25 12 14 6 18 3 165
    ivec: 3 6 10 12 14 18 25 165
    ivec: 165 25 18 14 12 10 6 3
    */

    std::vector<int> ivec{10, 25, 12, 14, 6, 18, 3, 165};
    printContainer("ivec", ivec);
    std::partial_sort(ivec.begin(), ivec.begin() + 3, ivec.end());
    printContainer("ivec", ivec);
    std::partial_sort(ivec.begin(), ivec.begin() + 3, ivec.end(), std::greater{});
    printContainer("ivec", ivec);

    /*
    OUTPUT
    -----
    ivec: 10 25 12 14 6 18 3 165
    ivec: 3 6 10 25 14 18 12 165
    ivec: 165 25 18 3 6 10 12 14
    */

    std::vector<int> ivec1{1, 2, 5, 10, 86, 98, 112};
    std::cout << "is ivec1 sortted : " << std::is_sorted(ivec1.begin(), ivec1.end()) << "\n";
    std::vector<int> ivec2{1, 2, 12, 10, 86, 98, 112};
    std::cout << "is ivec2 sortted : " << std::is_sorted(ivec2.begin(), ivec2.end()) << "\n";
    std::vector<int> ivec3{1, 2, 10, 10, 86, 98, 112};
    std::cout << "is ivec3 sortted : " << std::is_sorted(ivec3.begin(), ivec3.end(), std::greater{}) << "\n";
    std::cout << "is ivec3 (reverse) sortted : " << std::is_sorted(ivec3.rbegin(), ivec3.rend(), std::greater{}) << "\n";

    /*
    OUTPUT
    ------
    is ivec1 sortted : 1
    is ivec2 sortted : 0
    is ivec3 sortted : 0
    is ivec3 (reverse) sortted : 1
    */

    std::vector<int> ivec{1, 2, 5, 10, 120, 113, 112};
    auto iter1 = std::is_sorted_until(ivec.begin(), ivec.end());
    auto iter2 = std::is_sorted_until(ivec.begin(), ivec.end(), std::greater{});

    std::cout << "is sorted until iter1: " << std::distance(ivec.begin(), iter1) << "\n";
    std::cout << "is sorted until iter2: " << std::distance(ivec.begin(), iter2) << "\n";

    /*
    OUTPUT
    -----
    is sorted until iter1: 5
    is sorted until iter2: 1
    */

    return 0;
}