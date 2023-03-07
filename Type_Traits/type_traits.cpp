/*

https://en.cppreference.com/w/cpp/header/type_traits
https://github.com/necatiergin/cpp-kursu-kodlar/tree/main/0774_SFINAE

TYPE TRAITS
============
compile time içerisinde türler hakkında bilgi edinme işlemi.
Bu işlemin amacı belirli türlerin belirli template'ler ile kullanılması veya farklı türler için farklı kodların compile time'da belirlenmesi için kullanılıyor.
Bu bilgiler, girilen türün bir tam sayı türü olup olmadığı, bir pointer, referans olup olmadığı veya bir öğeye sahip olaup olmadıgi şeklinde olabilir.
Bu bilgiyi almak için type_traits kütüphanesi kullanılıyor.
type_traits sınıfında tüm sınıflar için taban oluşturacak integral_constant sınıfı bulunmakta
integral_constant sınıf şablonun ilk parametresi tür, ikinci parametresi ise bir sabit ifadesidir. Bu değer ikinci parametreye göre bir value verir
integral_constant<int,5::value = 5 sabiti.
integral_constant<bool,true::value = true sabiti.
integral_constant<bool,true::type = integral_constant<bool,true> oluyor.
integral_constant<bool,true::value_type = bool

bunun haricinde operator value_type()() fonksiyonu var. Bu bilinen tür değişim operatörü fonksiyonu.

TAG DISPATCH
------------
Bir template için belirli gruptaki türlere göre compile time içerisinde farklı kodların çalışmasını sağlama yöntemlerinden bir tanesi,
implemeantasyon fonksiyon içerisine fonksiyon parametreleri hariç type_traits objesi (false_type veya true_type) gönderilir.
type_traits içerisinde is_* fonksiyonları ile istenilen tür grubu true_type veya false_type olarak gönderilir.



Fonksiyon İsmi	                        Açıklama
---------------                         ---------
std::is_void	                Void türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_null_pointer	        Null pointer türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_integral	            Tamsayı (int, char, short, vb.) türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_floating_point	        Ondalık sayı (float, double, vb.) türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_array	                Dizi türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_pointer	                İşaretçi türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_lvalue_reference	    Lvalue referansı türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_rvalue_reference	    Rvalue referansı türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_member_object_pointer	Sınıfın veri elemanı işaretçisi türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_member_function_pointer	Sınıfın işlevi işaretçisi türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_enum	                Enum türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_union	                Birleşim türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_class	                Sınıf türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_function	            İşlev türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_reference	            Referans türü ise true_type'ı, değilse false_type'ı döndürür.
std::is_arithmetic	            Aritmetik türü (tamsayı veya ondalık sayı) ise true_type'ı, değilse false_type'ı döndürür.
std::is_fundamental	            Fundemantal türü (tamsayı, ondalık sayı, void ve null pointer) ise true_type'ı, değilse false_type'ı döndürür.
std::is_object	                Nesne türü (herhangi bir tür için) ise true_type'ı, değilse `false


std::is_same
------------
İki türün aynı tür olup olmadığı bilgisini verir.


template<class T, class U>
struct is_same : std::false_type {};

template<class T>
struct is_same<T, T> : std::true_type {};


std::remove_reference
---------------------
Compile time içerisinde T& veya T&& olan türleri T'ye dönüştürür.

template< class T >
using remove_reference_t = typename remove_reference<T>::type;

template< class T > struct remove_reference      { typedef T type; };
template< class T > struct remove_reference<T&>  { typedef T type; };
template< class T > struct remove_reference<T&&> { typedef T type; };
  
std::type_identity (C++ 20)
-------------------
templateler içerisinde girilen type için type transformation sağlar

template <class T>
T foo(T a, T b) {
  return a + b;
}
 
template <class T>
T bar(T a, std::type_identity_t<T> b) {
  return a + b;
}
 
int main() {
  // foo(4.2, 1); // error, deduced conflicting types for 'T'
  std::cout << bar(4.2, 1) << '\n';  // OK, calls bar<double>
}


Template Meta Programing Türe göre Kod Seçimi
----------------------------------------------
1.) TAG Dispatch
2.) constexpr if (static if)
3.) sfinae
4.) static_assert
5.)concept (C++20)

TAG_DISPATCH
------------
Kullanılan fonksiyona ekstra type_traits obje gönderilerek tür belirleme işlemi

STATIC_ASSERT
-------------
Asertion         : Programın derleme veya çalışma zamanında bir durumun programlama hatalarının bulunması için doğrulama.
Dynamic Asertion : Programın çalışma zamanında yapılan doğrulama.
Static Asertion  : Programın derleme zamanında yapılan doğrulama. Bir takım parametreler doğru değilse doğrulama işlemi hiç yapılmasın

static_asser C++11 ile gelen bir keyword. Dolayısıyla kullanmak için herhangi bir header dosyası include etmek gerekmiyor.

static_assert ( bool-constexpr , message )	

static_assert(03301 == 1729); // since C++17 the message string is optional
 
template <class T>
void swap(T& a, T& b) noexcept
{
    static_assert(std::is_copy_constructible_v<T>,"Swap requires copying");
    static_assert(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_assignable_v<T> "Swap requires nothrow copy/assign");
    auto c = b;
    b = a;
    a = c;
}
 
template <class T>
struct data_structure {
    static_assert(std::is_default_constructible_v<T>,"Data structure requires default-constructible elements");
};


constexpr if (static if)(C++ 17)
---------------------------------
Normal if içinde koşul compile time'da değil runtime'da kontrol ediliyor. 
template<typename T>
void foo(T x)
{
    if constexpr (std::is_pointer_v<T>)
    {
        std::cout<<"pointer type\n";
    }
    else
    {
        std::cout<<"not pointer type"; 

    }
}

compile time zamanında koşul kontrol edildiği için doğru durumda doğru kısımda kod derlenir yanlış ise yanlış kısımda kod derleniyor. 
diğer kısımdaki kod hiç derlenmiyor dolayısıyla tür için yanlışlık varsa derleyici herhangi bir hata vermiyor. 


SFINAE (Substitution failure is not an error)
---------------------------------------------
Substitution: Template argümanları fonksiyonların yerine sağlanma aşaması. 
Substitution aşamsında türlere yönelik olan error hard error şeklinde derleme bitiren error olmamaktadır. Derleyici o fonksiyonu overloadların set içerisinden çıkartılabilir. . 
Bu overloading set içerisinden çıkarma işlemi türe göre compile zamanda kod seçme işlemi yapılabilir. 



template<typename T, unsigned N>
std::size_t len(T(&)[N])
{
	return N; //size_type nested type sahip olmayan kodlar için bu alan seçildi
}

template<typename T>
typename T::size_type len(T const& t)
{
	return t.size(); //size_type nested type sahip olan kodlar için bu alan seçildi
}


enable_if sfinae ile çok kullanılıyor. 

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

enable_if'in ilk argümanı ture olursa ::type isimli nested memberı var. Bu type ise girilen ikinci template parametresi oluyor. 

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> func(T t) 
{
    std::cout << "func<integral T> " << '\n';
    return t;
}

+------------------------+-------------------------------------------------------------+----------------------------------------------------+
| Fonksiyon              | Açıklama                                                    | Örnek                                              |
+------------------------+-------------------------------------------------------------+----------------------------------------------------+
| if constexpr           | Koşulun doğru ya da yanlış olmasına bağlı olarak            | if constexpr(std::is_same_v<T, int>, [](auto x)    |
|                        | derleme zamanında belirli kod bloklarını seçer.             | {return x + 1;}, [](auto x) {return x;});          |
|                        | Eğer koşul doğru ise ilk lambda ifadesi çalıştırılır,       |                                                    |
|                        | aksi halde ikinci lambda ifadesi çalıştırılır.              |                                                    |
+------------------------+-------------------------------------------------------------+----------------------------------------------------+
| static_assert          | Derleme zamanında koşulu kontrol eder ve hata mesajı        | static_assert(std::is_integral_v<T>, "T is not     |
|                        | verir.                                                      | an integral type");                                |
|                        |                                                             |                                                    |
|                        | Örnek olarak, bir tamsayı tipi gerektiren bir şablonu       |                                                    |
|                        | özelleştirmeden önce bir statik_assert kullanabilirsiniz.   |                                                    |
+------------------------+-------------------------------------------------------------+----------------------------------------------------+
| enable_if              | Şablonların belirli koşullar sağlandığında kullanılması     | template <typename T, typename = std::enable_if_t< |
|                        | için kullanılan bir tür özelliğidir.                        | std::is_floating_point_v<T>>>                      |
|                        | Örneğin, yalnızca kayan nokta türleri için bir şablonu      | void foo(T t) {}                                   |
|                        | kullanmak istiyorsanız, enable_if kullanabilirsiniz.        |                                                    |
+------------------------+-------------------------------------------------------------+----------------------------------------------------+
| type_traits            | Tipler hakkında bilgi sağlamak için kullanılan bir başlık   | std::is_integral<int>::value;                      |
|                        | dosyasıdır.                                                 |                                                    |
|                        | Bu başlık dosyası, türlerin özelliklerine göre bilgi        | std::is_floating_point<double>::value;             |
|                        | sağlar. Örneğin, bir tamsayı veya kayan nokta tipi mi       |                                                    |
|                        | olduğunu öğrenmek için kullanılabilir.                      | std::is_same<int, double>::value;                  |
+------------------------+-------------------------------------------------------------+----------------------------------------------------+
| constexpr              | Bir ifade veya işlevin derleme zamanında değerini           | constexpr int factorial(int n) {return n == 0 ?    |
|                        | hesaplamak için kullanılan bir anahtar sözcüğüdür.          | 1 : n * factorial(n - 1);}                         |
|                        | Derleyici, sabit ifadeleri derleme zamanında                |                                                    |
|                        | değerlendirir ve kodun çalışma zamanında çalışmasına        |                                                    |
|                        | gerek kalmadan hesaplanmasına olanak tanır.                 |                                                    |
+------------------------+-------------------------------------------------------------+----------------------------------------------------+




*/

