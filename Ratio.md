# ratio

[std::ratio - cppreference.com](https://en.cppreference.com/w/cpp/numeric/ratio/ratio)

template<

[std::intmax_t](https://en.cppreference.com/w/cpp/types/integer) Num,

[std::intmax_t](https://en.cppreference.com/w/cpp/types/integer) Denom = 1

> class ratio;

---

**`std::ratio`**, oranları temsil etmek ve oranlarla matematiksel işlemler yapmak için kullanılan bir compile time kütüphanesidir. 

**`std::ratio`** iki tane non-type parametreye sahiptir. Birinci template parametresine karşılık gelen template argümanı kesrin pay değerini, ikinci template parametresine karşılık gelen template argümanı kesrin payda değerine karşılık gelmektedir. Örneğin, 2/3 oranını std::ratio<2, 3> şeklinde ifade edilir.Eğer ikinci template argümanı yazılması default değeri 1 kullanılır. 

**`std::ratio`** kütüphanesinden pay değerini almak için num fonksiyonu, payda değerini almak için den fonksiyonu kullanılabilir. Ancka bu değerler compile time zamanında sadeleştirilir. 

```cpp
#include <iostream>
#include <ratio>

int main() {
    // Oranları tanımlama
    typedef std::ratio<2, 3> Ratio1;  // 2/3
    typedef std::ratio<6, 8> Ratio2;  // 6/8 -> 3/4

    // Oranları ekrana yazdırma
    std::cout << "Ratio1: " << Ratio1::num << "/" << Ratio1::den << std::endl;
    std::cout << "Ratio2: " << Ratio2::num << "/" << Ratio2::den << std::endl;

    // Oranları toplama
    typedef std::ratio_add<Ratio1, Ratio2> SumRatio;
    std::cout << "SumRatio: " << SumRatio::num << "/" << SumRatio::den << std::endl;

    // Oranları çarpma
    typedef std::ratio_multiply<Ratio1, Ratio2> ProductRatio;
    std::cout << "ProductRatio: " << ProductRatio::num << "/" << ProductRatio::den << std::endl;

    return 0;
}

/*
OUTPUT:
Ratio1: 2/3
Ratio2: 3/4
SumRatio: 17/12
ProductRatio: 1/2
*/
```

| Fonksiyon | Açıklama |
| --- | --- |
| num | std::ratio nesnesinin payını temsil eden std::ratio sınıfının sabit üyesi |
| den | std::ratio nesnesinin paydasını temsil eden std::ratio sınıfının sabit üyesi |
| ratio_add | İki std::ratio nesnesini toplar ve sonucu temsil eden std::ratio türünü döndürür |
| ratio_subtract | İki std::ratio nesnesini çıkarır ve sonucu temsil eden std::ratio türünü döndürür |
| ratio_multiply | İki std::ratio nesnesini çarpar ve sonucu temsil eden std::ratio türünü döndürür |
| ratio_divide | İki std::ratio nesnesini böler ve sonucu temsil eden std::ratio türünü döndürür |
| ratio_equal | İki std::ratio nesnesinin eşit olup olmadığını kontrol eder |
| ratio_not_equal | İki std::ratio nesnesinin eşit olmadığını kontrol eder |
| ratio_less | Bir std::ratio nesnesinin diğerinden küçük olup olmadığını kontrol eder |
| ratio_less_equal | Bir std::ratio nesnesinin diğerinden küçük veya eşit olduğunu kontrol eder |
| ratio_greater | Bir std::ratio nesnesinin diğerinden büyük olup olmadığını kontrol eder |
| ratio_greater_equal | Bir std::ratio nesnesinin diğerinden büyük veya eşit olduğunu kontrol eder |