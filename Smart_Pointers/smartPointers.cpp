/*
Smart Pointers
===============

Smart pointer, pointer olmamaasına rağmen bir pointer interface'ine sahip (pointerlike) sınıflardan birisidir.
Smart pointer terimi tüm pointerlike sınıf değil bir kaynağın veya dinamik ömürlü nesnenin yaşam döngüsünü kontrol eden pointerlike sınıflar için kullanılır.
İki tane önemli smart pointer sınıfı bulunmakta bunlar
1. unique_ptr
2. shared_ptr

bunun haricinde weak_ptr sınıfı bulunmakta. weak_ptr tam olarak smart pointer değil ancak shared_ptr sınıfı kullanımında yardımcı olabilecek bir sınıftır.

Raw Pointer'a göre Avanrajları
------------------------------
- Exception handling konusunda avantajları var
- Resource leak hatalarının önüne geçiyor
- Double deletion önüne geçiyor
- Dangling pointer önüne geçiyor

Raw Pointer'a göre Dezavantajları
-----------------------------
- Performans konusunda shared_ptr daha dezavantajlı olabiliyor. Ancak unique_ptr için runtime'da ilave bir maliyet yok.


Kullanım alanları
-------------------
1.) Container içerisinde dinamik ömürlü nesne tutmak için kullanılabilir. Smart pointerlar yerine raw pointerlar tercih edilirse containerlardan silme veya containerların hayatının sonlanma durumunda tutulan ögelerin destrcutorları çağrılmadığı için resource leak olur.
2.) Dinamik ömürlü bir nesne döndüren factory fonksiyon raw pointer döndürürse, oluşturulan nesnenin hayatı sonlandırma sorumluluğu client code'a geçer. Ancak raw pointer yerine smart pointer kullanılırsa delete etme sorumluluğu factory fonksiyonda kalır.


auto_ptr
----------
günümüzdeki unique_ptr sınıfının eski C++ da karşılığı ancak. Günüzmüzdeki C++ da taşıma semantiği, perfect forwarding gibi araçlar eski C++ da olmadığı için problemli bir araçtı. C++11 ile deprecate edildi ve ardından kaldırıldı.

unique_ptr
----------
Bir kaynağı gösteren tek pointerdır. Bu pointer'ın hayatı bittiği zaman gösterdiği nesne delete edilir. Kopyalanamaz.
Exculusive ownership stratejisi: bir kaynağın tek sahibi olması. Kaynağı başkası kullanacaksa o kaynağın sahibi kaynağı bırakacak ve alacak yeni sahip kaynağı sahiplenecek.

template< class T,class Deleter = std::default_delete<T>>
class unique_ptr;

unique_ptr destructor içinde deleter çağrılıyor. standard kütüphane deleter içinde delete çağrıyor.

new ile hayata gelmiş dinamik ömürlü bir nesneyi gösteriyorsa default deleter kullanılması gerekiyor. Çünkü custom deleter kullanınca da aynı işlem yapılacak.

unique_ptr ile raw pointer sizeof değerleri aynıdır.

Bir sıfının üye elemanı unique_ptr olması durumunda, derleyicinin yazacağı copy assigment ve copy ctor delete edilecektir. Bunun sebebi unique_ptr lemanın kopyalama işlemlerine kapalı olmasıdır.

Deleter
=======
unique_ptr destructoru deleter olarak girilen template parametresini çağrıyor. Bu parametre default olarak delete fonksiyonudur.
Deleter olarak geçilecek parametre herhangi bir callable olabilir.
deleter delete fonksiyonu çağılmaması istenilen durumlarda, c apilerini sarmalamada ve farklı bir delete çağırma işlemlerinde kullanılabilir.


shared_ptr
-----------
Paylaşımlı sahipliğe izin veriyor. Kopyalanabilir. Kaynağı gösteren tüm pointerlerın hayatı bittiği zaman kaynak delete edilir.
Shared ownership stratejisi: bir kaynağın birden fazla sahibi olabilir.
Shared_ptr bir unique_ptr ile construct edilebilir.

template< class T > class shared_ptr;

shared_ptr template içerisinde deleter parametresi yok. Sharedptr custom deleter gerekirse ctor içerisinde ikinci parametre olarak gönderilebiliyor.

boş smart pointerlar dereference edilirse (*) nullptr'de olduğu gibi undefined behaviour olur. Exception throw etmez.

shared_ptr size_of değeri , raw pointer size of değerine göre daha fazladır. çünkü pointerı sarmalamanın yanı sıra reference counting yaptığı control block alanını da allocate etmesi gerekir.

weak_ptr
--------
weak_ptr bir shared_ptr'nin kaynağı sahip olup olmadığını gözlemlemek için kullanılıyor.
weak_ptr shared_ptr'nin gösterdiği nesnenin gözlemcisi olarak kullanılabiliyor. Ancak referans sayacı artmıyor. weak_ptr dereference edilemiyor.
bir weak_ptr, shared_ptr'den oluşturuluyor.
weak_ptr'nin en çok kullanıldığı yer cyclic refernas engellemeleridir. 

make fonksiyonları
-------------------
make unique ve make shared fonksiyon şablonları factory fonksiyonlarıdır. Template içerisinde tanımlanan nesneler için dinamik nesneler üretir.
Girilen variadic parametre paketini perfect forwarding ile şablona girilen tip için new ifadesi ile constructor çağrır.

template< class T, class... Args >
unique_ptr<T> make_unique( Args&&... args )
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}


template< class T, class... Args >
shared_ptr<T> make_shared( Args&&... args )
{
    return shared_ptr<T>(new T(std::forwards<Args>(args)...));
}

Smart pointer nesnelerinde bir kaynağı göstermenin en pratik yolu make fonksiyonları çağırmak.
make fonksiyonlarında template argümanı sadece dönüşte olduğu için deduction şansı yok.


Fonksiyonlar
============

Reset
-------
reset sarmalanan pointera yeni nesnenin adresini atıyor. Yani pointerın değerini değiştiriyor.
Eğer reset'e argüman verilmeden çağrılırsa nullptr atanıyor.
unique_ptr için reset() veya uptr = nullptr veya uptr = {} yazılırsa unique_ptr içindeki nesnenin hayatı sonlanır ve pointer boşa çıkar.
shared_ptr için reset() veya sptr = nullptr veya sptr = {} yazılırsa shared_ptr kaynağı göstermeyi bırakır. Eğer son kaynağı gösteren shared_ptr ise kaynak hayatı sonlandırılır.

Release
---------
release fonksiyonu smart pointer'ın sahipliğini sonlandırıyor ve tuttuğu nesnenin adresini döndürüyor.
release fonksyonu tuttuğu nesnenin adresini döndürüyor ve kendi içinde sarmaladığı pointerı'ı nullptr yapıyor.
Release edilen nesnnin hayatını bitirmek yazılımcının sorumluluğunda olur.

Get
---
get fonksiyonu tutuğu objenin sahipliğini bırakmıyor ancak objenin adresini döndürüyor.


Use_Count
---------
Sadece shared_ptr ve weak_ptr içinde var. Kaynağı kaç tane shared_ptr'nin gösterdiğinin sayısını döndürür

lock
----
sadece wak_ptr'de var geri dönüş değeri shared_ptr. Bu shared_ptr nullptr değerinde ise kaynak geri verilmiş demektir. Eğer nullptr değilse o kaynağa bir shared_ptr daha atanır.

expired
-------
sadece weak_ptr'de var. dönüş değeri bool. Eğer true ise izlenen shared_ptr kaynağı geri verildi (expired) anlamına gelir.

+--------------------+----------------------+--------------------------------------------------------------------------------+
| Smart Pointer Type | Functions            | Explanation                                                                   |
+====================+======================+================================================================================+
| std::unique_ptr    | get()                | Returns a pointer to the managed object                                          |
|                    | reset()              | Resets the unique_ptr to manage a new object                                     |
|                    | release()            | Releases ownership of the managed object and returns a pointer to it            |
|                    | operator*()          | Dereferences the managed object                                                  |
|                    | operator->()         | Accesses a member of the managed object                                           |
|                    | operator bool()      | Checks if the unique_ptr is managing an object                                    |
+--------------------+----------------------+--------------------------------------------------------------------------------+
| std::shared_ptr    | get()                | Returns a pointer to the managed object                                          |
|                    | reset()              | Resets the shared_ptr to manage a new object                                     |
|                    | use_count()          | Returns the number of shared_ptrs that share ownership of the managed object     |
|                    | operator*()          | Dereferences the managed object                                                  |
|                    | operator->()         | Accesses a member of the managed object                                           |
|                    | operator bool()      | Checks if the shared_ptr is managing an object                                    |
+--------------------+----------------------+--------------------------------------------------------------------------------+
| std::weak_ptr      | expired()            | Checks if the weak_ptr's underlying shared_ptr has expired                       |
|                    | lock()               | Returns a shared_ptr that shares ownership with the weak_ptr or an empty shared_ptr if the underlying shared_ptr has expired |
|                    | use_count()          | Returns the number of shared_ptrs that share ownership of the managed object     |
|                    | operator bool()      | Checks if the weak_ptr's underlying shared_ptr is valid                           |
+--------------------+----------------------+--------------------------------------------------------------------------------+
| std::auto_ptr      | get()                | Returns a pointer to the managed object                                          |
|                    | reset()              | Resets the auto_ptr to manage a new object                                       |
|                    | release()            | Releases ownership of the managed object and returns a pointer to it            |
|                    | operator*()          | Dereferences the managed object                                                  |
|                    | operator->()         | Accesses a member of the managed object                                           |
|                    | operator bool()      | Checks if the auto_ptr is managing an object                                      |
+--------------------+----------------------+--------------------------------------------------------------------------------+

*/

