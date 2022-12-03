/*
https://github.com/umutkotankiran/Cpp/blob/main/25_01_08_2021/main.cpp

FONKSİYON ŞABLONLARI
--------------------
Derleyicinin verilen şablona göre bir fonksiyon koduyazmasını sağlayan mekanizma

template <typename T>	 buradaki parametre template parametre
T& func(T& x)			 buradaki  paremetre function parametre 
{
    T y;
	//..
}

Template tür parametresi fonksiyon içerisinde her yerde kullanılabilir. Parametre, return type veya fonksiyon içinde bir tür olabilir. 

Başlık dosyasına template kodları konulunca ODR ihlal edilmemiş oluyor. Zaten derleyicinin kod üretebilmesi için bu şablonların
tanımlarını görmesi gerekiyor.

Default Tür Argümanı Kullanımı
---------------------------------
template<typename T, typename U = int>
void func(T x, U = U{})
{
}
Eğer U türünün ne olduğu konusunda bilgi verilmezse, derleyici U türü karşılığında argüman olarak int kullanacak.
int main()
{
	func<double>(1,0.); // burada T double, U ise int (<double> verilmiş sadece tür bilgisi olarak ) olacak
}


TYPE DEDUCTION Örnekleri (T için)
----------------------------------
template <typename T>
class TypeTeller;	 

//Typeteller classı incomplete type olduğu için derleyici derlerken hata verecek ancak. Bu hata için T için typename ismi yazıyor.
Dolayısıyla type deduction'da compiler'ın çıkarım yaptığı tür bilgisi bulmak için kullanılabilir.


template <typename T>
void func(T)
{
	TypeTeller<T> x;	
}						
int main()
{
	func(12); // Burada argüman olan tür ne ise derleyici T yi o tür olarak alacak. İNT olacak.
	
	//------------------------------------------------------------------------------------------------------
	
	const int a = 5;
	func(a); // int olacak. const luk düşüyor.auto daki gibi.
	
	//------------------------------------------------------------------------------------------------------
	
	const volatile int b = 10;
	func(b) // yine int. volatile ve const düştü
	
	//------------------------------------------------------------------------------------------------------
	
	int i = 3;
	int &r = i;
	func(r); // T nin türü int olacak. & düştü.
	
	//------------------------------------------------------------------------------------------------------
	
	int i = 3;
	const int &r = i;
	func(r) ; // T türü yine int. hem int hemde & düştü.
	
	//------------------------------------------------------------------------------------------------------
	
	int a[] = {1,2,3,4,5};
	func(a); // T türü int *
	
	//------------------------------------------------------------------------------------------------------
	
	const int a[] = {2,5,7,8};
	func(a); // türü const int *
	
	//------------------------------------------------------------------------------------------------------
	
	func("haydar"); // const char *
	
	//------------------------------------------------------------------------------------------------------
	int foo(int);
	int main()
	{
		func(foo); // int(*)(int);
	}
	//------------------------------------------------------------------------------------------------------
}


TYPE DEDUCTION Örnekleri (T& için)
----------------------------------

template <typename T> 
class TypeTeller;	 
template <typename T>
void func(T&)
{
	TypeTeller<T> x;	
}						
int main()
{
	
	//------------------------------------------------------------------------------------------------------
	int x = 10;
	func(x); // T türü int.		Func ın içi func(int&) oldu yani
	//------------------------------------------------------------------------------------------------------
	const int x = 10;
	func(x); // T türü const int.		Func ın içi func(const int &) oldu.
	//------------------------------------------------------------------------------------------------------
	int a[5] = {0};
	func(a); // T türü int [5].		Func ın içi func(int (&r)[5]) oldu.
	//------------------------------------------------------------------------------------------------------
	const int a[5] = {0};
	func(a); // T türü const int [5].		Func ın içi func(const int (&r)[5]) oldu.
	//------------------------------------------------------------------------------------------------------
	func("Haydar"); // T türü const char [7] .		func ın içi func(const char (&r)[7])
	//------------------------------------------------------------------------------------------------------
	int foo(int);
	int main()
	{
		func(foo); // T türü int (int).			Func ın içi  func(int(&)(int));
	}
	//------------------------------------------------------------------------------------------------------

TYPE DEDUCTION Örnekleri (T&& için)
----------------------------------
template <typename T>
void func(T &&)
{
	
}

Standartların kullandığı terminolojiye göre buradaki parametreye FORWARDING REFERENCE deniliyor.
Aynı anlamda kullanılan 2. bir terim ise Scott Meyers in terminolojiye kazandırdığı UNIVERSAL REFERENCE .

T&& durumunda, reference collapsing olabiliyor.

T&		 &		&
T&		 &&		&
T&&		 &		&
T&&		 &&		&&

class Myclass{
};
using Type = Myclass&;
using Nec = Type&;		// Myclass & & geliyor. & + & --> &; Nec in türü Myclass&
using Type = Myclass&&;
using Nec = Type&;		// Myclass& yine
using Type = Myclass&&;
using Nec = Type&&;		//  Myclass&& + && --> &&. Nec türü Myclass&&


template <typename T> 
class TypeTeller;	 
template <typename T>
void func(T&&)
{
	TypeTeller<T> x;	
}						
int main()
{
	//------------------------------------------------------------------------------------------------------
	func(10); // T nin türü int.			Func ın içi func(int&&) oldu
	
	AÇIKLAMA
	auto &&x = 10 dersek
	auto burada int oldu.
	T ye karşılık int geldi
	func(T&&) yani func(int&&) oldu
	
	//------------------------------------------------------------------------------------------------------
	int x = 10;
	func(x); // T nin türü int&.			Func ın içi &+&& -> &. func(int&) oldu
	AÇIKLAMA
	auto &&x = x dersek
	auto burada int& oldu.
	T ye karşılık int& geldi
	int & && --> Sonuç int& çıktı.
	func(T&&) yani func(int& &&)--> func(int&)
	//------------------------------------------------------------------------------------------------------
}


Template argument deduction her zaman başarılı olamayabilir. Bunun iki sebebi olabilir.

1 - derleyicinin function çağrısında kullanılan argümanlardan yola çıkarak template tür parametresinin ne olduğunu anlama şansı olmaz
template <typename T>
T foo()
{
	
}
int main()
{
	foo(); // func parametresi yok derleyici T türünün ne olduğunu anlayamayabilir.Argüman yok çünkü. 
}


2 - Ambigiuty
Birden fazla parametre değişkeni olan fonksiyonlarda aynı tür tipi kullanılmışsa ve bu tür tipi için farklı çıkarımlar yapılmışsa olur. 

template <typename T>
void func(T x, T y);
int main()
{
	func(1,2); // GEÇERLİ. int int
	func("ali","veli"); //GEÇERLİ. const char *, const char *
	func(3.4,2.44); // GEÇERLİ double double
	func(2,3.4); //SENTAKS HATASI. int double. int mi double mı ? Ambigiuty.
		
}


template <typename T>
void func(T &x, T &y);
int main()
{
	int a[5]{}, b[5]{},c[4]{};
	func("Ali","Can"); //Geçerli
	func("Umut","Haydar"); //Geçersiz çünkü const char [5] , cosnt char [7]
	func(a,b);	//GEÇERLİ
	func(a,c); //GEÇERSİZ çünkü int [5] , int [4]
}

template <typename T>
void func(T &&x, T &y);
int main()
{
	int i = 10;
	//----------------------------------------------------
	ÇOK ÖNEMLİ !!!
	
	func(i,i); 	//SENTAKS HATASI
	- birinci parametre için, karışık kısım bu
	auto &&x = i dersek 
	auto burada int& olur.
	Tye karşılık int& gelir
	func(T&&,diğer param) için func(int& &&, diğer param) --> func(int&, diğer param)
	
	- ikinci parametre için
	auto &y = i dersek
	auto burada doğrudan int çıkar. 
	T ye int geldi yani
	func(birinci param, T&) --> func(birinci param, int&)
	BURADAKİ SIKINTI T BİRİNDE İNT İKEN DİĞERİNDE İNT&.AMBIGIUTY !!!!
	int&, int  AMBIGIUTY. T ikisi arasında seçilemez
	//----------------------------------------------------
	
	func(15,25); // GEÇERSİZ.
	
	-Birinci parametre
	auto &&x = 15 dersek
	auto burada int çıkar
	T ye int geldi 
	func(T&& , ...) --> func(int && , ...)
	
	-İkinci Parametre
	auto &x = 25; //SENTAKS HATASI. Lvalue reference, R value exp bind etmez.
	SENTAKS HATASI
	
	//----------------------------------------------------


    template <typename T>
    void func(T**)
    {
    }
    int main()
    {
        int x{};
        int *ptr{&x};
        int **p{&ptr};
        func(p); // Burada T burada int türü olur.
        
        // void func(T*) olsaydı 
        
        func(p); // Burada T burada int* türü olur
        // void func(T) olsaydı 
        func(p); // burada da int** olur.
    }

    template <typename>
    class TypeTeller;
    template <typename T, int size>
    void func(T (&)[size])
    {
        TypeTeller<T> x;
    }
    int main()
    {
        int a[10];
        func(a); // T nin türü burada int.  func parametre değişkeni ise int (&r)[10] olacak.
    }

}

FUNCTION OVERLOADING

template <typename T>
void func(T x)
{
	std::cout <<"function template type is " << typeid(T).name() << "\n";
}
void func(int)
{
	std::cout << "Gercek Function\n";
}
int main()
{
	double dval{};
	func(dval);
}

Derleyici bu noktaya gelince template fonksiyon için argument deduction yaparak bir fonksiyon imzası üretiyor. 
Template üretilen fonksiyon ve int parametreli fonksiyonlar aday fonksiyon oluyor. Template üretilen fonksiyon double parametreli olacağı için o fonksiyon çağrılıyor. 
Eğer double değil float gönderilseydi template o zaman float parametreli fonksiyon üretip onu çağrıcaktr. 
Eğer func(24) şeklinde int parametreli fonksiyon üretilseydi bu noktada derleyici yeni fonksiyon yazmayacaktı. Hali hazırda geliştiricinin yazdığı int parametreli fonksiyonu çağrıcaktı.

KURAL : Gerçek fonksiyonların, function overload resolutionda templatelere göre üstünlüğü var.


PARTIAL ORDERING RULES
----------------------

İki template fonksiyonda type deduction sonrasında uygun durumda ise daha spesifik olan çağrılır.

template <typename T>
void func(T x)
{
	std::cout << "1";
}
template <typename T>
void func(T *x)
{
	std::cout << "2";
}
int main()
{
	func(12); 1
	int x{};
	func(&x); iki fonksiyon da legal ama 2 numaralı fonksiyon spesifik bir parametresi olduğu için 2 seçilir. 
}


2 Sayıyı toplayan bir template fonksiyon yazılırsa
template<typename T>
T sum(T x, T y)
{
	return x + y;
}
int main()
{
	auto x = sum(12,45);   // T değeri int
	auto x = sum(1.2,4.5); // T değeri double
	string s1{"veli"},s2{"ali"};
	auto z = sum(s1,s2); // T burada string
	auto x = sum(4, 4.5); //BURASI SENTAKS HATASI.
}


Farklı 2 türden değerin için template yazılırsa
template<typename T, typename U>
T sum(T x, U y)
{
	return x + y;
}
int main()
{
	auto z = sum(3, 3.4); //Z nin türü burada return değeri T olduğundan ve o da int olur. işlem sonucu 6.4 olsa da dönüş tipi int olduğu için 6 döner. Veri kaybı oluşur.
}

Veri kaybının önüne geçmek için programcı explicit double girebilir. Ancak aşağıdaki yolları da deneyebilir.

TRAILING RETURN TYPE 
---------------------

auto sum(T x, U y) -> double  
{ 
    	return x + y;
}

template <typename T,typename U>
decltype(x+y) sum(T x, U y)  // BURADA HATA VAR. Func parametre isimleri x ve y decltype kısmında kullanılamaz.
{								//  x ve y nin scope u orası değil.
	
}
Aşağıdaki gibi yazılabilir.
template <typename T,typename U>
auto sum(T u, U y) -> decltype(x+y) 
{
	
}

AUTO RETURN TYPE (C++ 14)
Hem gerçek func lar hemde func şablonları için kullanılabiliyor.
auto SUM(int x, double y)
{
	return x * y -1;
}


DECLTYPE AUTO
-------------
decltype kurallarına göre tür çıkarımı yapılır
template <typename T>
decltype(auto) foo(T x)
{
	return (x);   
}

Decltype Kuralları
-----------------
1 - İsim formunda ise
Bu isim hangi türden declere edildiyse bizim elde ettiğimizde o tür
2 - İsim formunda ifade değilse
Bu durumda decltype karşılığı elde edilen tür parantez içindeki ifadenin value kategorisine bağlı.
a - eğer ifade pr value expr ise, decltype yerine gelen tür 	T türü
b - eğer ifade L value exp.ise decltype yerine geşen tür 	T & türü
c - eğer ifade X value exp.ise decltype yerine geşen tür 	T && türü


template <typename T>
decltype(auto) foo(T x)
{
	return (x);   // decltype kurallarına göre tür çıkarımı yapılırsa decltype((x)); int& çıkar
	int *ptr;
	return *ptr; // burada ise decltype(*ptr); int& çıkar türü.
}
int main()
{
	foo(12);	
}
SONUÇ : AUTO VARSA RETURN TÜR ÇIKARIMI AUTO YA GÖRE DECLTYPE(AUTO) VARSA DECLTYPE AUTOYA GÖRE YAPILIR !!!!
auto func()
{
	const int x = 10;
	return x;  // burada bunun çıkarımı auto ya göre INT olur
}
//main
decltype(auto) func()
{
	const int x = 10;
	return x;  // Budrada ise decltype(auto) ya göre CONST INT olur.
}



TYPENAME KEYWORD
----------------
template <typename T>
int func(T x, int y)
{
	typename T::Nec;
}
Diyelim ki T ye bağlı bir nested type oluşturmak istiyoruz.Normalde T::Nec a; gibi 
BU şekilde yazdığımızda dilin kurallarına göre burada öncelik bunun bir nested type olması yönünde değil,
bunun sınıfın static bir veri elemanı olması yönünde. DOlayısıyle dilin kurallarının çözünürlük operatörünün
sağ tarafında(Eğer sol tarafı bir template parametresi ise) ki ismin bir tür ismi olarak alınmasını istersek
burada typename keyword ünü kullanmak zorundayız.

Yani T türünün bir nested type olan Nec i bir tür  bilgisi olarak kullanacaksak başına typename koyacağız. 
Aşağıdaki gibi olacak

template <typename T> // buradaki typename yerine class gelebilir
typename T::value_type func(T x, int y)
{
	typename T::Nec; // Buradaki typename yerine class keyword gelemez.
}

Eğer template tür parametresine bağlı bir türden bahsediyorsak, bunu çözünürlük operatörü ile niteliyorsak, bunun bir tür bilgisi olduğunu
başka bir anlamda ele alınmaması gerektiğini belirtmek için typename keyword kullanmak zorunlu.

template <typename T> // buradaki typename yerine class gelebilir
typename T::value_type func(T x)
int main()
{
	func(12); //  SENTAKS HATASI. Burada T in türü. int in nested type ı olarak belirtilmiş 
				// ama böyle bir tür yok.Olamaz çünkü int primitive tür.class değil. 
}

template <typename T> 
typename T::value_type func(T x);
class Myclass{
public:
	typedef int value_type;
};
int main()
{
	Myclass mx; 
	func(mx); // GEÇERLI çünkü Myclass ın value_type isimli türü var

}


template <typename T>
typename T::Nec func(T x);
void func(double);
int main()
{
	func(12); //SENTAKS HATASI YOK. Çünkü SFINAE
}


Bir sınıfın herhangi bir üye fonksiyonu hatta ctor'u bile function template olabilir. Bunun için sınıfın template olması gerekmekz

*/

