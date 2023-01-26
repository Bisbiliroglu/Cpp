/*
https://en.cppreference.com/w/cpp/container/set
https://github.com/umutkotankiran/Cpp/blob/main/33_29_08_2021/main.cpp

SET
---
tipik olarak var mı yok mu sorgusu için kullanılıyor.

template<class Key,class Compare = std::less<Key>,class Allocator = std::allocator<Key>>
class set;

kullanılan iteratörler bi-directional iteratörleri.

karşılaştırma operandı geliştirici yazmak isterse çeşitli garantileri vermek zorunda

!(a op b) && !(b op a)

a op b = true ise b op a = false olacak (veya tam tersi) (antisymetric)

a op a her zaman false olacak. (irrefelixice)

a op b = ture ve b op c = true ise a op c 'de true olması gerekir.  (transitive)

set için aynı değerden ikisinin eklenmesi mümkün değil. Ancak multiset için eklenebilir.

insert fonksiyonu pair gönderiyor. second işlemi boolean. ekleme yapılırsa true, değilse false döner. first ise eklenen değerin iteratörünü döner.

set içerisindeki anahtarı değiştirmek için iki yol var.
1. Anahatarı silip yeni anahtarı eklemek. (find -> erase -> insert)

set'in insert fonksiyonu pair döndürmektedir. Bu pair <iter,bool> şeklinde. eğer bool true ise ekleme yapıldığı, false ise ekleme yapılmadığını göstermektedir.
multisette ekleme yapılma garantisi vardır.

set içerisinde diğer insert fonksiyonlarında olmayan iteratör parametreli insert fonksiyonu bulunmaktadır. Burada set için girilen yere ekleme yapmaktan ziyada eklenecek yer için bir hint verilmektedir.
diğer bir amacı ise inserter fonksiyonu (iteratör adaptörü) ile beraber kullanmaktadır.

Bu hint insertün emplace fonksiyonu için emplace_hint şeklinde ekstra bir fonksiyon bulunmaktadır.

erase fonksiyonu geri dönüş değeri silinen öge sayısı. Yani o anahtara ait tüm ögeleri siliyor. set için geri dönüş değeri 1 iken multiset için birden fazla oluyor.

extract fonksiyonu: set içerisinden bir node çıkartmaktadır. Bextractın geri dönüş değeri node handle fonksiyonudur. Bu fonksiyon düğümde tutulan nesneye erişim sağlamaktadır. 
set içerisinde değer değiştirmek için kullanılabilir.


upper bound, lower bound ve equal range bahsetmek için sıralanmış bir range olması gerekmektedir.

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


*/

#include<set>
#include<iostream>