#include<iostream>
#include<memory>


class CustomDeleter
{
public:
    void operator()(const std::string* p)
    {
        std::cout << "Adress: " << p << " Custom deleter\n";
        delete p;
    }

};

class Myclass
{
public:
    Myclass()
    {
        std::cout << "Myclass ctor\n";
    };
    ~Myclass()
    {
        std::cout << "Myclass destrutor\n";
    };
    int data;
};

int main()
{
    std::unique_ptr<Myclass> uptr1; //nullptr
    std::unique_ptr<Myclass> uptr2{}; //nullptr

    if (!uptr1 && !uptr2) //==nullptr
        std::cout << "uptr1 and uptr2 is nullptr\n";
    //uptr1 and uptr2 is nullptr
    {
        std::unique_ptr<Myclass> uptr3{new Myclass};
        uptr3->data = 5;
        (*uptr3).data = 15;
        //uptr1 = uptr3; //error: object of type 'std::unique_ptr<Myclass>' cannot be assigned because its copy assignment operator is implicitly deleted
    }
    std::cout << "Main devam ediyor\n";
    /*
    OUTPUT
    ------
    Myclass ctor
    Myclass destrutor
    Main devam ediyor
    */

    /*
    Myclass myclass;
    std::unique_ptr<Myclass> uptr4{&myclass}; //undefine behaviour delete çağrılacak ancak dinamik nesne değil

    Myclass* dmyclass = new Myclass();

    std::unique_ptr<Myclass> uptr5{dmyclass};
    std::unique_ptr<Myclass> uptr6{dmyclass};
    //Undefined behaviour: nesnelerden birisinin hayatı bittiği zaman diğeri dangling pointer oluyor.
    */

    std::unique_ptr<Myclass> uptr7 = std::make_unique<Myclass>();

    std::unique_ptr<Myclass> uptr8;

    // uptr8 = new Myclass(); sentaks hatası 

    uptr8.reset(new Myclass());
    uptr8.reset(); //uptr8 = nullptr;
    /*
    OUTPUT
    ------
    Myclass ctor
    Myclass destrutor

    */
    std::cout << std::endl;

    {
        std::unique_ptr<std::string, CustomDeleter> uptr{new std::string("Test")};
        //Adress: 0x1004040a0 Custom deleter
    }

    {

        auto customDeleter2 = [](const std::string* p) {
            std::cout << "Address: " << p << " custom deleter 2\n";
            delete p;
        };
        std::unique_ptr<std::string, decltype(customDeleter2)> uptr{new std::string("Test2")};
        //Address: 0x100304110 custom deleter 2

    }


    {

        std::shared_ptr<Myclass> sp1 = std::make_shared<Myclass>();
        std::cout << "sp1.use_count(): " << sp1.use_count() << "\n";
        std::shared_ptr<Myclass> sp2 = sp1;
        std::cout << "sp1.use_count(): " << sp1.use_count() << "\n";
        std::shared_ptr<Myclass> sp3 = sp2;
        std::cout << "sp1.use_count(): " << sp1.use_count() << "\n";
        /*
        Output
        ------
        Myclass ctor
        sp1.use_count(): 1
        sp1.use_count(): 2
        sp1.use_count(): 3
        Myclass destrutor
        */

        auto customDeleter2 = [](const std::string* p) {
            std::cout << "Address: " << p << " custom deleter 2\n";
            delete p;
        };
        std::shared_ptr<std::string>{new std::string("Test2"), customDeleter2};
        //Address: 0x1003040c0 custom deleter 2
    }

    {
        std::shared_ptr<Myclass> sp = std::make_shared<Myclass>();
        std::weak_ptr<Myclass> wp(sp);

        if (wp.expired())
        {
            std::cout << "Shared_ptr expired\n";
        }

        sp.reset();

        if (wp.expired())
        {
            std::cout << "Shared_ptr expired\n";
        }

        /*
        OUTPUT
        ------
        Myclass ctor
        Myclass destrutor
        Shared_ptr expired
        */

    }

    {
        std::shared_ptr<Myclass> sp = std::make_shared<Myclass>();
        std::weak_ptr<Myclass> wp(sp);

        if (std::shared_ptr<Myclass> sp2 = wp.lock())
        {
            //sp2 burada shared pointer olarak kullanılabilir.
        }
        else
        {
            std::cout << "Shared_ptr expired\n";

        }

        sp.reset();

        if (std::shared_ptr<Myclass>  sp2 = wp.lock())
        {

        }
        else
        {
            std::cout << "Shared_ptr expired\n";

        }

        /*
        OUTPUT
        ------
        Myclass ctor
        Myclass destrutor
        Shared_ptr expired
        */

    }

}