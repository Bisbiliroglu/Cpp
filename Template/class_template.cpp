/*
https://github.com/umutkotankiran/Cpp/blob/main/26_07_08_2021/main.cpp

CLASS TEMPLATE
----------------
Function template mekanizması ile derleyiciye bir fonksiyon yazdırıldığı gibi class template ile derleyiciye bir sınıf yazdırılmaktadır.

Class template bir class değildir. Class template class oluşturmayı sağlayan bir koddur. Class'ın kendisi bu templatein herhangi bir specialization'ıdır .

Class template, yapıların türden bağımsızlığını sağlamak için kullanılıyor. Genel kullanım örnekleri olarak veri yapıları verilebilir. Linked list, vector gibi sınıflar class template'dir.


Sentaks
-------
template <typename T>
class Myclass{

};

Class template için typename keywordu kullanmak zorunludur. 

Template kodlar tipik olarak başlık dosyasında tutuluyor. ODR (One defination RUle) ihlal etmiyorlar. 
Ancak sadece bir kaynak dosyada kullanılacka ve diğer kodları ilglendirmiyorsa sadece o kaynak dosyada bulunabilir. Bunun için bir engel yok.

C++ 17 ile Sınıf şablonları için template argument type deduction eklendi. Ancak bu özellik sınırlı bir bağlamda kullanılabiliyor. 
Class template, type deduction işlemine CTAD (Class template argument deduction)

Ör: 
template <typename T>
class Myclass{
Myclass(T)
}

int main()
{
    Myclass<int> a(10); 
    Myclass b(10);

    //Derleyici int bleirtilmemesine rağmen ctor argümanınıdan T nesnesinin int olması gerektiği çıkarımını yapabiliyor.

}

template <typename T>
class Myclass{
public:
	T f(T x); //  T int ise int f(int x );		data olsaydı data atüründen olacaktı ...
	int foo(const T&); // burada da türe göre yazılır.
private:
	T mx;
};
Template parametreleri sınıf kodu içinde heryerde kullanılabilir. public private... 

template sınıfının üyeleri çağrılmadığı süreçte template için obje kodu oluşturulmayacaktır. 


MEMBER FUNCTION SENTAKSI
------------------------
Member functionların belirli bir sentaksi var
1. SINIF ŞABLONUNUN MEMBER FUNCLARINI DOĞRUDAN SINIF TANIMI IÇINDE INLINE OLARAK YAZABILIRIZ.
---------------------------------------------------------------------------------------------
template <typename T>
class Myclass{
public:
	void func();
	
	T foo(T x)
	{
		x.func();
		return x;
	}
private:
	T mx;
};
2. SINIFIN DIŞINDA BU FUNC IN TANIMINI YAZABILIR.
-------------------------------------------------
Bu Cpp de yazabiliriz demek değil çünkü derleyicinin kodu yazabilmesi için kodu görmesi lazım. 
Her durumda bunların tanımını derleyici görmeli yoksa yazamaz. Yine Header file içinde sınıf dışında yazılabilir.
//.h
template <typename T>
class Myclass{
public:
	void func();
	
	T foo(T x);
	
	T f1(T x);
	T f2(T x);
	T f3(T x, T y);
private:
	T mx;
};
template<typename T>   
T Myclass<T>::foo(T x)
{
	//...
}
template<typename U>    // her bir tanımda burası yazılacak.Ayrıca Burada U gibi farklı bir isimde kullanılabilir ancak tipik olanı aynı ismin kullanılması
U Myclass<U>::f1(U x)	
{
}
template<typename T>   
T Myclass<T>::f1(T x, T y)
{
    //EĞER FUNC IÇINDE SINIFIN ISMINI DOĞRUDAN KULLANIRSAK HANGI AÇILIMSA O AÇILIMI KULLANMIŞ OLURUZ.
    	Myclass x; //bu olur. Buda zaten Myclass <T> demek.
		Myclass<T> x; // buda olur.İkiside aynı.

}

iki farklı dosyaya ayırmak istenirse template sınıf tanımları .h dosyasında, implemantasyonu .hpp dosyasında yapılıp hpp dosyası .h dosyası altında tanımların altında include edilebilir. 


DİKKAT : EĞER FUNC IÇINDE SINIFIN ISMINI DOĞRUDAN KULLANIRSAK HANGI AÇILIMSA O AÇILIMI KULLANMIŞ OLURUZ.
template <typename T>
class Myclass{
public:
	void func(T)
	{
		Myclass x; //bu olur. Buda zaten Myclass <T> demek.
		Myclass<T> x; // buda olur.İkiside aynı.
	}
};
--------------------------------------------------------------------------------------------------------------------
FUNC TANIMINI SINIF DIŞINDA YAZINCADA AYNI DURUM VAR.
template<typename U>    // her bir tanımda burası yazılacak.Ayrıca Burada U gibi farklı bir isimde kullanabilirim
U Myclass<U>::func(U x)		// Aynı olacak diye birşey yok ama programcılar aynı ismi kullanıyorlar.
{
	Myclass a; // dendiği zaman bu da Myclass<U> a; demek aslında
}
--------------------------------------------------------------------------------------------------------------------
EĞER RETURN DEĞERI SINIF TÜRÜNDENSE
template <typename T>
class Myclass{
public:
	Myclass func(T);
};
template<typename T>
Myclass<T> Myclass<T>::func(T x) // Bu şekilde yazılır. Return değerine Sadece Myclass yazarsak SENTAKS HATASI.
{
	
}
--------------------------------------------------------------------------------------------------------------------

Normal bir sınıfın üye fonksiyonu template olabilir. Bu türk fonksiyonlara member template denir. 
Class template içerisinde farklı template argğmana sahip member template kullanılabilir. Burada dikkat edilecek nokta template parametre ismini farklı olmasıdır. bkz baz3

Eğer template sınıf içerisinde kullanılan member template fonksiyonun parametresi && yapılırsa UNIVERSAL REFERENCE diğer ismiyle FORWARDING REFERENCE olur.

*/

