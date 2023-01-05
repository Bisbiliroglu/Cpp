/*

COPY
====

algorithm başlık dosyası içerisindedir. 
Containerlar arasında copyalama işlemi yapar.
Kopyalanacak containerların aynı türden olmasına gerek yoktur.


SENTAKS

destination.end = copy(source.begin, source.end, destination.begin)

Hedef (kopyalanacak) range'deki alan büyüklüğünün en az kaynak (kopyalanan) range'deki alan büyüklüğü kadar olması gerekiyor. diğer durumda hata verecektir. 

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

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

    std::vector<int> ivec = {1, 2, 3, 4, 5,6};
    std::list<int> ilist(6);

    printContainer("ivec", ivec);
    printContainer("ilist", ilist);

    std::copy(ivec.begin(), ivec.end(), ilist.begin());

    printContainer("ivec", ivec);
    printContainer("ilist", ilist);

    /*
    OUTPUT
    ------
    ivec: 1 2 3 4 5 6 
    ilist: 0 0 0 0 0 0 
    ivec: 1 2 3 4 5 6 
    ilist: 1 2 3 4 5 6 
    */

    return 0;
}