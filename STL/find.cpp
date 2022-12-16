/*
FIND
----

algorithm başlık dosyasında bulunur. Arama algoritmalarından birisidir.

Eğer aranan değer bulunursa bulunan öğenin konumunu, ancak bulunamazsa fonksiyona gönderilen range'in end iteratörünü dönüdürür.

minimum Input kategoride iteratör alır.

Sentaks
-------

bulunanan_iter find(begin_iter, end_iter, aranan_deger)

Eğer aranan değer bulunmazsa end_iter döner.



*/

#include<algorithm>
#include <iostream>
#include <vector>


int main()
{

    std::vector<std::string> svec = { "ab","ac","bb","dd" };


    if (auto find_iter = find(svec.begin(), svec.end(), "bb"); find_iter != svec.end())
    {
        std::cout << "bulundu: " << *find_iter <<" index: "<< std::distance(svec.begin(), find_iter)<<"\n";
    }
    else {
        std::cout << "bb bulunamadi";
    }



    if (auto find_iter = find(svec.begin(), svec.end(), "aa"); find_iter != svec.end())
    {
        std::cout << "bulundu: " << *find_iter << " index: "<<std::distance(svec.begin(), find_iter) <<"\n";
    }
    else {
        std::cout << "aa bulunamadi";
    }


    /*
    OUTPUT
    ------
    bulundu: bb index: 2
    aa bulunamadi
    */

    return 0;
}