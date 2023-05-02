# Rastgele sayı üretimi

"Rastgelelik" tahmin edilemeyen bir durumu ifade eder. Rastgelelik, bir olayın önceden belirlenmiş bir düzene göre değil, tamamen şansa bağlı olarak gerçekleşmesidir.

"Rastgele sayı üretimi", belirli bir aralıkta, belirli bir düzene göre değil, tamamen rastgele bir şekilde seçilen bir sayıdır. Bu işlem, birçok alanda kullanılır, örneğin bilgisayar programlama, istatistik, kriptografi ve simülasyon gibi. Rastgele sayı üretimi, zar atma, anahtar oluşturma veya tesadüfi olayların simülasyonu gibi durumlarda kullanılabilir.

"Pseudo-rastgele sayı üretimi", belirli bir algoritma veya formülasyona dayalı olarak rastgele görünen sayıların üretilmesidir. Bu algoritmalar, gerçek rastgelelik kadar öngörülemez veya güvenli değildir. 

"True rastgele sayı üretimi" ise, tamamen öngörülemeyen ve rastgele bir şekilde oluşan sayıların üretilmesidir. Bu, fiziksel bir süreç veya doğal olaylar kullanılarak elde edilebilir. Örneğin, radyoaktif bozunma, atmosferik gürültü veya çevresel faktörler gibi doğal rastgelelik kaynakları kullanılabilir. True rastgele sayı üretimi, kriptografi, güvenli iletişim, finansal işlemler ve diğer güvenlik odaklı uygulamalarda kullanılır.

# CPP'de Rastgele Sayı Üreticileri

 C içerisinde rand ve srand fonksiyonları ile rastgele sayı üretilebilmektedir. Ancak bu fonksiyonların rastgele sayının önemli olabileceği problemlerde kullanılmaması gerekmektedir.

C++ ile birlikte random kütüphanesi eklenmiştir. Bu kütüphane içerisindeki rastgele sayı üreticilerinin kriptoloji içerisinde kullanılmaması önerilmektedir. Random kütüphanesi iki bölüme ayrılır. Bunlar random number generation ve distribution bölümleridir.

Uniform random number generator içerisinde mersenne twister ve lagged fibonacci algoritmaları kullanılmaktadır. Distribution ise üretilen rastgele sayı kümesinin belirli bir düzene göre üretilmesini sağlar. Örneğin, rastgele sayılar %55 true ve %45 false olabilir.

Rastgele sayı üreticileri distribution formatları ile birlikte kullanılmaktadır. Random kütüphanesi içerisinde rastgele sayı üretiminin template şablonları bulunmaktadır. Bu şablonlar engine olarak isimlendirilir ve kodlarda bu enginelerin çeşitli parametrelerde oluşturulmuş specializationları kullanılmaktadır. Örneğin, mt19937, mersenne twister algoritmasının özel parametrelerle oluşturulmuş bir specialization'ıdır.

Rastgele sayı üretiminde başlangıçta kullanılan bir değer vardır. Bu değere tohum değeri denir (seed value) ve bu tohum değeri ile üretilecek rastgele sayı zinciri oluşturulur. Her seferinde aynı tohum değeri için aynı output çıkacaktır. C++ standard kütüphanesi aynı seed değerine sahip rastgele sayı üreticileri için aynı çıktıyı garanti etmektedir. Derleyici değişse bile aynı çıktılar üretilecektir. Ancak distribution sınıflarının implementasyonu aynı olmak zorunda değildir.

### Rastgele Sayı Üreticileri

Rastgele sayı üreticileri, seed data kullanarak pseudo-random sayılar üretir. Çeşitli farklı pseudo-random sayı üretme algoritmaları şablonlar olarak özelleştirilebilir.

Hangi engine'in kullanılacağı, birkaç trade-off'a bağlıdır: linear congruential engine, hızlıdır ve durum için çok küçük bir depolama gereksinimi vardır. Lagged Fibonacci üreteçleri, daha az istenen spektral özelliklere sahip olsa da, gelişmiş aritmetik komut kümesi olmayan işlemcilerde bile çok hızlıdır ve daha büyük depolama gereksinimleri vardır. Mersenne twister, doğru parametrelerle en uzun tekrarlamayan sekansı ve en istenen spektral özellikleri (verilen istenen tanım için) en uzun süreli sağlayan, daha yavaş ve daha fazla durum depolama gereksinimleri olan bir engine'dir.

