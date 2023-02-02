/*
std::array
==========
C dizilerini sarmalayan (wrapper) bir sınıf şablonudur.

template< class T, std::size_t N >
struct array;

Avantajları
------------
-stl ile dizilere göre daha uyumlu hale geliyor.
-array kullanılırken array decay söz konusu. (dizinin ilk elemanın adresine dönüştürülmesi). Bu bazı durumlarda istenmiyor.
-C ve C++ dilleri boyutu 0 olan bir diziye izin vermiyor. Ancak generic programlama paradigmasında diğer containarlarda olduğu gibi boş bir kap gerekebiliyor.
-Exception handling'den kısıtlı olsada faydalanma imkanı sağlıyor.
-Fonksiyonlara parametre olarak veya dönüş değeri olarak kullanılabilir. C tipi arraylar bu şekilde direkt kullanılamaz.

performans konusunda C tipi arraye göre bir dezavantajı yok.

array sınıfı tanımlandığı zaman garbage value barındırır.

Array içerisinde tutulacak öğelerin default consturctble olması gerekiyor.

fill isimli fonksiyon ile array belirli değerlerle doldurulailir.

boş bir array 

empty fonksiyonu ile veya data fonksiyonu nullptr'ye göre karşılaştırılarak kontrol edilebilir.
boş bir array
[] operatörü ile
front veya bak fonksiyonu ile erişilmesi undefined behaviour 

*/

#include <iostream>
#include <array>


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

int main()
{
    std::array<double, 20> da;

    std::array<double, 20> da2{};

    printContainer("da", da);
    //da: 0 0 0 0 0 0 0 3.04933e-314 4.94066e-324 3.04933e-314 6.90421e-192 3.79442e-321 2.12203e-314 2.12203e-314 1.26481e-321 0 2.12203e-314 2.12203e-314 1.26481e-321 0 

    printContainer("da2", da2);
    //da2: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 

    da.fill(3.14);
    printContainer("da", da);
    //da: 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 3.14 

    for (int i = 0;i < 20; i++)
    {
        da.at(i) = i / 10.;
    }

    printContainer("da", da);
    //da: 0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 
    
    
    }