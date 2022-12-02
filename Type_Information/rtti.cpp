/*
https://github.com/umutkotankiran/Cpp/blob/main/24_31_07_2021/main.cpp
https://github.com/umutkotankiran/Cpp/blob/main/25_01_08_2021/main.cpp


RTTI -> Runtime Type Information
Bir nesnenin dinamik türünün programın çalışma zamanında saptanması.

C++ ta bir nesnenin türünü öğrenmek  kötü bir tasarımın sonucu olabilir.Virtual dispatch zaten bunu bilmeden
kullanması olanağını sağlıyor.Runtime polimorfizminin sağladığı temel avantaj bu. Yukarıdaki kodlar aşağıdakilere
bağımlı hale de gelmemiş oluyor.
Ama öyle durumlar varki nesnenin dinamik türünü sorgulamamız gerekiyor. Ya tasarımsal durum ya da belirli kodların bize
sunulmamış olmasından ötürü olabilir.İstediğimizi yapmak için başka bir araç olmayabilir.


runtime da tür saptandığı için bir maliyeti de var.
Bazı durumlarda kullanılabilir ama özünde polimorphic sınıflar sözkonusu olduğunda bir nesnenin dinamik türünün programın runtime da
anlaşılması ve sorgulanmasını sağlıyor.

C++ ta nesnelerin türlerinin çalışma zamanında anlaşılmasına yönelik 3 adet araç seti var.
dynamic_cast -> tür dönüştürme operatorü
typeid -> bir operator çıktısı typeinfo -> bu da bir sınıf türünden bir referans


DYNAMIC CAST
------------

bir down-casting programın çalışma zamanında güvenli olup olmadığını test eder. 
down-casting base class -> derived class

dynamic_cast<target type>(expr)

dynamic_cast operatörü eğer başarılı olurssa hedef türden bir nesne pointer üretir. 
dynamic_cast operatörü eğer başarısız olursa nullptr üretir.
Eğer tür dönüşümü pointer yerine referansa yapılırsa nullreferans olmadığı için BAD_CAST türünden exception throw eder.

dynamic_cast operatörü için operand olan türk polyhmorphic olması gerekir.
Not: bir sınıfı polymorphic



TYPE ID
------------

typeid(type)

typeid(int)
typeid(base)
typeid(der)

typeid operatörünün operandı herhangi bir tip olabilir

typeid(expr)

expr olarak herhangi şey yazılabilir.

dynamic_cast farklı olarak polymorphic sınıf istemez.
typeid operatörü ile oluşturulmuş ifade bir typeinfo nesnesine referans olur
typinfo sınıfından obje üretmenin tek yolu typeid operatörünü kullanmak. 
farklı türlerin (int, double, sınıflar) farklı type info
bunlar == operatörü kullanarak karşılaştırma yapabiliriz.

if(typeid(int) == typeid(x))


typeinfo sınıfının name isimli bir fonksiyonu var.
name fonksiyonu dönen sınıfın ismini yazar
typeid(int).name() = "int"

ancak bu implemention defined farklı derleyiciler için farklı yazılar çıkar. 

if(typeid(Base) == typeid(Der))

eğer base polymorphic bir sınıf ise yukarıdaki if koşulu doğru, diğer durumda yanlış olacaktır. 

type_id nesnesi içinde oluşturulan ifade bir unvaluated context 


POLIMORHIC TÜRLER SÖZKONUSU OLDUĞUNDA DİNAMİK TÜR BİLGİSİ NASIL ELDE EDİLİYOR
------------------------------------------------------------------------------
Derleyiciler virtual dispacth mekanizmasını implemente ederken virtual function table tutuyorlar. 
Bu tablo içerisinde bir index type_info türünden nesne adresi için tutuluyor.


dynamic_cast ile tür bilgisi elde edilirken programın maliyeti, typeid'ye göre daha fazla olabilir. Çünkü tüm taban sınıfılara bakıyor. Typeid operatörü sadece bir tane typeinfo nesnesine bakıyor.
*/

#include<iostream>

class Car
{
    public:
     virtual void func()
     {
        std::cout<<"Car \n";
     }

};

class Audi : public Car
{
    public:
     virtual void func() override
    {
        std::cout<<"Audi\n";
    }
};


int main()
{


Car car;
Audi * ap = dynamic_cast<Audi*>(&car);
car.func();

if(ap != nullptr)
    ap->func();


if(typeid(Car) == typeid(car))
{
    std::cout<<&car<<": is Car\n";
}


if(typeid(Car) == typeid(ap))
{
    std::cout<<&car<<": is Car\n";
}

std::cout<<typeid(*ap).name()<<"\n";

    
return 0;
}