int main()
{
    {
        using namespace std;
        set<int> myset;
        for (int i = 100; i >= 0; i--)
        {
            if (i % 2 == 0)
            {
                myset.insert(i);
            }
        }

        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            cout << *iter << " ";
        }
        cout << "\n";

        /*
        OUTPUT
        ------
        0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 50 52 54 56 58 60 62 64 66 68 70 72 74 76 78 80 82 84 86 88 90 92 94 96 98 100
        //Büyükten küçüğe insert edilse dahi set'in default comparatörü less oldupu için küçükten büyüğe sıraladı. Rastgele sayılar girilseydi de küçükten büyüğe sıralanmış olacaktı.
        */
    }

    {
        using namespace std;
        set<int, greater<int>> myset;
        for (int i = 100; i >= 0; i--)
        {
            if (i % 2 == 0)
            {
                myset.insert(i);
            }
        }

        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            cout << *iter << " ";
        }
        cout << "\n";

        /*
        OUTPUT
        ------
        100 98 96 94 92 90 88 86 84 82 80 78 76 74 72 70 68 66 64 62 60 58 56 54 52 50 48 46 44 42 40 38 36 34 32 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2 0
        //karşılaştırma operatörü greater verildiği için büyükten küçüğe sıraladı.
        */
    }

    {
        std::set<int> myset{ 3,4,2,1,7,6,2,2,2,8,24,15,17,0,8 };
        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n";
        /*
        OUTPUT
        ------
        0 1 2 3 4 6 7 8 15 17 24
        */

    }


    {
        std::multiset<int> myset{ 3,4,2,1,7,6,2,2,2,8,24,15,17,0,8 };
        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n";
        /*
        OUTPUT
        ------
        0 1 2 2 2 2 3 4 6 7 8 8 15 17 24
        */

    }

    {
        using namespace std;
        set<string> myset{ "ali", "ayse", "veli" , "ahmet", "baris" };
        if (auto [iter, success] = myset.insert("fatma"); success) //[] ile pairi iki değiskende almak structure binding set ile alakası yok. Tüm pair döndüren fonksiyonlarda kullanılabilir. 
        {
            cout << *iter << " eklendi\n";
        }
        else {
            cout << *iter << " eklenmedi. set içerisinde mevcut\n";
        }

        if (auto [iter, success] = myset.insert("baris"); success)
        {
            cout << *iter << " eklendi\n";
        }
        else {
            cout << *iter << " eklenmedi. set icerisinde mevcut\n";
        }

        string name = "fatma";
        if (auto iter = myset.find(name); iter != myset.end())
        {
            cout << name << " set icerisinde mevcut indeks: " << distance(myset.begin(), iter) << "\n";
        }
        name = "tarkan";
        if (auto iter = myset.find(name); iter != myset.end())
        {
            cout << name << " set icerisinde mevcut indeks: " << distance(myset.begin(), iter) << "\n";
        }
        name = "ahmet";
        if (auto cnt = myset.count(name); cnt > 0)
        {
            cout << name << " set icerisinde mevcut " << cnt << " tane var\n";
        }

        name = "fatma";
        if (myset.contains(name)) //cpp 20 ile eklendi
        {
            cout << name << " set icerisinde mevcut \n";

        }

        myset.erase(name);
        if (myset.contains(name)) //cpp 20 ile eklendi
        {
            cout << name << " set icerisinde mevcut \n";
        }
        else
        {
            cout << name << " set icerisinde mevcut degil \n";
        }
        /*
        OUTPUT
        -----
        fatma eklendi
        baris eklenmedi. set icerisinde mevcut
        fatma set icerisinde mevcut indeks: 4
        ahmet set icerisinde mevcut 1 tane var
        fatma set icerisinde mevcut
        fatma set icerisinde mevcut degil
        */
    }

    {
        using namespace std;
        multiset<string> myset{ "ali", "ayse", "veli" , "ahmet", "baris" };
        string name = "fatma";

        myset.insert(name);
        myset.insert(name);
        myset.insert(name);

        myset.insert("ahmet");
        myset.insert("ahmet");


        if (auto iter = myset.find(name); iter != myset.end())
        {
            cout << name << " set icerisinde mevcut indeks: " << distance(myset.begin(), iter) << "\n";
        }
        name = "tarkan";
        if (auto iter = myset.find(name); iter != myset.end())
        {
            cout << name << " set icerisinde mevcut indeks: " << distance(myset.begin(), iter) << "\n";
        }
        name = "ahmet";
        if (auto cnt = myset.count(name); cnt > 0)
        {
            cout << name << " set icerisinde mevcut " << cnt << " tane var\n";
        }

        name = "fatma";
        if (myset.contains(name)) //cpp 20 ile eklendi
        {
            cout << name << " set icerisinde mevcut \n";

        }

        myset.erase(name);
        if (myset.contains(name)) //cpp 20 ile eklendi
        {
            cout << name << " set icerisinde mevcut \n";
        }
        else
        {
            cout << name << " set icerisinde mevcut degil \n";
        }
        /*
        OUTPUT
        -----
        fatma set icerisinde mevcut indeks: 6
        ahmet set icerisinde mevcut 3 tane var
        fatma set icerisinde mevcut
        fatma set icerisinde mevcut degil
        */
    }


    {
        std::set<int> myset{ 1, 2, 3, 4, 5 };
        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n";

        auto iter = myset.find(3);
        auto handle = myset.extract(iter);

        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n";

        handle.value() = 9;
        myset.insert(std::move(handle));

        for (auto iter = myset.begin(); iter != myset.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << "\n";


        /*
        OUTPUT
        ------
        1 2 3 4 5 
        1 2 4 5 
        1 2 4 5 9 
        */

    }
}