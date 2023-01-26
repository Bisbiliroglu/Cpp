/*
MAP
----

set ile aynı veri yapısı ancak farklı olarak anahtar karşılığı bir value'e erişiliyor. 
Bunun için pair tutuluyor. 
    pair.first key
    pair.second value

map ile set interfaceleri çok farklı değil. 

map içerisinde bir anahtardan bir tane tutulabilir. Ancak multimapte birden fazla tutulabilir.

template<
    class Key, (anahtarın türü)
    class T,  (value türü)
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
> class map;

mymap insert fonksiyonuna pair argümanı girilerek insert işlemi ypaılabilir.
emplace fonksiyonu için (key,value) argümanı yapılarka ekleme yapılabilir.

arama fonksiyonlarında key aranmaktadır. Fonksiyon sonucunda iter<pair> dönmektedir. Bu pair ilk değeri key, ikinci değeri value'dir. 

değiştirme işlemleri için set'de olduğu gibi ya silip tekrar ekleme yapmak gereikiyor ya da extract yapmak gerekiyor. 
map içerisinde value değiştirme işlemi [key] operatörüne assign işlemi ile de yapılabiliyor. 
 
map içerisinde sıralama işlemleri value'ye göre oluyor

lower bound
------------
bir değerin range içerisinde sırayı bozmadan insert edilebileceği ilk konum. 


upper bound
-----------
bir değerin range içerisinde sırayı bozmadan insert edilebileceği son konum. 


equal range
------------
lower bound ile upper bound arasındaki range.
equal range 'in distance o anahtardan kaç tane olduğunun sayısıdır. 


[] operator fonksiyonu
----------------------
Bu fonksiyon sadece map'te bulunuyor. multimapte yok.
bu fonksiyın non-const fonksiyon olduğu için const map nesneleri için çağrılamaz.

mappedType& operator[](const keyType&)

map<int,string>

string <- mymap[int]

eğer mapte girilen anahtar varsa o anahtara ait ögenin değerini değiştiriyor. 
eğer mapte girilen anahtar yoksa o anahtar için value initialized edilmiş ögenin secondını eriştiriyor. Yani anahtar yoksa istenilen ögeyi ekliyor.

mymap[5] = Baris;
Eğer mapte 5 keyli bir öge varsa o ögenin değerini "baris" ile değişitiriyor.
Eğer mapta 5 keyli bir öge yoksa 5 key için "baris" değerini ekliyor.

dezavantajları
----------------
mapte tutulacak pairin second (value değeri) default ctor'u olması gerekiyor. 
geri dönüş değeri value olduğu için ekleme mi yaptığı yoksa değiştirme mi yaptığı anlaşılmıyor. 


cpp17 ile beraber bu dezavantajların üstesinden gelmek için insert_or_assign fonksiyonu eklendi. [] operatörü ile aynı işlemi yerine getiriyor.
geri dönüş değeri iteratör bool geliyor. dolayısıyla insert mü edilmiş yoksa var olan öğeye mi eriştiği anlaşılabiliyor.

bir map başka bir mape (aynı türden) merge edilebilir. bunun için merge fonksiyonu kullanılıyor.

*/

#include <iostream>
#include <map>

template  <typename T>
void printmap(const T & map)
{
    for (auto &[key , value] : map)
    {
        std::cout<<"key: "<<key<<" value: "<<value<<"\n";
    }

}

int main ()
{

    using namespace std;

    {
        map<int, int> mymap {
            {1,9},
            {2,8},
            {3,7},
            {4,7}

        } ;

    mymap.insert(make_pair(5,5));
    mymap.emplace(6,4);
    printmap(mymap);

    if(auto iter = mymap.find(5); iter != mymap.end())
    {
        cout<<"Found Key: "<<iter->first<<" value: "<<iter->second<<"\n";
    }

    /*
    OUTPUT
    ------
    key: 1 value: 9
    key: 2 value: 8
    key: 3 value: 7
    key: 4 value: 7
    key: 5 value: 5
    key: 6 value: 4
    Found Key: 5 value: 5
    */
    }

    return 0;
}