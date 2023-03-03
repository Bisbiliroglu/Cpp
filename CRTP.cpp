/*
CRTP
Curiously Recurring Template Pattern

Runtime polymorphism'e virtual dispatch mekanizması kullanmadan bir alternatif sunuyor.
Virtual dispatch mekanizmasınınbir runtime maliyeti var. Ancak CRTP kullanılırsa işlem compile time sırasında maliyeti olacaktır. 

Bir sınıf şablonunu ile inheritance yapılarak kullanıldığı zaman taban sınıf üye sınfıın fonksiyonlarını çağırabiliyor.



*/

#include <iostream>

template<typename Der>
class MyclassBase{

// Burada T kullanılırsa taban sınıf kendi türemiş sınıfını kullanabiliyor. 
public:
    void foo()// Bu sınıf T ye karşılık gelen taban sınıfı çağırabilir. 
    {
        (static_cast<Der*>(this))->print(); 
        //Bu tamamen CRTP'ye güvenerek yapılıyor. 
        //Burada sentaks hatası yok çünkü compile time sırasında fonksiyon compiler kod yazacak.
        //Eğer türemiş sınıfın print fonksiyonu olmazsa sentaks hatası olacaktır 
    }
};


class Myclass : public MyclassBase<Myclass>
{
    public:
    void bar()
    {
        foo();
    }

    void print()
    {
        std::cout<<"Myclass\n";
    }

};

class Myclass2 : public MyclassBase<Myclass2>
{
    public:
   
    void print()
    {
        std::cout<<"Myclass2\n";
    }

};

class Myclass3 : public MyclassBase<Myclass3>
{
   public:
    void print()
    {
        std::cout<<"Myclass3\n";
    }

};


int main()
{
    Myclass mc;
    Myclass2 mc2;
    Myclass3 mc3;

    mc.foo();
    mc2.foo();
    mc3.foo();
    /*
    OUTPUT
    ------
    Myclass
    Myclass2
    Myclass3
    */
}