/*
References
https://github.com/umutkotankiran/Cpp

Exception handling, program çalışma zamanında meydana olağandışı durumların yakalanması ve işlenmesi için kullanılan mekanizmadır. 
Meydana gelen olağandışı durumlar hata olarak adlandırılır. 

Hatalar compile time (derleme zamanı) veya run time (çalışma zamanı) meydana gelebilir. 
Compile time'da meydana gelen hataların bir kısmı derleyeici sentaks hatası olarak bildirir.
Run time'da meydana gelen hatalar, programın dinamik bellek bloğunu alocate etmeye çalışması ama edememesi veya kullanıcıdan gelen sayılar ile sıfıra bölünme hatası gibi hatalardır.
Bu hatalar meydana geldiği zaman program işlevini yapamadığı anlayabiliyor ve hata gönderebiliyor. Ancak burada önemli konu bu hatalar meydana gelince programın nasıl davranacağına karar vermek. Buna exeption handling (hata işleme) deniliyor.

EXCEPTION HANDLING 3 ANA BİLEŞENİ VAR
-------------------------------------
1 - Try Blok
------------
İçinde çalışan kodda hata denetimini yapan alan. Bu blok içerisinde hata arama yapılır. 

2 - Catch Blok
--------------
Try dan hata gelirse, programın akışı durdurulup bu bloğun içine geliyor. Hata çözme, kullanıcıya bildirme işlemi burada yapılabilir. Eğer hata çözecek kısım burası değilse hata bir üst katmana iletilebilir. Bu kısım parametre olarak hata objesini alır. Gelen hata objeleri aynı ise program catch bloğunun içine girer.

3 - Throw Statement
-------------------
Beklenmeyen durum (Hata) oluştuğu zaman, bu bilgiyi kendisini çağıran koda gönderecen keyword. Hata gönderimi objeler ile olmakta. Bu obje bir class object olabileceği gibi, int string vb. de olabilir. Bu objennin tipine göre farklı catch blokları oluşabiliyor.


Exception hiç yakalanmazsa program terminate fonksiyonunu çağrıyor. Bu fonksiyon default olarak abort fonksiyonu ile programı sonlandırıyor.
Set terminate fonksiyonu ile terminate fonksiyonunun çağırcağı fonksiyon değiştirilebiliyor. Set terminate fonksiyonunun dönüş değeri, set terminate fonksiyonu çağrılmadan önceki çağırdığı fonksiyon. Program ilk başladığı zaman dönüş değeri abort fonksiyonu adresi oluyor.

catch(...) bloğu ile tüm exceptionlar yakalanabilir.

try bloklarının en az bir tane catch bloğu olmak zorundadır. Birden fazla cath bloğu da olabilir. Bu bloklardan ilk yakalayan ctach bloğunun içine program girer diğerlerine girmez. Dolayısıyla catch blokları özelden genele doğru sıralanacak şekilde oluşturulmalıdır.

Standard Templete Libraray'nin exception türünden bir base sınıfı var. tüm std hataları bu sınıftan türüyor. 
Exception sınıfının what isminde bir virtual fonksiyıonu var türeyen sınıflar bu fonksiyonu override ediyor ve hata ile ilgili bilgi giriyor. catch altında bu fonksiyon ile hata bilgisi alınabilir.
Catch bloğu farklı türleri yakalamasa da runtime polymorphisimini destekliyor. Dolayısıyla tüm std exceptionlar için exception türünden veri beklenebilir. 
Eğer oluşturulan custom exception nesnesi what fonksiyonunu override etmezse 

HATA YAKALANDIĞINDA TİPİK SENARYOLAR 
------------------------------------
Basic Guarante
--------------
Program çalışmaya devam eder.Bu devam etme şu koşullarda olmalı.
 - Programın durumu değişebilir ancak tutarlı bir durumda kalacaktır
 - Hiçbir kaynak sızıntısı olmayacak
 - Hayatı devam eden nesneler geçersiz/invalid bir duruma gelmeyecek.	
Bu garantiye basic guarantee deniyor.Bir exception gönderildi ama bizim func ımızın çalışması kaynak sızıntısı oluşturmayacak 
ve herhangi bir invalid meydana getirmeyecek.Buna deniyor.
Bu duruma exeption safe deniyor. Bir programın exception safe olması nedir?.
 - Program çalışırken hata gönderilme ihtimali olan tüm nesneleri yakalayacak. Uncaught exception olmayacak.Tüm hataları yakalayacak
 - Herhangibir function bir exception gönderdiğinde yani bir throw işlemi yaptığında hiçbir kaynak sızıntısı olmayacak
   ve hayatı devam eden nesneler invalid hale gelmeyecek.

cppreference de exception safety kısmında ne tip bir garanti olduğu yazıyor. Mesela exception verdiğinde memory leak oluştu
bu kabul edilebilir değil. Ne STD lbirary de ne de third partide 

Nesnelerin değeri basic guarantee de değişmiş olabilir ancak geçersiz olamaz. Örneğin bir vector hata sonucunda sıfırlanabilir vb.


Strong Guarantee
---------------
Fonksiyon expception throw ederse, fonksyion çağrılmadan önceki state ne ise o durum sağlanacak. Bu garanti zaten basic garantinin
verdiklerini verip bir de üstüne programın state ini koruma garantisi veriyor.
STD librarynin bir çok sonkyionu strong guarantee veriyor.
Buradaki garantiye commit or rollback te deniyor aynı zamanda.
Bundan ya iş yapılmış halde çıkılacak yada exception oluşursa, bu fonksyion
çağrılmadan önceki nesnenin state i ne ise ona dönülür.
 - Programın durumu değişemez
 - Commit or rollback yani ya işini yapacak ya da eski state e geri dönecek
 - Program tutarlı bir durumda kalacak 
 
 Strong, Basic ten daha maliyetli.
Nothrow Guarantee
----------------
En güçlü garanti. Benim çalışmam sırasında exception throw edilmeyecek diyor. Buna güvenip compiler optimizasyonda yapıyor.
cppreference tan bakılabilir.
Şimdi func yazarken baştan belirlenmiş exception garatiside var.
 - Fonksiyon işini yapma garantisi veriyor.
 - Hata gönderilirse kendisi yakalayıp işini yapacak.
Burada kullanılan terimler
emit = Exceptionun dışarı sızması anlamında
propagate = Çağıran fonksiyondan dışarı çıkması demek.


Gelen hata hiç değiştirilmeden yukarı gönderilmek istenirse rethrow edilebilir. Bunun için throw ; yazmak yeterlidir yanına herhangi bir şey yazmaya gerek yoktur. Bu işlem ile compiler üretti hata nesnesini herhangi bir kopyalam vb. işlem yapmadan direkt yukarıdaki fonksiyona taşır.
re-throw işlemi için thow; yerine throw ex; gibi gelen hata tekrar throw edilmeye çalışılırsa object slicing oluşabilir ve kopyalama işlemi yapılır. Zaten bu işlem re-throw değildir. 

SORU: Aşağıdaki durumda gönderilen tüm hata nesnelerini yakalamış olma garantim var mı?
CEVAP: HAYIR
int main()
{
	try
	{
		// all code in main
	}
	catch(...)
	{
		
	}
}
Çünkü global değişkenler olabilir.Global değişkenler veya sınıfların static veri elemanı olan değişkenler hayata main çağrılmadan önce geliyor.
Bizim uygulamamızda static ömürlü global değişken veya bir sınıfın static veri elemanı varsa bunların ctorları mainden önce çalıştırılıyor.
Dolayısı ile o kod bu try bloğu içinde değil.Dolayısı ile onların ctorları exception gönderirse yakalama şansımız yok.


STACK UNWINDING 
------------------------------------
Otomatik ömürlü nesneler bulunduğu scope tan çıkılınca hayatıda sona eren nesnelerdir. Eğer bulunduğu scopetan
çıkılmadan exception throw edilmiş ve hata yakalananmışsa terminate fonksiyonu çağrılır. 

1 - Eğer uncaught exception oluşmuşsa o exceptionun gönderildiği yere kadar oluşturulmuş otomatik ömürlü sınıf nesneleri için destructor 
çağrılma garantisi yoktur. 

2 - Eğer exception yakalandıysa, otomatik nesneler oluşturulduğu sıranın tersi şeklinde tek tek yok edilir. Buna stack unwinding denir. 

Exception handling işlevinin en önemli özelliklerinden birisi stack unwindingdir. Böylece hata durumunda oluşturulan nesneler için destructor çağrılır

Stack unwinding işleminde stackte sondan başa oluşturulmuş tüm otomatik ömürlü nesneler için destructor çağrılır.
Hata yakalndığında program akışı henüz catch bloğuna girmemişken stack unwinding işlemi başlar ve tüm destructorlar çağrılmış olur.

destruvtor içerisinde exception throw etmemek gerekir. 

otomatik ömürlü nesnelerde destructorlar çağrılsa da dinamik ömürlü nesneler için böyle bir durum yoktur. Dolayısıyla dinamik ömrülü nesnelerde hata durumunda kaynak sızıntısı olabilir.
dinamik ömürlü nesnelerde kaynak sızıntısını önlemek için RAII idiomu veya smart poninterlar kullanılabilir.

*/


