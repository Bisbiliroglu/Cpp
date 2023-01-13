/*
PARTITITON
----------
Bir gurubu özellikerine göre alt gruplarına ayrılma işlem. Bölümleme.
Bir veri yapısını belirli koşulu sağlayanlar ve sağlamayanlar şeklinde ikiye bölme işlemini yapıyor.

stable and unstable partititon
------------------------------
partition işlemi sonrasında containerdaki izafi konum konulursa stable partition, diğer durumda unstable partition olur


partition point
-------------
1 3 2 7 8 10 6 4 11 23 18 giriş

2 8 10 6 4 18 1 11 23 3 7 tek/çift ayırma

partition point koşulu sağlamayanlardan ilkinin konumu. Yukarıdaki örnek için partition point 11 değerinin bulundupu konum.

partition ve stable_partition algoritmaları partition point döndürür.


SENTAKS
--------
iter partition(beg, end, u_pred)


partititon_copy
--------------
Koşulu sağlayanları bir range, sağlamayanları başka range yazıyor.


SENTAKS
-------
pair partition(beg, end, true_iter, false_iter, u_pred)

true_iter: koşulu sağlayanların yazılacağı range başlangıcı
false_iter: koşulu sağlamayanların yazılacağı range başlangıcı


is_partititoned
---------------

*/

#include <iostream>
#include <vector>
#include <algorithm>

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

    std::vector<int> ivec = {1, 2, 3, 4, 5};
    printContainer("ivec", ivec);
    auto iter = std::partition(ivec.begin(), ivec.end(), [](const int &a)
                               { return a % 2; });
    printContainer("ivec", ivec);
    std::cout << "partition point " << *iter << " ,index " << std::distance(ivec.begin(), iter) << "\n";

    /*
    OUTPUT
    ------
    ivec: 1 2 3 4 5
    ivec: 1 5 3 4 2
    partition point 4 ,index 3
    */

    std::vector<int> container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<int> primes(container.size());
    std::vector<int> non_primes(container.size());
    printContainer("primes", primes);
    printContainer("non_primes", non_primes);

    std::partition_copy(container.begin(), container.end(), primes.begin(), non_primes.begin(), [](const int &a)
                        {
                            if (a < 2)
                                return false;

                            for (int i = 2; i < a; i++)
                            {
                                if (a % i == 0)
                                    return false;
                            }
                            return true;
                        });

    printContainer("primes", primes);
    printContainer("non_primes", non_primes);

    /*
    OUTPUT
    ------
    primes: 2 3 5 7 11 0 0 0 0 0 0 0
    non_primes: 1 4 6 8 9 10 12 0 0 0 0 0
    */

    return 0;
}