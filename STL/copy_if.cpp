/*
COPY_IF
------
Bir rangedeki belirli bir koşulu sağlayan değerleri başka range kopyalar




Sentaks
---------
outIter copy_if (source_begin, source_end, dest_begin, pred_function)



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
    std::list<int> ilist(ivec.size());

    printContainer("ivec", ivec);
    printContainer("ilist", ilist);

    auto copy_iter = std::copy_if(ivec.begin(), ivec.end(), ilist.begin(), [](const int i){return i%2;});

    printContainer("ivec", ivec);
    printContainer("ilist", ilist);

    std::cout<<"number of item was copied : "<<std::distance(ilist.begin(),copy_iter);




    /*
    OUTPUT
    -------
    ivec: 1 2 3 4 5 6 
    ilist: 0 0 0 0 0 0 
    ivec: 1 2 3 4 5 6 
    ilist: 1 3 5 0 0 0 
    number of item was copied : 3
    */


    return 0;
}