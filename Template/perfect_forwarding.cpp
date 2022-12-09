/*
PERFECT FORWADING
------------------
Bir fonksiyon çağıran fonksiyonlarda girilen parametrelerşn aynı şekilde çağrılan fonksiyona transfer edilmesini sağlayan mekanizma.
bu mekanizmada kullanılan araçlar c++11 de dile eklenmiştir. 

Burada gönderilen argümanların value category bilgisi (L value, R value) const, volatile gibi durumlarının aynen krounması gerekmektedir. 

Forwarding reference 
-------------------------
template<typename T>
void perfect_forwarding(T&& r)


template<typename T, typname U, typename V>
void perfect_forwarding(T&& t, U&& u, V&& v)

std::forward()
-------------
perfect forwarding için kullanılan çevrim fonksiyonu. Forward edilecek parametre bu fonksiyon ile çevrilerek istenilen fonksiyona gönderilir.


containerlerin emplace isimli fonksiyonları perfect forwarding uygulanıyor.

template <typename T, typename U, typename K>  
void func(T&& t, U&& u, K&& k)
{
	foo(std::forward<T>(t),std::forward<U>(u), std::forward<K>(k));  
}


*/


#include<iostream>
#include<utility>

template<typename T> // Bu şimdi eklendi.
void func(T x)
{
	foo(x);
}

class Myclass{};

void foo(Myclass&)
{
	std::cout << "Myclass& | L Value Reference \n";
}
void foo(const Myclass&)
{
	std::cout << "const Myclass& | const L Value Reference\n";
}
void foo(Myclass&&)
{
	std::cout << "Myclass&& | R Value Reference\n";
}


template<typename T>
void perfect_forwarding(T&& r)
{
    //parametre universal reference (diğer adıyla forwarding refernce)
    //Gelen parametreye göre reference collapsing uygulanır. Dolayısıyla L value gönderilince parametre L value, R value gönderilirse parametre R value olur.
    //Gelen parametreye L Value gönderilirse T& olur ancaK, R value gönderilirse T olur.

    foo(std::forward<T>(r));
}


int main()
{
	Myclass m;
	const Myclass cm;

	foo(m); 
	foo(cm); 
	foo(Myclass{}); 
    /*
    OUTPUT
    ------
    Myclass& | L Value Reference 
    const Myclass& | const L Value Reference
    Myclass&& | R Value Reference
    */

    func(m);
	func(cm);
	func(Myclass{}); 
    /*
    OUTPUT
    ------
    Myclass& | L Value Reference 
    Myclass& | L Value Reference 
    Myclass& | L Value Reference 
    */


   perfect_forwarding(m);
   perfect_forwarding(cm);
   perfect_forwarding(Myclass{});
  /*
    OUTPUT
    ------
    Myclass& | L Value Reference 
    const Myclass& | const L Value Reference
    Myclass&& | R Value Reference
    */



}