#include<iostream>
#include<stdexcept>
#include <memory>



#define print_function_start    std::cout<<__func__ <<" function just started\n";
#define print_function_end      std::cout<<__func__ <<" function has ended\n";



void re_throw_example()
{
    print_function_start
    try
    {
         throw std::runtime_error("Re_throw_example throw");
    }
    catch(const std::exception& e)
    {
        std::cout<<"Exception caught for re_throw_example function \n";
        std::cerr << e.what() << '\n';
        throw; //re-throw same object 
    }
    print_function_end
}

void f1()
{
    print_function_start
    throw 7;
    print_function_end
}

void f2()
{
    print_function_start
    f1();
    print_function_end
}
void f3()
{
    print_function_start
    f2();
    print_function_end
}
void f4()
{
    print_function_start
    f3();
    print_function_end
}




void f5() noexcept
{

}

//f4 ile aynı true olusaydı f5 ile aynı olacaktı
void f6() noexcept(false)
{

}

void f7() noexcept(noexcept(f5()))
{

}


class Myclass
{
    public:
    Myclass()
    {
        std::cout <<"Kaynak edinildi\n";
    }

    ~Myclass()
    {
        std::cout<<"Kaynak geri verildi\n";
    }

};



class Myexception : public std::exception{
public:
	Myexception()
	{
		std::cout << "Myexception default ctor\n";
	}