#include<iostream>


template<typename T, typename U>
auto sum1(T x, U y) -> decltype(x+y)
{
    return x+y;
}

auto sum2(auto x, auto y) //use of 'auto' in parameter declaration only available with '-std=c++20' or '-fconcepts'"
{
    return x+y;
}

template <typename T>
void baz(T x)
{
	std::cout << "1\n";
}
template <typename T>
void baz(T *x)
{
	std::cout << "2\n";
}

template <typename T>
void func(T x)
{
	std::cout <<"function template type is " << typeid(T).name() << "\n";
}
void func(int)
{
	std::cout << "non-template function type is int\n";
}


template <typename T>
void bar(T) = delete;

void bar(int x)
{
    std::cout << "bar function\n";
}


template <typename T,typename U>
void foo(T x, U y)
{
}


template <typename T, int a>
void non_type_template(T x)
{
	std::cout << typeid(T).name() << "\n";
	std::cout << a;
}



int main()
{
	
	func(2.4);
    func(2.4f);
    func(3u);
    func(5);
    /*
    OUTPUT 
    _____________
    function template type is d
    function template type is f
    function template type is j
    non-template function type is int
    */



    //sadece int parametreli fonksiyon çağrılabilir. Kalan tüm fonksiyonlar template kullanarak delet edildi. 
    bar(5); 
    // bar(5.7); error: use of deleted function 'void bar(T) [with T = double]'


	baz(12); // 1 numaralı fonksiyon çağrılır
	int x{};
	baz(&x); // iki fonksiyon uygun olsa da 2 numaralı fonksiyon daha spesifik olduğu için 2 çağrılır.


    foo<double>(12,5); // T türü double, U türü deductiondan int olarak çıkarılır.
	foo<double,int>(12,5); // T türü double, U türü int olarak programcı tarafından verilmiş.


	non_type_template<int,5>(39); //i ve 5 yazar


    auto a = sum1(3.5,6);
    auto b = sum1(6,3.5);
    auto c = sum2(3.5,6);
    auto d = sum2(6,3.5);

    std::cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<" d: "<<d<<"\n";
    //a: 9.5 b: 9.5 c: 9.5 d: 9.5


    return 0;

}