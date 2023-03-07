/*
Kaynakça
https://github.com/umutkotankiran/Cpp/blob/main/25_01_08_2021/main.cpp


Derleyicinin bizim yerimize kod yazmasını istersek templateler kullanırız.
Derleyiciye template ile bir şablon verilir ve bu şablonlar ile türden bağımsız şekilde kod yazılabilir.
Yani geliştirici proram yazarken template yazar ve derleyici bu templatei kullanarak gereken her örnek için kendi kodunu yazar ve kullanır.
Dolayısıyla template'ler çalışan kodun kendisi değildir. Derleyici templateler ile çalışan kodu yazarlar.
Türden bağımsız yazıldığı için algoritmalar daha üst düzey bir soyutlama yapılır. 
Örnek olarak iki int nesnenin swap edilmesi değil de iki nesnenin swap edilmesi gibi.
Programcı template yazdıktan sonra derleyici bu template'i kullanarak kendi gerçek kodu her örneği için compile time'da yazıyor. 
Bu işleme template instantiation denir. Yazılan her bir gerçek koda ise templatein o tür için template specialization'ı denir. 
C++ ın çok büyük kısmını STL oluşturuyor. STL açılımı Standard Template Library. 
string, vector veya unique_ptr sınıfı gibi bir çok sınıf template'dir ve derleyici, derleme zamanında kodları yazarlar. 


Temel Kategorilere ayrılıyor.
- Function Templates
- Class Templates
- Alias Template		C++11 ile geldi
- Variable Template		C++11 ile geldi
- Concept Template		C++20 ile geldi


int main()
{
	std::vector <int>x; 
}
Standart vector sınıfını kullanırken ismi vector olan sınıf şablonundan tür olarak int türünü
kullanması ve bizim için int türünden bir konteyner sınıfı yazmasını istiyoruz. 

FONKSIYON VE SINIF ŞABLONLARI
-----------------------------
Template kullanırken keyword olarak "template" ve hemen ardından  açısal parantez "<>"" kullanılır. 

Açısal parantez içindeki bildirimlere template parametreleri denir.
template <typename T >  veya template <class T >  

Template parametreleri,
	a - Type/Tür parametresi olabilir
		Bir isim kullanıyoruz ve bu bir türe karşılık geliyor.

            template <typename T >  veya template <class T >  
            template <typename T, typename U>

	
	b - non-type parameter olabilir.(sabit parametre)
        Bir isim kullanılıyor ve bu bir sabite karşılık geliyor.
            template <int x>
	
	c - template template parameter olabilir. 


TYPE PARAMETER
--------------

Tür parametresi, derleyiciye bir isim veriliyor ve bu isim int, double veya bir class ismi gibi bir türe karşılık geliyor.

Tür parametresi geçerken kullanılabilecek 2 adet keyword var.
1. class
2. typename

template <class T>   T ismi burada sınıf veya primitive bir türü temsil ediyor
Daha sonra eklenen ise typename keyword. Bu keywordun eklenme sebebi class çok uygun bir keyword olmadığı düşünüldüğü için.
Mesela T burada bir int veya pointer veya enum türü olabilir. Bunlar sınıf türü değil. Ama başında class var. Çok uygun bir keyword olmadığı için typename eklendi.


template <typename T>
template <class T>	

ikiside geçerli ve aynı. 

Tür parametresinin ne olduğunu derleyicisin bilmesi gerekiyor. Bu bilgiyi geliştirici açısaln parantez içinde yazarak kendi de verebilir veya tür çıkarım (deduction) mekanizması kullanılabilir.
	template <typename T>
	void func(T x);

    func<int>(10) şeklinde fonksiyon çağrılırsa bu explicit oluyor ve T int türden olduğu derleyiciye söylenmiş oluyor.
    func(3.4) olursa burada type deduction (tür çıkarım) mekanizması devreye giriyor ve T double oluyor.  



NON-TYPE PARAMETER
-------------------
Template'e bir sabit ifadesi vermek içink ullanılıyor. 
template <int x>	Burada x int türden sabit olmak üzere anlamına geliyor. 

int main()
{
	std::array<int, 2> ar;		arrayde ilk argüman tür argümanı ikincisi ise sabit parametreye karşılık gelen sabit argümanı.
}

array sınıf şablonu aağıdaki gibi.
template <typename T, size_t size> birincisi tür ikincisi boyut olarak kullanılacak
struct array{
};


Template specialization, template'den üretilen sınıfın adı.

Explicit Specializaiton
-------------------------
Explicit specialization, öyle bir kod ki belirli template argümanı ya da argümanları için derleyicinin bir specialization oluşturması yerine biim sağladığımız kodun (specialization) kullanılması talimatıdır.
Explicait specialization diğer adı full specialization.
Hem fonksiyon hem de sınıf şablonlarında kullanılabiliyor ancak daha çok sınıf şablonlarında kullanılıyor. 
Kullanım Amacı:
Oluşturulan template, bir çok tür için verilen şablona göre istenilen kodu döndürüyor ancak bazı türler için daha özelleştirilmiş bir çözüm isteniyorsa kullanılıyor.

template <typename t>
T getmax(T x, T y)
{
	return x>y?x:y;
}

int main()
{
	std::cout<<getmax(10,20);
	std::cout<<getmax(3.85, 4.2);
	std::cout<<getmax("abc","defg");
	std::cout<<getmax("defg","abc");

	OUTPUT
	--------
	20
	4.2
	abc
	defg

	son iki örnekte string literali const char * geliyor. 
	Dolayısıyla stringler değil adresler karşılaştırılmış oluyor ve yanlış sonuç ortaya çıkıyor.
}


Partial Specialization,
Explicit specialization'dan farklı olarak bir tür tipi için değil, belirli bir gruptaki tür tipleri için ayrı bir specialization partial specialization ile verilir.

Not: Function template ile partial specializationk kullanılamıyor sadece class template ile kullanılabiliyor.

SENTAKS
-------
template<typename T>
class MyClass{

}
template<typename T>
class MyClass<T*>{ // pointer türleri için bu specialization kullanılacak
	
}


DEFAULT TEMPLATE ARGUMENT
-------------------------
Template parametreleri için default argüman sağlanmasıdır. 
Eğer template argümanında explicit bir argüman kullanılmamışsa default olarak verilen argüman kullanılacak.


SENTAKS
-------
template <typename T = type>
void func(T)


default argument yerine başka bir türe air template parametresi kullnılabilir. 

template<typename = std::pair(int,double)

template<typnema T ,typename U=T>

STL container sınıfı templatelerin biri hariç hepsi default argüment alır.  

template<typename T typename A = std::allocator<T>>
class Vector
{
	...
}

Vector<int> vec;
Vector<int , std::allocator<int>> vec;

ikiside aynı

//allocator dinamik bellek ihtiyacını karşılamak ve yönetmek için kullanılan bir tür

templatelerde fonksiyonlarda olduğu gibi bir parametre varsayılan argüman aldığı zaman, bu parametrenin sağındaki tüm parametrelerinde varsayılan argüman alması gerekir.
tüm template argüman tipleri (1. type parameter, 2. non-type parameter 3. template template argument parameter) default argument alabilir.
template <typename T = int, int a = 5>;

Not: Modern C++ öncesinde sadece sınıf şablonları varsayılan argüman alabilirdi. Fonksiyon şablonlarının varsayılan argüman alması daha sonra eklendi. 


Alias Template
---------------
Alias template, var olan bir template'in adının daha okunaklı ve açıklayıcı bir şekilde değiştirilmesine olanak tanıyan bir C++ özelliğidir. Alias template, özellikle uzun veya karmaşık template isimleri ile karşılaşıldığında kodun okunabilirliğini artırır.
Alias template'in kullanımı, temel template ismi belirlendikten sonra "using" anahtar kelimesiyle belirlenen yeni bir isim verilmesiyle gerçekleştirilir. Aşağıdaki örnek, "vector" yerine "IntVector" olarak adlandırılan bir alias template oluşturur:

Bu örnekte, "IntVector" adı "std::vector<int>" ile eşdeğerdir. Böylece, kodun okunabilirliği artırılır ve "std::vector<int>" yerine "IntVector" kullanarak kod yazmak daha kolay hale gelir.

template<typename T>
using IntVector = std::vector<int>;

template <typename T>
using IsPointer_t = typename std::is_pointer<T>::type;

is_pointer_t<T> ile typename std::is_pointer<T>::type aynı 
standard kütüphanesde "_t" son ekli templateler alias template için kullanılıyor.
Ör: is_pointer_t<T>


Variable Template
------------------

Daha önceden tanımlanmış bir template'in bir memberını compile time içerisinde değişken olarak tanımlanması için kullanılır.

template<typename T>
constexpr T pi = T(3.1415926535897932385);

is_pointer_v<T> ile std::is_pointer<T>::value aynı 
standard kütüphanesde "_v" son ekli templateler variable template için kullanılıyor.
Ör: is_pointer_v<T>

*/