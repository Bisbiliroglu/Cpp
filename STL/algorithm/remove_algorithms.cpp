/*
unique
------
bir veri yapısındaki ögelerden ardışık tam sayı olanların sayısını bire indirmek

4 7 7 7 7 2 2 2 2 3 4 4 9 2 7 5 6 1 5 6 

4 7 2 3 4 9 2 7 5 6 1 5 6

unique hale getirdikten sonra yanyana aynı öge olmayacak.

remove
------
belirli bir değere sahip olanları siliyor

remove_if
---------
belirli koşulu sağlayan ögeleri siliyor. 

silme algoritmları lojik silme işlemi yapar. 

4 7 7 7 7 2 2 2 2 3 4 4 9 2 7 5 6 1 5 6 

4 7 2 3 4 9 2 7 5 6 1 5 6 ? ? ? ? ? ? ? ?

B                       LE            E
(begin)            (logical end)     (end)
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

int main()
{

    {
    std::vector<int> ivec = {1,1,1,1,2,2,2,2,3,3,4,5,5,5,1,2,3,4,5};
    printContainer("ivec", ivec);
    std::unique(ivec.begin(), ivec.end());
    printContainer("ivec", ivec);
    /*
    OUTPUT
    ------
    ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5 
    ivec: 1 2 3 4 5 1 2 3 4 5 4 5 5 5 1 2 3 4 5 
    */
    }

    {
    std::vector<int> ivec = {1,1,1,1,2,2,2,2,3,3,4,5,5,5,1,2,3,4,5};
    printContainer("ivec", ivec);
    std::remove_if(ivec.begin(), ivec.end(), [](const int a){return a%2 == 0;});
    printContainer("ivec", ivec);
    /*
    OUTPUT
    ------
    ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5 
    ivec: 1 1 1 1 3 3 5 5 5 1 3 5 5 5 1 2 3 4 5 
    */
    }


    return 0;
}