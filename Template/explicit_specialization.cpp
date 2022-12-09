/* 
EXPLICIT SPECIALIZATION, FULL SPECIALIZATION 
---------------------------------------------

Explicit specialization, öyle bir kod ki belirli template argümanı ya da argümanları için derleyicinin bir specialization oluşturması yerine biim sağladığımız kodun (specialization) kullanılması talimatıdır.
Explicit specialization diğer adı full specialization.
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


SENTAKS
--------

template <typename t> 
T getmax(T x, T y)
{
	return x>y?x:y;
}

template<> 
const char * getmax(const char * p1, const char * p2)
{
    std::strcmp(p1,p2) >= 0?p1:p2;
}



//"<>" diamong olarak da adlandırılır." 


Not: Function template için explicit specialization bazı durumlarda görülmesi zor hatalara neden olabildiğinden programcılar fonksiyon şablonlarında explicit specialization yerine templateleri overload etmeyi tercih ediyorlar. 

Explicit specialization ve template aynı namespace içerisinde olması gerekiyor. Derleyicinin explicit specialization gördüğü noktada master (primary) templati görmesi gerekiyor.

Oluşturulan explicit specialization aynı isimli bir önce tanımlanan overloadın explicit specialization'ı olur. 


Explicit template classlar ile beraber kullanıldığında sınıfların interfaceleri aynı olması gerekmez. 



*/


#include <iostream>
#include <cstring>

template <typename T> 
T getmax(T x, T y)
{
	return x>y?x:y;
}

template<> 
const char * getmax(const char * p1, const char * p2)
{
    return std::strcmp(p1,p2) >= 0 ? p1 : p2;
}


template<typename T>
class MyClass
{
    public:
    MyClass()
    {
        std::cout<<"Primary Template\n";
    }

    void f1();
    void f2();


};


template<>
class MyClass<int>
{
        public:
    MyClass()
    {
        std::cout<<"Explicit template\n";
    }

    void f1();
    void f3();
};

int main()
{
	std::cout<<getmax(10,20) <<"\n";
	std::cout<<getmax(3.85, 4.2) <<"\n";
	std::cout<<getmax("abc","defg") <<"\n";
	std::cout<<getmax("defg","abc") <<"\n";
    /*
    OUTPUT
    -------
    20
    4.2
    defg
    defg
    */

   MyClass<double> md;
   MyClass<const char *> mc;
   MyClass<int> mi;

   /*
   OUTPUT
   --------
   Primary Template
   Primary Template
   Explicit template 
   */

    return 0;

}