#include<iostream>


template <typename T>
class MyClass
{
    public:
    MyClass() = default;
    MyClass(T d)
    {
        data = d; 
    }
    T foo (T);
    T bar(T x, T y)
    {
        return x+y;
    }

    void baz(T x)
    {
        x.func();
    }

    void baz2(MyClass x)
    {

    }

    template <typename U>
    void baz3(MyClass<U> x)
    {

    }

    T data;

    template <typename U>
    void universal_reference(U&& u)
    {
        std::cout<<typeid(u).name()<<"\n";
    }

    private:

    T private_data;

};

template <typename T>
T MyClass<T>::foo(T a)
{
 return a;
}



int main()
{
    MyClass<int> i_myclass;
    MyClass d_myclass(2.14); //CTAD
    //MyClass<double> d_myclass;
    std::cout<<"i_myclass.bar(3,5): "<< i_myclass.bar(3,5)<< " d_myclass.foo(5.7): "<<d_myclass.foo(5.7)<<"\n";
    //i_myclass.bar(3,5): 8 d_myclass.foo(5.7): 5.7
    //-------------------------------
    // baz fonksiyonu çağrılmadığı sürece hata vermez
    // i_myclass.baz(5);
    // Derlerken aşağıdaki hata verir.
    //  error: member reference base type 'int' is not a structure or unionx.func();

    
    /*
    i_myclass.baz2(d_myclass);
    
    Hata verir
    note: candidate constructor not viable: no known conversion from 'MyClass<double>' to 'int' for 1st argument MyClass(T d)
    Hata sebebi iki sınıfın farklı olması
    
    Bu hatayı gidermek için func fonksiyonun kendisi de member template yapılabilir. Ancak burada template parametre ismi değişik seçilmelidir. bkz baz3
    
    */
    i_myclass.baz3(d_myclass);
    /*
    i_myclass.baz3(&d_myclass);
    error: no matching member function for call to 'baz3' i_myclass.baz3(&d_myclass);
    */


    i_myclass.universal_reference(d_myclass);
    i_myclass.universal_reference(&d_myclass);    
    i_myclass.universal_reference(std::move(d_myclass));
    i_myclass.universal_reference("test");
    /*
    OUTPUT
    -----------
    7MyClassIdE
    P7MyClassIdE
    7MyClassIdE
    A5_c
    */

 




    return 0;
}