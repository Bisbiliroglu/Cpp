/*
https://en.cppreference.com/w/cpp/header/functional
https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

FUNCTIONAL
-----------

Function object sınıflaır () operatörlerini overload eden sınıflardır. Bu sınıflar genelde algoritmalara argüman olarak geçilirken veya template parametrelere default argüman olarak geçilirken kullanılmaktadır.

plus<int>{} (10,20) çağrılan fonksiyon 10 ve 20'yi toplayarak geri döndürecek

std::reference_wrapper
------------------
rebindable : başka bir nesneye bağlanabilir
Elemanları referans olan bir dizi veya template argümanı reference olan bir obje oluşturulamaz.
ref fonksiyon şablonu ile reference wrapper cinsinden nesne döndürür.
cref fonksiyonu ile reference wrapper cinsiden const nesne döndürür.
yüksek boyutlu nesnelerin fonksiyona argüman olarak geçilirken kopyalanmasının önüne geçmek için ref fonksiyonu ile reference_wrapper'a çevrilebilir.
copy ctor'u olmayan nesneleri fonksiyona argüman olarak geçilirken kopyalanabilmesi için ref fonksiyonu ile reference_wrapper'a çevrilebilir.

std::bind
-----
bir fonksiyonun interface'ini değiştirmek için kullanılabiliyor. Burada birden fazla parametre olan fonksiyona default argüman atamak, argüman sırası değiştirmek gibi işlemler yapılabilir.
bind bir callable object döndürüyor. parametre olarak bir callable ve bu callable'a parametre olarak girilecek argümanları alır. Bu argüman sayısı fonksiyonun argüman sayısı ile aynı olmalıdır.
Argman yerina std::placeholders::_1 veya std::placeholders::_2 gibi placeholderslar girilirse bu girilen placeholders için oluşturulan callable nesneye argüman geçilmesi gerekir.
bind kendi içinde gönderilen argümanlar için kopyalama semantiği kulanır. reference semantiği kullanmak için  argümanların reference_wrapper ile sarmalanarak gönderilmesi gerekir.

std::function
--------------
fonksiyon sarmalamak için  kulanılıyor
fonksiyon türü int(int)
fonksiyon adresi türü int(*)(int)
std::function callable sarmalamaya yarayan sınıf şablonu.
hem fonksiyonlara parametre olark hem geri dönüş değeri olarak kullanılabilir.
containerlar içerisinde ulanılabilir.
std::function nesneleri default initialize edilebiliyor. Ancak bu durumda herhangi bir fonkisyon sarmalamıyor.
std::function nesnesinin bir şeyi sarmalayıp sarmalamadığını test etmek istenirise oeprator bool fonksiyonu kullanılabilir.
std::function nesnesi boş ise fonksiyon çağrı operatörünün operandı yapılırsa exception throw eder.

std::not_fn
-----------
Bir fonksiyon adaptörüdür. Bu fonksiyona bir callable gönderilirse bind gibi bir callable döndürür. 
Arka planda kendisine argüman olarak gönderilen fonksiyonu çağrıyor ancak logic olarak tersini döndürüyor. 
En çok kullanılan kısımlar algoritmalara argüman olarak gönderilen predicate bölümü. 

std::mem_fn
------------
Bir fonksiyon adaptörüdür. Bu fonksiyona bir callable gönderilirse bind gibi bir callable döndürür. 
Ancak argüman olarak aldığı callable bir sınıfın non-static üye fonksiyonunun adresidir. Buna göre bir funcion object döndürür. 
std::mem_fn fonksiyonundan dönen callable'a bir sınıf nesnesi veya sınıf pointer'ı göndermek gerekiyor.

std::invoke 
------------
CPP 17 ile eklendi. General bir callable invoker. Callable ve argümanları girilirse girilen callab eincoke eder. 
Bir fonksiyon şablonu. İlk parametre olarak callable alır. Diğer parametreler ise peerfect forwarding ile fonksiyona geçilecek parametrelerdir. 
Dönüş değeri argüman olarak geçilen fonksiyonun dönüş değeridir. 
Eğer bir sınıfın üye fonksiyonu invoke edilecekse, invoke fonksiyonuna, callable'den sonra sınıf argüman olarak geçilmesi gerekmektedir. 


*/

#include<functional>
#include<iostream>
#include <vector>
int foo(int x)
{
    std::cout << "foo(int x ) x = " << x << "\n";
    return x * x;
}

int bar(int y)
{
    std::cout << "bar(int x ) x = " << y << "\n";
    return y * y * y;

}
int baz(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 5;
    int b = 7;
    std::reference_wrapper<int> iref = a;
    std::cout << "a: " << a << " b: " << b << " iref: " << iref << "\n";
    iref *= 2;
    std::cout << "a: " << a << " b: " << b << " iref: " << iref << "\n";
    iref = b; //rebind
    std::cout << "a: " << a << " b: " << b << " iref: " << iref << "\n";
    iref.get() = 99;
    std::cout << "a: " << a << " b: " << b << " iref: " << iref << "\n";


    /*
    OUTPUT
    ------
    a: 5 b: 7 iref: 5
    a: 10 b: 7 iref: 10
    a: 10 b: 7 iref: 7
    a: 10 b: 99 iref: 99
    */


    std::vector<std::reference_wrapper<int> > ivecref;
    ivecref.push_back(a);
    ivecref.push_back(b);

    for (auto i : ivecref)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    //10 99 


    std::reference_wrapper rf = foo;

    auto val1 = rf(5);

    rf = bar;

    auto val2 = rf(5);

    std::cout << "val1: " << val1 << " val2: " << val2 << "\n";
    /*
    OUTPUT
    ------
    foo(int x ) x = 5
    bar(int x ) x = 5
    val1: 25 val2: 125
    */

    auto bfoo1 = std::bind(foo, 10);
    std::cout << "bfoo1: " << bfoo1() << "\n"; //100

    auto bbaz1 = std::bind(baz, 5, std::placeholders::_1); //binden alınacak callable baz( argüman, 5) olacak yani ikinc argümanı hep 5 olacak
    /*
    std::placeholders::_1 ilk argüman
    std::placeholders::_2 ikinci argüman
    _1 ikinci parametre olarak gidildiği için oluşturulan bbaz1 in 2. parametresi 1e yazılmış oldu. Yani baz(60,5) çağrıldı
    */
    std::cout << "bbaz1: " << bbaz1(60) << "\n"; //baz(60,5) = 65

    auto bbaz2 = std::bind(baz, std::placeholders::_1, std::placeholders::_1);
    std::cout << "bbaz2: " << bbaz2(60) << "\n"; //baz(60,60) = 120


    std::function<int(int)> f;
    if (f)
    {
        std::cout << "dolu\n";
    }
    else
    {
        std::cout << "bos\n";
    }
    f = foo;
    if (f)
    {
        std::cout << "dolu\n";
    }
    else
    {
        std::cout << "bos\n";
    }
    f(25);
    f = [](int a) {return a;};
    f(26);
    std::vector<std::function<int(int)>> fvec;
    /* 
    OUTPUT 
    ------
    bos
    dolu
    foo(int x ) x = 25
    */


}