Mersenne twister, içerisinde tekrar etmeyen en uzun sekansı sağladığı için, fazla yer kaplamasına ve yavaş olmasına rağmen en çok kullanılan rastgele sayı üreticisidir.

Aşağıdaki tabloda, C++ standard kütüphanesi içerisinde bulunan rastgele sayı üreticileri yer almaktadır:

[linear congruential](https://en.cppreference.com/w/cpp/numeric/random/linear_congruential_engine) : yeterince hızlı ve az bellek alanı istiyor

[lagged Fibonacci](https://en.cppreference.com/w/cpp/numeric/random/subtract_with_carry_engine) : çok bellek kullanılıyor ancak hızlı

[Mersenne twister](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine): yavaş ve fazla bellek kaplıyor

Rastgele sayı üreticileri belirli bir sekans sonunda tekrar etmesi gerekiyor. Mersenne twister içerisinde tekrar etmeyen en uzun sekansı Mersenne twister sağlıyor. 

| https://en.cppreference.com/w/cpp/numeric/random/linear_congruential_engine(C++11) | implements https://en.wikipedia.org/wiki/Linear_congruential_generator algorithm |
| --- | --- |
| mersenne_twister_engine(C++11) | implements Mersenne twister algorithm(class template) |
| subtract_with_carry_engine(C++11) | implements a subtract-with-carry (lagged Fibonacci) algorithm(class template) |

Default Random Engine: Derleyicinin kendi default verdiği rastgele sayı üreticisidir. Genelde  derleyiciler MT19937 kullanır. 

### random_device

[std::random_device - cppreference.com](https://en.cppreference.com/w/cpp/numeric/random/random_device)

Eğer derleyici destekliyorsa gerçek rastgele sayı verir. Ana akım derleyiciler implemente etmiştir. 

Rastgele sayı üreticilri kullanarak rasgtele sayı üretiminde seed değeri olarak random_device çıktısı veya epoch zaman değeri kullanılırsa her program açılışında farklı rastgele sayı seti üretilebilir.

```cpp
#include <iostream>
#include <map>
#include <random>
#include <string>
 
int main()
{
    std::random_device rd;
    std::map<int, int> hist;
    std::uniform_int_distribution<int> dist(0, 9);
 
    for (int n = 0; n != 20000; ++n)
        ++hist[dist(rd)]; // note: demo only: the performance of many
                          // implementations of random_device degrades sharply
                          // once the entropy pool is exhausted. For practical use
                          // random_device is generally only used to seed
                          // a PRNG such as mt19937
 
    for (auto [x, y] : hist)
        std::cout << x << " : " << std::string(y / 100, '*') << '\n';
}

/*
OUTPUT:
0 : ********************
1 : *******************
2 : ********************
3 : ********************
4 : ********************
5 : *******************
6 : ********************
7 : ********************
8 : *******************
9 : ********************

*/
```

## Disturbition

Rastgele sayı üretiminde "distribution" (dağılım), belirli bir aralık veya olasılık dağılımına uygun rastgele sayılar üretmek için kullanılan bir kavramdır. Örneğin, bir uniform distribution (eşit dağılım), belirli bir aralıktaki tüm sayıların eşit olasılıkla üretilmesini sağlar. Normal distribution (normal dağılım), örneklem sayısı arttıkça ortalaması belirli bir değere yaklaşan bir dağılımdır.

### uniform_int_distirbution:

[std::uniform_int_distribution - cppreference.com](https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution)

min ve max paramereli ctoru vardır. bu değerler üretilen çıktı için dahildir.

```cpp
#include <iostream>
#include <random>
 
int main()
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);
 
    // Use distrib to transform the random unsigned int
    // generated by gen into an int in [1, 6]
    for (int n = 0; n != 10; ++n)
        std::cout << distrib(gen) << ' ';
    std::cout << '\n';
}

//OUTPUT: 1 1 6 5 2 2 5 5 6 2
```

### uniform_real_distirbution:

[std::uniform_real_distribution - cppreference.com](https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution)

min ve max değer aralığı için ondalık rastgele sayı üretiminde kullanılır. 

```cpp
#include <random>
#include <iostream>
 
int main()
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1.0, 2.0);
    for (int n = 0; n < 10; ++n) {
        // Use dis to transform the random unsigned int generated by gen into a 
        // double in [1, 2). Each call to dis(gen) generates a new random double
        std::cout << dis(gen) << ' ';
    }
    std::cout << '\n';
}

//OUTPUT: 1.80829 1.15391 1.18483 1.38969 1.36094 1.0648 1.97798 1.27984 1.68261 1.57326
```

### Normal Distubition

[std::normal_distribution - cppreference.com](https://en.cppreference.com/w/cpp/numeric/random/normal_distribution)

Çan eğrisi veya gauss dağılımı için kullanılır. 

Ctor ilk değeri aritmetik ortalama ikinci değeri ise standart sapma değeridir. 

```cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
 
int main()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{5, 2};
 
    std::map<int, int> hist{};
    for (int n = 0; n != 10000; ++n)
        ++hist[std::round(d(gen))];
 
    for (auto [x, y] : hist)
        std::cout << std::setw(2) << x << ' ' << std::string(y / 200, '*') << '\n';
}

/*

OUTPUT:

-2
-1
 0
 1 *
 2 ***
 3 ******
 4 ********
 5 **********
 6 ********
 7 *****
 8 ***
 9 *
10
11
12

*/
```

### **bernoulli_distribution**

[std::bernoulli_distribution - cppreference.com](https://en.cppreference.com/w/cpp/numeric/random/bernoulli_distribution)

bernoulli distirbution sonucunda sadece true veya false değeri alınır. Bernoulli distirbution ile sonuç alınırken sadece true false oranı verilir. 

```cpp
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // give "true" 1/4 of the time
    // give "false" 3/4 of the time
    std::bernoulli_distribution d(0.25);
 
    std::map<bool, int> hist;
    for (int n = 0; n < 10000; ++n)
        ++hist[d(gen)];
 
    std::cout << std::boolalpha;
    for (auto const& [key, value] : hist)
        std::cout << std::setw(5) << key << ' '
                  << std::string(value / 500, '*') << '\n';
}

OUTPUT:
/*
false ***************
true ****
*/
```

### **discrete_distribution**

[std::discrete_distribution - cppreference.com](https://en.cppreference.com/w/cpp/numeric/random/discrete_distribution)

Üretilen rastgele sayının bazırlarınının daha fazla veya daha az üretilmesini sağlamak için kullanılır. Örnek olarak hileli zar varilebilir. tüm sayılarının belirli miktarda olması ancak 6 sayısının fazla olması gibi. 

Birden fazla ctoru var ancak en fazla initializer_list parametreli kullanılır. 

```cpp
discrete_distribution( std::initializer_list<double> weights );
```

Bu ctor ile  0 sayısınından başlayarak çıkan sonuçlar için ağırlık bilgisi girilir.  Bunun haricinde range parametreli ctoru da vardır.

```cpp
template< class InputIt >
discrete_distribution( InputIt first, InputIt last );
//first, last	-	the range of elements defining the numbers to use as weights. 
//The type of the elements referred by InputIterator must be convertible to double
```

```cpp
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({40, 10, 10, 40});
    std::map<int, int> map;
 
    for (int n = 0; n < 1e4; ++n)
        ++map[d(gen)];
 
    for (const auto& [num, count] : map)
        std::cout << num << " generated " << std::setw(4) << count << " times\n";
}

/*
OUTPUT:

0 generated 4037 times
1 generated  962 times
2 generated 1030 times
3 generated 3971 times

*/
```

## Rastgele Sayı Üretimi ile İlgili Algoritmalar

### shuffle

[std::random_shuffle, std::shuffle - cppreference.com](https://en.cppreference.com/w/cpp/algorithm/random_shuffle)

Bir veri yapısını rastgele karıştırmak için kullanılır.

```cpp
template< class RandomIt, class URBG >
void shuffle( RandomIt first, RandomIt last, URBG&& g );

/*
Reorders the elements in the given range [first, last) such that each possible permutation of those elements has equal probability of appearance.

1) The source of randomness is implementation-defined, but the function std::rand is often used.
2) The source of randomness is the function object r.
3) The source of randomness is the object g.

*/
```

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
 
int main()
{
    std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);
 
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

/*
OUTPUT:
8 6 10 4 2 3 7 1 9 5
*/
```

## Referans

[https://en.cppreference.com/w/cpp/numeric/random](https://en.cppreference.com/w/cpp/numeric/random)