     const char* what() const noexcept override //_NOEXCEPT ile noexcept aynı ancak mac de noexept hata verdi
    {
        return "Myexception error";
    }
	
	~Myexception() noexcept
	{
		std::cout << "Myexception Destructor\n";
	}
	Myexception(const Myexception &other)
	{
		std::cout << "Myexception Copy Constructor\n";
	}
};


int main()
{

    print_function_start
    /*

     try
    {
        f4();
    }
    catch(const int& e)
    {
        std::cerr <<"Exception caught for int: " << e << '\n';
    }
  
    f1 fonksiyonunda atılan hata yakalandı. catch bloğundan sonra program devam etti.

    OUTPUT
    ____________________________________
    main function just started
    f4 function just started
    f3 function just started
    f2 function just started
    f1 function just started
    Exception caught for int: 7
    Main function is ongoing
    main function has ended
    */


   /*
    f4()

    f1 fonksiyonunda atılan hata yakalanmadı, terminate fonksiyonu çağrıldı ve program sonlandırıldı.

    OUTPUT
    ____________________________________
    main function just started
    f4 function just started
    f3 function just started
    f2 function just started
    f1 function just started
    libc++abi: terminating with uncaught exception of type int
   */


   /*

   try
    {
        f4();
    }
    catch(const double& e)
    {
        std::cerr <<"Exception caught for int: " << e << '\n';
    }
    

    f1 fonksiyonunda atılan hata catch bloğu double olduğu için yakalanmadı, terminate fonksiyonu çağrıldı ve program sonlandırıldı.

    OUTPUT
    ____________________________________
    main function just started
    f4 function just started
    f3 function just started
    f2 function just started
    f1 function just started
    libc++abi: terminating with uncaught exception of type int

  */



/*
   try
   {
     throw Myexception();
   }
   catch(const std::exception& e)
   {
    std::cout << "Exception caught for Myexception\n";
    std::cerr << e.what() << '\n';
   }
    
    Myexception nesnesi yakalandı ve program devam etti. catch referans cinsinden parametre aldığı için compiler hata nesnesini object slicing olmadı. what fonksiyonu ovverride edildiği gibi davrandı.

    OUTPUT
    ____________________________________
    main function just started
    Myexception default ctor
    Exception caught for Myexception
    Myexception error
    Myexception Destructor
    Main function is ongoing
    main function has ended
    */
    /*
   try
   {
    Myexception mex = Myexception();
     throw mex;
   }
   catch(std::exception e)
   {
    std::cout << "Exception caught for Myexception\n";
    std::cerr << e.what() << '\n';
   }


    Myexception nesnesi yakalandı ve pro gram devam etti. throw'a geçici nesne gösterilmediği için copy constructor çağrıldı ve program başka hata nesnesi üretti. catch referans cinsinden parametre almadığı için compiler hata nesnesini object slicing oldu ve what fonksiyonu base class (std::exception) gibi davrandı.

    OUTPUT
    ____________________________________
    main function just started
    Myexception default ctor
    Myexception Copy Constructor
    Myexception Destructor
    Exception caught for Myexception
    std::exception
    Myexception Destructor
    Main function is ongoing
    main function has ended
    */


    /*

    try
    {
        Myclass a;
        Myclass b;
        Myclass c;
        Myclass d;
        throw std::runtime_error("Error was occured");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    stack unwinding olduğu için  hata oluşunca otomatik ömürlü nesneler için destructor çağrıldı.

    OUTPUT
    ____________________________________
    main function just started
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    Kaynak geri verildi
    Kaynak geri verildi
    Kaynak geri verildi
    Kaynak geri verildi
    Error was occured
    Main function is ongoing
    main function has ended
    */



    /*
    Myclass a;
    Myclass b;
    Myclass c;
    Myclass d;
    throw std::runtime_error("Error was occured");
  
    Error yakalanmadığı için stack unwinding olmadı ve destructorlar çağrılmadı.

    OUTPUT
    ____________________________________
    main function just started
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    libc++abi: terminating with uncaught exception of type std::runtime_error: Error was occured
    */


    
    /*

    try
    {
        Myclass * a = new Myclass;
        Myclass * b = new Myclass;
        Myclass * c = new Myclass;
        Myclass * d = new Myclass;
        throw std::runtime_error("Error was occured");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    stack unwinding olsa da dinamik ömürlü olduğu için kaynaklar geri verilmedi.

    OUTPUT
    ____________________________________
    main function just started
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    Error was occured
    Main function is ongoing
    main function has ended
    */

    /*

    try
    {

        auto a = std::make_unique<Myclass>();
        auto b = std::make_unique<Myclass>();
        auto c = std::make_unique<Myclass>();
        auto d = std::make_unique<Myclass>();
        throw std::runtime_error("Error was occured");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    dinamik ömürlü olsa da smart pointer kullanıldığı için kaynaklar geri verildi.

    OUTPUT
    ____________________________________
    main function just started
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    Kaynak edinildi
    aynak geri verildi
    Kaynak geri verildi
    Kaynak geri verildi
    Kaynak geri verildi
    Error was occured
    Main function is ongoing
    main function has ended
    */
  
    /*

    std::cout<< "f4 functions no except guarantee is " << noexcept(f4())<<"\n";
    std::cout<<"f5 functions no except guarantee is "<< noexcept(f5())<<"\n";
    std::cout<<"f6 functions no except guarantee is "<< noexcept(f6())<<"\n";
    std::cout<<"f7 functions no except guarantee is "<< noexcept(f7())<<"\n";

    
    OUTPUT
    ____________________________________
    main function just started
    f4 functions no except guarantee is 0
    f5 functions no except guarantee is 1
    f6 functions no except guarantee is 0
    f7 functions no except guarantee is 1
    Main function is ongoing
    main function has ended
    */

/*

*/

    std::cout<<"Main function is ongoing\n";

    print_function_end
    return 0;
}