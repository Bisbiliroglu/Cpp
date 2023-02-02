/*

https://en.cppreference.com/w/cpp/utility/tuple

TUPLE
=====

tuple pair'in çoklusu. istenilen sayıdaki öğe demet çeşlinde bir arada tutulabiliyor.

template< class... Types >
class tuple;

get interface'i ile veya c++17 de gelen structure binding ile ögelere erişilebilir.
get interface ile geçersiz index doğrudan compile time'da anlaşalılabiliyor. Dolayısıyla sentaks hatası veriyor.

tuple'a dinamik olarak eleman eklenemiyor.

aynı tüden tüm tuple ögeleri birbirleriyle karşılaştıırlabilir.
Tüm öge nesneleri sırayla birbirleri ile karşılaştırılır.
Küçükten büyüğe sıralama yapılıp yazdırılırsa
önce 1. ögenin küçükten büyüe gittiği görülür. İlk değeri aynı olanların 2. ögelerin sıralandığı görülür. 2. öge aynı olanların 3. ögelerinin sıralandığı görülür ve böyle devam eder.

diğer containerlara template parametre olarak referans atanamazken, pair ve tuple'a atılabilir.

tuble element il e
*/

#include <tuple>
#include <iostream>

std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    if (id == 3) return std::make_tuple(0.6, 'F', "Bart Simpson");

    throw std::invalid_argument("id");
}




int main()
{
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
        << "GPA: " << std::get<0>(student0) << ", "
        << "grade: " << std::get<1>(student0) << ", "
        << "name: " << std::get<2>(student0) << '\n';

    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
        << "GPA: " << gpa1 << ", "
        << "grade: " << grade1 << ", "
        << "name: " << name1 << '\n';

    // C++17 structured binding:
    auto [gpa2, grade2, name2] = get_student(2);
    std::cout << "ID: 2, "
        << "GPA: " << gpa2 << ", "
        << "grade: " << grade2 << ", "
        << "name: " << name2 << '\n';

    auto student3 = get_student(3);
    std::cout << "ID: 3, "
        << "GPA: " << std::get<double>(student3) << ", "
        << "grade: " << std::get<char>(student3) << ", "
        << "name: " << std::get<std::string>(student3) << '\n';

    /*
    OUTPUT
    -----
    ID: 0, GPA: 3.8, grade: A, name: Lisa Simpson
    ID: 1, GPA: 2.9, grade: C, name: Milhouse Van Houten
    ID: 2, GPA: 1.7, grade: D, name: Ralph Wiggum
    ID: 3, GPA: 0.6, grade: F, name: Bart Simpson
    */

    int x = 5;
    int y = 14;


    //swap with tuple
    std::cout << "x: " << x << " y: " << y << "\n";
    std::tie(x, y) = std::tuple{ y,x };
    std::cout << "x: " << x << " y: " << y << "\n";
    /*
    OUTPUT
    ------
    x: 5 y: 14
    x: 14 y: 5
    */


}