/*
unique
------
bir veri yapısındaki ögelerden ardışık tam sayı olanların sayısını bire indirmek

4 7 7 7 7 2 2 2 2 3 4 4 9 2 7 5 6 1 5 6

4 7 2 3 4 9 2 7 5 6 1 5 6

unique hale getirdikten sonra yanyana aynı öge olmayacak.

iki overload'u vardır. 
İlk overload equeal_to yani == sınaması yapıyor. 
İkinci overloadu binary pred alıyor. 

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

logical end ile end arasındaki ögeler silinmiş öge değeri olduğu konusunda bir garanti yok.

remove algoritmaları ile containerdan silme işlemi yaptıktan sonra, containerın kendi erase fonksiyonu ile ögeler gerçekten silinebilir.
Bu işleme remove erase fonksiyonu denir.

ivec.erase(std::remove(ivec.begin(), ivec.end(), 2);,ivec.end());

c++ 20'de remove erase idiomu yerine global erase fonksiyonu eklendi.
Bu fonksiyon ile referanse sematiği ile container'ı alıp silme işlemi yapıyor.

erase_if global fonksiyonu da bulunmaktadır. Belirli koşula göre silinmek istenilen ögelere göre silme işlemleri yapılabilir. 


remove_copy & remove_copy_if
----------------------------
silme işleminde sonrası vectorü girilen yeni range'e alarak silme işlemini yapıyor. .

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
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
        std::vector<int> ivec = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 5, 5, 5, 1, 2, 3, 4, 5};
        printContainer("ivec", ivec);
        auto logical_end = std::unique(ivec.begin(), ivec.end());
        printContainer("ivec", ivec);

        /*
        OUTPUT
        ------
        ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5
        ivec: 1 2 3 4 5 1 2 3 4 5 4 5 5 5 1 2 3 4 5
        */
    }

    {
        std::vector<int> ivec = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 5, 5, 5, 1, 2, 3, 4, 5};
        printContainer("ivec", ivec);
        auto logical_end = std::remove_if(ivec.begin(), ivec.end(), [](const int a)
                                          { return a % 2 == 0; });
        printContainer("ivec", ivec);
        /*
        OUTPUT
        ------
        ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5
        ivec: 1 1 1 1 3 3 5 5 5 1 3 5 5 5 1 2 3 4 5
        */
    }

    {
        std::vector<int> ivec = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 5, 5, 5, 1, 2, 3, 4, 5};
        printContainer("ivec", ivec);
        auto logical_end = std::remove(ivec.begin(), ivec.end(), 2);
        printContainer("ivec", ivec);
        /*
        OUTPUT
        ------
        ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5
        ivec: 1 1 1 1 3 3 4 5 5 5 1 3 4 5 1 2 3 4 5
        */

        // Gerçk silme işemi için
        ivec.erase(logical_end, ivec.end());
        printContainer("ivec", ivec);
        // ivec: 1 1 1 1 3 3 4 5 5 5 1 3 4 5
    }

    {
        std::vector<int> ivec = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 5, 5, 5, 1, 2, 3, 4, 5};
        printContainer("ivec", ivec);
        auto n = std::erase(ivec, 2);
        printContainer("ivec", ivec);
        std::cout<<"n : "<<n<<"\n";
        /*
        OUTPUT
        -----
        ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5
        ivec: 1 1 1 1 3 3 4 5 5 5 1 3 4 5
        n : 5
        */
    }

    {
        std::string s = "  kelime1    kelime2   kelime3 kelime4     ";
        std::cout<<"s: "<<s<<"\n";
        auto log_end = std::unique(s.begin(),s.end(), [](char c1, char c2)
        {
            return (isspace(c1) && isspace(c2));
        }
         );
        s.erase(log_end, s.end());
        std::cout<<"s: "<<s<<"\n";

        /*
        OUTPUT
        ------
        s:   kelime1    kelime2   kelime3 kelime4
        s:  kelime1 kelime2 kelime3 kelime4
        */
    }


        {
        std::vector<int> ivec = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 5, 5, 5, 1, 2, 3, 4, 5};
        std::vector<int> ivec2;
        printContainer("ivec", ivec);
        std::remove_copy(ivec.begin(), ivec.end(), std::back_inserter(ivec2), 2);
        printContainer("ivec2", ivec2);

        /*
        OUTPUT
        ------
        ivec: 1 1 1 1 2 2 2 2 3 3 4 5 5 5 1 2 3 4 5
        ivec2: 1 1 1 1 3 3 4 5 5 5 1 3 4 5
        */
    }

    return 0;
}