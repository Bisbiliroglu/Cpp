/*
UNORDERED CONTAINER
===================

hashtable veri yapısını implemente eden conteinerlardır. map ve set conteinerlar sıralı tutuarak ikili arama ağcı yapısında arama yaparken, unordered set ve map containerları karışık tutar.

unordered_set
unordered_multiset
unordered_map
unordered_multimap

burada amaç arama işleminin karmaşıklığını constant time'a düşürmek. set ve map için (assosiative continers) logaritmik karmaşıklığa sahip.
set anahtarın olup olmadığını map ise anahtara karşılık gelecek bir value'yu sağlar.
multi olanlar ise birden fazla anahtarı kabul eder.

Hash Table
----------
value'ler bir array'de (vectorelbir veri yapısı) tutulur. anahtar ise bir fonksiyondan geçirilerek bir indexe çevrilir ve bu indexteki veri geri döndürülür. Bu sayede constant time içerisinde veri alınmış olur.
anahtarı indekse çeviren fonksiyona hash function veya hasher olarka adlandırılır. Bu işlemin kendisine ise hashing denilir. Türkçe olarak bu işleme çırpılama, yapan fonksiyona ise çırpı fonksiyonu olarak adalndırılıyor.

hasher'dan beklenen iki önemli özellik vardır.
1.) Sürekli çağrılacağı için hızlı olması gerekiyor.
2.) Anahtarları mümkün olduğu kadar farklı indekslere dönüştürmesi gerekiyor.

hasher fonksiyonu ne kadar kaliteli olursa olsun kaçınılmaz bir şekilde belirli anahtarları aynı indekse döndürecektir. Bu duruma collision denilir. Dolayısıyla hashtable oluşturulurken collision'a karşı bir stratejisi olması gerekmektedir.

unorered_set ve unordered_multiset
----------------------------------

template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;

user define type için geliştiricininkendi hasher fonksiyonu oluşturması gerekir.

std::hasher fonksiyonun verdiği tam sayı size_t::min ile size_t::max arasındadır. unordered_containers bu değeri indekse çevirirler.
unordered containerlarda custom sınıflar tutmak için uygun hash fonksiyonu ve == fonksiyonlarının tanımlı olması gerekir.

custom hash fonksiyonu için iki metod var.
1. hash template için bir expilicit spacialization yazılabilir.
    template <>
    struct std::hash<CustomClass>
    {
        ostd::size_t operator()(const CustomClass& cs) const
        {
            .... hash algorithm codes  (boost hash fonksiyonu kullanılabilir)
        }
    }
2. Custom functor sınıfı yazılabilir
    struct CustomHasher{
        std::size_t operator()(const CustomClass & cs)  const
        {
            .... hash algorithm codes
        }
    }

    veya basit bir fonksiyon da olabilir.

    auto customHasher = [](const CustomClass & cs){ return ....hash};


unordered conteinerlarda hash sonrası yerleştirme işlemleri sonucu ögeler bucketlarda tutulur. Her bucket bir linked list olarka düşünülebilir. hash sonrası indeks dönüşümü bucket'ın indeksini verir.

size fonksiyonu tutulan öğe sayısını verir.

load_factor = containerda tutulan öğe sayısının cntainerda tutulan  bucket sayısına oranı. size/bucket.count
max_load_factor set veya get edilebiliyor.
Bucket count arttırıldığı zaman tekrar öğeler konumlandırılacak ve rehash yapılacak. Bunun bir maliyeti var.
max_load_factor : max_load_factor ne kadar büyük tutulursa re-hash gecikecek; En uygunu 0.7 0.8 arasında kullanmak. default değeri 1 olması biraz collision şansını arttırabiliyor.
bucket count toplam bucket sayısı
bucket.size her bucket için öğe sayısı
*/

#include<vector>
#include<iostream>
#include<unordered_set>
#include<functional>
class A
{
    public:
    int x = 5;
};



// custom specialization of std::hash can be injected in namespace std
template<>
struct std::hash<A>
{
    std::size_t operator()(A const& a) const 
    {
        return std::hash<int>{}(a.x);
    }
};


class AHasher
{
    public:
    std::size_t operator()(A const& a) const 
    {
        return std::hash<int>{}(a.x);
    }

};



int main()
{

    
    std::unordered_set<A > a_set1;
    std::unordered_set<A, AHasher > a_set2;



    return 0;
}