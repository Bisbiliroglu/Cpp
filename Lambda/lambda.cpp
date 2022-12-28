/*

https://github.com/umutkotankiran/Cpp/blob/main/29_15_08_2021/main.cpp
https://github.com/umutkotankiran/Cpp/blob/main/30_21_08_2021/main.cpp


LAMBDA
======
C++ 11 ile dile eklendi. 
C++ içerisinde nested function açığını kapatıyor. 

Lambda expression şeklinde programcının verdiği fonksiyonlar, derleyici tarafından compile time'da geçici nesne şeklinde yazılıyor. 
Lambda ifadeleri ile derleyicinin oluşturdupu türe closure type, oluşan geçici nesneye ise closure object denir.

Sentaks
-------

[](){}();   // Bu bir lambda ifadesi

[] -> lambda introducer :buraya yazılan ifadelere lambda capture deniyor. Lambda ifadesinden önce oluşturulmuş lokal objeler bu ifadenin içerisine yazılarak lambda içerisine kopyalanabilir. 
ilk () ->  parametre parantezi -> Derleyicinin yazdığı sınıfın parametresinin parantezi
{} -> fonksiyon ana buloğu -> Derleyicinin yazacağı sınıfın anabloğu
son () -> Fonksiyon çağrı operatörü 

Örnek
-------
[](int x){ return x + 5;}  

auto f = [](int x){ return x + 5;};
f(3) gibi çağırabilirim


int x = 10;
auto f = [x](int a){ return x * a; }; //x kopyalama yoluyla alınıyor.
f(45) = 45 * 10 olacak.

[](int x, int y) mutable {};
[](int x, int y) noexpect {};
[](int x, int y) constexpr {};
[](int x, int y)  -> int {};

mutable: üye fonksiyon non-const üye fonksiyon olsun 
noexpect: fonksiyon içerisinde expeection throw etmeme garantisini veriyor. 
constexpr: fonksiyonun constexpr olduğunu anlatıyor. Fonksiyonun constexpr olmasını engelleyen durum olursa sentaks hatası olacak. Not: constexpr yazılmasa bile eğer uygunsa constexpr yapılır.
-> type : trailing return type: Fonksiyonun dönüş tipini beliryor. Eğer bu keyword kullanılmazsa fonksiyonun geri dönüş değeri için bir çıkarım yapılması gerekiyor. 


auto f1 = [](int x, int y){return x*y;};
auto f2 = [](int x, int y){return x*y;};
auto f3 = f1; //C++20
decltype(f1) f4; 

std::cout<<"is_same f1 f2: "<<std::is_same_v<decltype(f1), decltype(f2)><<"\n";
//is_same f1 f2: 0 f1 ve f2 aynı lambda ifadesine sahip olsa da aynı türden değiller. 

std::cout<<"is_same f1 f3: "<<std::is_same_v<decltype(f1), decltype(f3)><<"\n";
//is_same f1 f3: 1  f3 f1 in kopyalanmasından oluştuğu için aynı türe sahipler. 

std::cout<<"is_same f1 f4: "<<std::is_same_v<decltype(f1), decltype(f4)><<"\n";
//is_same f1 f3: 1 f4 f1 in default ctoru ile oluşturulduğu için aynı türde. 

Ancak yapılan bu atama işlemi C++ 20 ile eklendi daha öncesi için atama operatör fonksiyonları ve default ctorları delete ediliyorlardı.
ctor kullanmak sadece statless lambdalar için geçerlidir. 

Introducer []
--------------
Yerel değişkenler bir lambda ifadesi içinde kullanılmak istenirse capture mekanizmasından yaralanılır. 
Lambda ifadeleri yazıldığı zaman derleyiciler bir sınıf kullanarak fonksiyon oluşturur. 
Kullanılan bu sınıf introducer içine yazılan her değişken için bir yerel değişken oluşturur bu yerel değişkenin initialize işlemini introducer içindeki nesne ile yapar. 
Yani introducer içindeki nesne direkt kullanılmaz bir kopyası kullanılır. Ardından const bir üye fonksiyon lambda ifadesi olarak döner
Eğer introducer içerisinde "=" yazılırsa görünürdeki tüm nesneler kopyalanmış olur. [=] Capture all by copy
Eğer introducer içerisine "&" yazılırsa görünürdeki tüm nesnelerin referansı alınmış olur. [&] Capture all reference


    int a = 10;
    auto f = [a](int x)
    {
        a *=x;
    }

oluşturulan fonksiyon const olduğu için hata verir.

    int a = 10;
    auto f = [a](int x) mutable
    {
        a *=x;
    }

bu şekilde yazılırsa hata vermez. Çünkü fonksiyon non-const üye fonksiyon oluyor. 



    int a = 10;
    auto f = [a](int x) mutable
    {
        a *=x;
    };

    f(5);

    std::cout<<"a: "<<a<<"\n";
    //a: 10 

a kendisi değil kopyası içeri alındığı için a değeri değişmez. 

    int a = 10;
    auto f = [&a](int x) mutable
    {
        a *=x;
    };

    f(5);

    std::cout<<"a: "<<a<<"\n";
    //a: 50

Burada referansı sınıf içerisinde oluşturulan referansa geçildiği  için a değeri 50 olur. Burada mutable yazılmasına gerek toktur. 

Statless lambda: herhangi bir değişkeni capture etmeyen lambda
Stateful Lambda: herhangi bir değişkeni capture eden lambda. 

Lmabdalar için oluştutulan lambdaların, default ctorları ve copy assigmentı statless lambda için geçerlidir.  

Statless lambdalar doğrudan fonksiyon pointera dönüşebiliyor.

POSITIVE LAMBDA IDIOM
---------------------
Eğer işaret ooperatoru + kullanılırsa bir dönüşüm gerçekleşir. Burada lambda closure type'ı function pointer olur.

auto f = +[](int a) {return a*a;}; // f function pointer
auto f = [](int a) {return a*a;}; // f bir sınıf türü. 

*/

#include<iostream>

int main()
{
    const auto sum = [](int x, int y){return x+y;};
    std::cout<< "sum(3): "<<sum(3,5)<<"\n"; 
    //sum(3): 8

    auto f1 = [](int x, int y){return x*y;};
    auto f2 = [](int x, int y){return x*y;};
    auto f3 = f1; //C++20
    decltype(f1) f4; 

    std::cout<<"is_same f1 f2: "<<std::is_same_v<decltype(f1), decltype(f2)><<"\n";
    //is_same f1 f2: 0 f1 ve f2 aynı lambda ifadesine sahip olsa da aynı türden değiller. 

    std::cout<<"is_same f1 f3: "<<std::is_same_v<decltype(f1), decltype(f3)><<"\n";
    //is_same f1 f3: 1  f3 f1 in kopyalanmasından oluştuğu için aynı türe sahipler. 

    std::cout<<"is_same f1 f4: "<<std::is_same_v<decltype(f1), decltype(f4)><<"\n";
    //is_same f1 f3: 1 f4 f1 in default ctoru ile oluşturulduğu için aynı türde. 



    int a = 10;
    auto f = [&a](int x) mutable
    {
        a *=x;
    };

    f(5);

    std::cout<<"a: "<<a<<"\n";
    //a: 50

    auto f = [](int a) {return a*a;};


    return 0;
}