#include<iostream>
#include<type_traits>

template<typename T>
void func_impl(T x, std::true_type)
{
    std::cout << "TAG Dispatch pointer turleri icin implementasyon\n";
}

template<typename T>
void func_impl(T x, std::false_type)
{
    std::cout << "TAG Dispatch pointer olmayan turler icin implementasyon\n";

}


template<typename T>
void func(T x)
{
    func_impl(x, typename std::is_pointer<T>::type());
}

int main()
{
    func(12);
    int* a;
    func(a);
    /*
    OUTPUT
    -----
    TAG Dispatch pointer olmayan turler icin implementasyon
    TAG Dispatch pointer turleri icin implementasyon
    */

    std::cout << std::is_same<char, char>::value << ' ';
    std::cout << std::is_same<char, unsigned char>::value << ' ';
    std::cout << std::is_same<char, signed char>::value << ' ';
    std::cout << std::is_same<char, volatile char>::value << ' ';
    std::cout << std::is_same<char, const char>::value << '\n';
    //1 0 0 0 0


    std::cout << std::is_same_v<char, char> << ' ';
    std::cout << std::is_same_v<char, unsigned char> << ' ';
    std::cout << std::is_same_v<char, signed char> << ' ';
    std::cout << std::is_same_v<char, volatile char> << ' ';
    std::cout << std::is_same_v<char, const char> << '\n';
    //1 0 0 0 0


    std::cout << "std::remove_reference<int>::type is int? " << std::is_same<int, std::remove_reference<int>::type>::value << '\n';
    std::cout << "std::remove_reference<int&>::type is int? " << std::is_same<int, std::remove_reference<int&>::type>::value << '\n';
    std::cout << "std::remove_reference<int&&>::type is int? " << std::is_same<int, std::remove_reference<int&&>::type>::value << '\n';
    std::cout << "std::remove_reference<const int&>::type is const int? " << std::is_same<const int, std::remove_reference<const int&>::type>::value << '\n';
    /*
    OUTPUT
    -----
    std::remove_reference<int>::type is int? 1
    std::remove_reference<int&>::type is int? 1
    std::remove_reference<int&&>::type is int? 1
    std::remove_reference<const int&>::type is const int? 1
    */

}