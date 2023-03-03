/*
Dinamik Ömürlü Nesneler
=======================

Dinamik ömrülü nesneler, geliştirici ne zaman isterse hayatı başlar, ne zaman isterse hayatı biter.
Statik ömürlü nesneler programın başında ömrü başlar, program sonlanınca ömrü sonlanır.
Otomatik ömürlü nesne ise kendi scope'u içindde tanımlanınca hayata gelir, scope bitince ömrü biter
Thread local nesneler ise bir threadin statik ömürlü değişkeni olarak düşünülebilir.


Dinamik ömrülü nesnelerin bellek alanı programın çalışma zamanında ayrılıyor. Hatta dinamik ömürlü nesnelerin tipleri de çalışma zamanı belli oluyor.

Dinamik ömürlü nesnelerin hayatını başlatmak için new operatörleri, sonlandırmak için delete operatörleri kullanılıyor.

Not: Java C# gibi dillerde tüm nesneler dinamik olduğu için obje tanımlarken hep new kullanılır. ancak C++ için böyle bir zorunluluk yoktur.

Sentaks
-------
new T
delete T

new operatörü kullanıldığı zaman operator new(sizeof(T)) fonksiyonu çağrılır. Bu fonksiyon sizeof(T) kadar bellekte yer ayıracak (malloc eşdeğeri), eğer edemezse exception throw (bad alloc) edecek.
Eğer exception throw edilmezse operatör new fonksiyonun geri döndürdüğü adresi this* olarak derleyici kullanacak ve ilgili nesne için ctor çağıracak.

Dinamik ömrülü nesnelerin işi bittiği zaman delete operatörü ile nesneler delete edilmelidir. Bu sayede kullanılan nesnelerin destructorları çağrılır ve bellek alanı boşaltılır.

operator new ve operator delete fonksiyonları overload edilirse tüm new ve delete için overload edilmiş fonksiyonlar çağrılacak
Ancak bir sınıf için new ve delete fonksiyonları overload edilirse sadece o sınıf için new ve delete ifadeleri değişmiş olur.
Bir sınıf için new ve delete fonksiyonları overload edilirse static yapılması gerekmektedir. Zaten static keyword'u kullanılmasa dahi otomatik olarak bu fonksiyonlar statik olacaktır.

new ile allocation sürecinde bellek alanı alınmazsa hemen exception throw edilmez. new_handler fonksiyonunun sürekli çağrıldığı bir sonsuz döngüye girilir.
Bunun amacı bu işlem sırasında programda farklı bir bellek alanı boşa çıkarsa o bellek alanını allocate etmketir.
set_new_handler fonksiyonu ile new handler farklı bir function pointer ile custimize edilebilir.
get_new_handler fonksiyonu ile new_handler fonksiyonun adresi alınabilir. Adres program başlangıcında nullptr dir

Array new
---------
new T[n]  boyutunda dinamik ömürlü dizi oluşturuyor.
delete[]  dinamik ömürlü diziyi siler.

Placement new
--------------
Çağrılacak operatör new fonksiyonuna ileva argüman ya da argümanlar gönderliyor.
new (arg) T

void * operator new (void * vptr, size_tn)

bu fonksiyon overload edilemiyor ve girilen adresi döndürür.
Bu işlem ile bir nesne istenilen adreste oluşturulabiliyor.

bu işlemde delete çağrılırsa ubdefined behaviour oluşur. Bunun sebebi alınmış olan alanın free edilmesidir. Bu nedenle destructor ismiyle çağrılır.

nothrow new
------------
new işlemi başarısz olursa exception throw etmiyor ancak nullptr döndürüyor.

new (nothrow) T


*/

#include <iostream>

class Myclass
{
    uint64_t a = 5;
};


class MyCustomClass {
public:
    MyCustomClass()
    {
        std::cout << "MyCustomClass ctor\n";
    }

    ~MyCustomClass()
    {
        std::cout << "MyCustomClass destructor\n";
    }

    uint64_t a = 5;

    void* operator new (std::size_t n)
    {
        std::cout << "MyCustomClass: operator new allocate size : " << n << "\n";
        if (n == 0)
            ++n; // avoid std::malloc(0) which may return nullptr on success

        if (void* ptr = std::malloc(n))
            return ptr;

        throw std::bad_alloc{};
    }

    void operator delete (void* ptr)
    {
        std::cout << "MyCustomClass: operator delete ptr:" << ptr << "\n";
        std::free(ptr);
    }
};

int main()
{
    std::cout << "sizeof(Myclass) " << sizeof(Myclass) << "\n";

    Myclass* mc1 = new Myclass();

    const Myclass* mc2 = new const Myclass();

    std::cout << "sizeof(mc1) " << sizeof(mc1) << "\n";

    std::cout << "sizeof(mc2) " << sizeof(mc2) << "\n";


    delete mc1;
    //mc1->~Myclass()
    //operator delete(mc1)
    delete mc2;
    //mc2->~Myclass()
    //operator delete(mc2)

    /*
    OUTPUT
    -------
    sizeof(Myclass) 8
    sizeof(mc1) 8
    sizeof(mc2) 8
    */

    MyCustomClass* mcc = new MyCustomClass();
    std::cout << "mcc ptr: " << mcc << "\n";
    delete mcc;
    /*
    OUTPUT
    ------
    MyCustomClass: operator new allocate size : 8
    MyCustomClass ctor
    mcc ptr: 0x100204180
    MyCustomClass destructor
    MyCustomClass: operator delete ptr:0x100204180
    */


    auto* p = new MyCustomClass[10];
    delete[] p;
    /*
    OUTPUT
    ------
     10 x MyCustomClass ctor
     10 x MyCustomClass destructor
    */

    //placement new
    unsigned char buffer[sizeof(Myclass)];
    auto a = new (buffer) Myclass();
    //Buffer adresinde Myclass objesi yerleştirildi.ß
    a->~Myclass();
    //placement new için delete fonksiyonu çağrılmaz bu durumda buffer free olur ve undefined behoviour olur.


    auto b = new (std::nothrow) Myclass;

}