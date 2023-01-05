/*

Spaceship <=> operator (three-way comparison operator)
----------------------
C++ 20 ile eklendi
C++ 20 ile == opetör fonksiyonlarında değişiklik yapıldı.

bool operator==(const Classs&) const ile == operatörü yazılınca C++ 20 öncesinde != operatörü sentaks hatası veriyordu.
C++20 sonrasında == operatörü yazılınca derleyici != operatörünü de yazıyor.

MyClass17 sınıfında C++ 20 öncesi için karşılaştırma operatörleri yazılmıştır.

CPP 20 ile == operatörü yazılınca != operatörünü de yazmaktadır. Aynı zamanda operatörler swap edebilmektedir.

default eden == operatörü tüm değişkenleri && ile bağlıyor hepsi eşit ise true dönüyor.

<=> operatörünü kullanmak için compare başlık dosyasını include etmek gerekiyor.
compare başlık dosyası ile bazı sınıflar geliyor

partial_ordering: karşılaştırılamayan ögeler içeriyor. Örnek gerçek sayı sınıfında sonsuz değerler sayı olmayan değerler gibi.
strong_ordering: ya birinci büyük ya ikinci büyük ya da eşit. Örnek iki intin karşılaştıırlması
weak_ordering: strong_ordering + equvelent (birbirine denk) olabiliyor. "masa" "MASA" gibi case sensitive olduğu zaman "masa" > "MASA" int sensitive için eşit

Primitve türden değerleri karşılaştırmak için spaceship operatörünü kullanmaya gerek yok.
Spaceship operatörü C++ 20 ile geldi ve default edilebiliyor. Eğer default edilirse <, <= >, >= == ve != operatörlerini (yani tüm karşılaştırma operatörlerini) yazmaya gerek yok.
MyClass20 ve MyClass17 sınıfları karşılaştırma operatörleri aynı işlemleri yapmaktadır. 
*/
#include <iostream>
#include <compare>

class MyClass20
{

public:
    MyClass20(int value) : m_c(value) {}
    auto operator<=>(const MyClass20 &) const = default;

private:
    int m_c{};
};

class MyClass17
{
public:
    MyClass17(int value) : m_c(value) {}

    bool operator<(const MyClass17 &other) const
    {
        return m_c < other.m_c;
    }

    bool operator>(const MyClass17 &other) const
    {
        return other.m_c < m_c;
    }

    bool operator<=(const MyClass17 &other) const
    {
        return !(other.m_c < m_c);
    }

    bool operator>=(const MyClass17 &other) const
    {
        return !(m_c < other.m_c);
    }

    bool operator==(const MyClass17 &other) const
    {
        return m_c == other.m_c;
    }

    bool operator!=(const MyClass17 &other) const
    {
        return !(m_c == other.m_c);
    }

private:
    int m_c{};
};

int main()
{

    int x = 0, y = 42;
    // if((x <=> y) == std::strong_ordering::greater)
    if ((x <=> y) > 0) // x > y
    {
        std::cout << "x(" << x << ")>y(" << y << ")\n";
    }

    if ((x <=> y) < 0) // x < y
    {
        std::cout << "x(" << x << ")<y(" << y << ")\n";
    }

    if ((x <=> y) == 0) // x == y
    {
        std::cout << "x(" << x << ")==y(" << y << ")\n";
    }

    MyClass17 mc17(10);
    MyClass20 mc20(10);

    std::cout << "--------------------------------------\n";
    std::cout << "mc17 == 10 " << (mc17 == 10) << "\n";
    std::cout << "mc17 == 11 " << (mc17 == 11) << "\n";
    std::cout << "mc17 != 11 " << (mc17 != 11) << "\n";
    std::cout << "mc17 != 10 " << (mc17 != 10) << "\n";
    std::cout << "mc17 <= 10 " << (mc17 <= 10) << "\n";
    std::cout << "mc17 <= 11 " << (mc17 <= 11) << "\n";
    std::cout << "mc17 <= 9 " << (mc17 <= 9) << "\n";
    std::cout << "mc17 >= 10 " << (mc17 >= 10) << "\n";
    std::cout << "mc17 >= 11 " << (mc17 >= 11) << "\n";
    std::cout << "mc17 >= 9 " << (mc17 >= 9) << "\n";
    std::cout << "mc17 < 10 " << (mc17 < 10) << "\n";
    std::cout << "mc17 < 11 " << (mc17 < 11) << "\n";
    std::cout << "mc17 < 9 " << (mc17 < 9) << "\n";
    std::cout << "mc17 > 10 " << (mc17 > 10) << "\n";
    std::cout << "mc17 > 11 " << (mc17 > 11) << "\n";
    std::cout << "mc17 > 9 " << (mc17 > 9) << "\n";
    std::cout << "--------------------------------------\n";
    std::cout << "mc20 == 10 " << (mc20 == 10) << "\n";
    std::cout << "mc20 == 11 " << (mc20 == 11) << "\n";
    std::cout << "mc20 != 11 " << (mc20 != 11) << "\n";
    std::cout << "mc20 != 10 " << (mc20 != 10) << "\n";
    std::cout << "mc20 <= 10 " << (mc20 <= 10) << "\n";
    std::cout << "mc20 <= 11 " << (mc20 <= 11) << "\n";
    std::cout << "mc20 <= 9 " << (mc20 <= 9) << "\n";
    std::cout << "mc20 >= 10 " << (mc20 >= 10) << "\n";
    std::cout << "mc20 >= 11 " << (mc20 >= 11) << "\n";
    std::cout << "mc20 >= 9 " << (mc20 >= 9) << "\n";
    std::cout << "mc20 < 10 " << (mc20 < 10) << "\n";
    std::cout << "mc20 < 11 " << (mc20 < 11) << "\n";
    std::cout << "mc20 < 9 " << (mc20 < 9) << "\n";
    std::cout << "mc20 > 10 " << (mc20 > 10) << "\n";
    std::cout << "mc20 > 11 " << (mc20 > 11) << "\n";
    std::cout << "mc20 > 9 " << (mc20 > 9) << "\n";

    /*
    OUTPUT
    --------
    mc17 == 10 1
    mc17 == 11 0
    mc17 != 11 1
    mc17 != 10 0
    mc17 <= 10 1
    mc17 <= 11 1
    mc17 <= 9 0
    mc17 >= 10 1
    mc17 >= 11 0
    mc17 >= 9 1
    mc17 < 10 0
    mc17 < 11 1
    mc17 < 9 0
    mc17 > 10 0
    mc17 > 11 0
    mc17 > 9 1
    --------------------------------------
    mc20 == 10 1
    mc20 == 11 0
    mc20 != 11 1
    mc20 != 10 0
    mc20 <= 10 1
    mc20 <= 11 1
    mc20 <= 9 0
    mc20 >= 10 1
    mc20 >= 11 0
    mc20 >= 9 1
    mc20 < 10 0
    mc20 < 11 1
    mc20 < 9 0
    mc20 > 10 0
    mc20 > 11 0
    mc20 > 9 1

    */

    return 0;
}