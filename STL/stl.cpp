/*
https://github.com/umutkotankiran/Cpp/blob/main/29_15_08_2021/main.cpp

STL : STANDARD TEMPLATE LIBRARY
--------------------------------
Nesne yönelimli değil, generic bir kütüphane. Kalıtım var ancak runtime polymorphism yok.

STL'in üç önemli üyesi var.

CONTAINER : Veri yapılarını implemente eden sınıf şablonlarına deniyor. Ör: vector dinamik dizi veri yapısını implemente ediyor.

ITERATOR :  Pointer benzeri arayüze sahip.Nesneleri pointer gibi kullanılabilen sınıf şablonları.
	        Amacı : Containerda bulunan öğelerin konumlarını tutan sınıflar.Adreste bir konumdur.Raw pointer da bir iterator olarak kullanılabilir.
	        Containerda bulunan öğelere erişmek için kulanılıyor.
            
ALGORITMA:  Algoritmaları implemente eden fonk şablonları. sort, find, reverse ...
	        Containerda bulunan veriler üzerinde birtakım işlemler yapılması gerekiyor. Bunların yapılması için algoritma denen functionları çağırıyoruz.
	        Algoritmalarla containerları birbirine bağlıyan ise iterator.
	        Algoritmalar iteratorleri kullanarak containerlar üzerinde birtakım işlemler yapan functionlar.


Başka öğelerde var
CONTAINER ADAPTERS, ITERATOR ADAPTERS, FUNCTION ADAPTERS, FUNCTION OBJECTS

STL aynı zamanda extendable bir yapıya sahip. kendimiz yeni algoritmalar oluşturabiliriz.Varolan container veya iteratörleri kullanarak bunları yapabiliriz.
Yeni iterator, container sınıfları oluşturabiliriz. ÖR: Boostta stl de olmayan birsürü container ve iterator sınıfı aynı zamanda algoritma şablonları var


CONTAINERS
============

SEQUENCE CONTAINERS
-------------------
Ekleme silme işlemleri konumla yapılıyor.İstediğim konuma istediğim öğeyi ekleyebiliyorum.
std::vector			-> En çok kullnılan STL container
std::deque			-> double ended queue. Baştan ve sondan ekleme yapabileceğimiz veri yapısı. Dinamik array tutuyor. 
std::list			-> doubly linked list
std::forward_list	-> (C++ 11 de geldi)  singly linled list
std::string			-> Yazı tutuyor.Gördük bunu.Bu da containers.Bunu daha çok STL algoritmalarıyla kullanacağız.
std::array			-> (C++ 11 de geldi) array container.

ASSOCIATIVE CONTAINERS
----------------------
İkili arama ağacı
Ekleme işlemi belirli bir konum değil değerle yapılıyor.
İkili arama ağacı veri yapısı kullanılıyor. Değerin ne olduğuna bağlı olarak ekleneceği yer belirleniyor.
Log N karmaşıklığa sahiptir. 

std::set	    -> Sadece anahtar tutuyor.Tamsayıların setini oluşturursak 17 nin sette olup olmadığını sorgulayabiliriz.Bir anahtardan bir tane var.
std::multiset	-> Bir anahtardan birden fazla olabilir.Tamsayıların setinde 1 tane 12 olabilir.multisetinde 3,4,5,6 tane 12 olabilir.
std::map	    -> Anahtarın değerle eşlendiği veri yapısı.Anahtarla erişiyoruz yine ama anahtar karşılığı bir değere erişiyoruz.Buradakiler pair gibi anahtar değer çifti
std::multimap	-> Bir anahtardan birden fazla olabilir.

UNORDERED ASSOCIATIVE CONTAINERS
--------------------------------
Diğer dillerdeki adı hash tablosu olan veri yapısını implemente eden sınıflar.
Associative containerslardan farklı olarak constant time karmaşıklığa sahiptirler.

std::unordered_set		    -> (C++ 11 de geldi) Sadece anahtar tutuyor.Bir anahtardan bir tane var.
std::unordered_multiset		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.
std::unordered_map	    	-> (C++ 11 de geldi) Anahtarın değerle eşlendiği veri yapısı.Buradakiler pair gibi anahtar değer çifti
std::unordered_multimap		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.

Not: stack, queue, priority_queue container değil container adaptor olarak geçiyor.

Boost içinde STL'den daha fazla container var.


ITERATORS
=========
iteratorler pointerların daha soyutlanmış hali. Containerlerın için konum tutan bir nesne. 
sınıfın başlangıç ve bitiş konumunu bulmak için sınıfın kendi begin ve end fonksiyonları veya c++ ile gelen stdd:begin ve std::end fonksiyonları çağrılır.
Bu fonksiyonlar iteratör cinsinden fonksiyonlar döner. 

global fonksiyonlar olan std::begin ve std::end c style arraylar ile de kullanılabilir. 


begin
cbegin : const begin
rbegin : reverse begin
crbegin :const reverse begin

end
cend :const end
rend :reverse end
crend :const reverse end

Reverse Iteratör
-------------------
reverse iteratör sınıfları begin ve end normal iteratör sınıflarına göre çapraz gibi düşünülebilir. ++ operatörü ise normal iteratörlerin -- operatörü ile benzer çalışır. 
reverse iteratör sınıfları dereference edilirse bir önceki değeri dereference eder. dolayısıyla rbegin dereference edilirse container'ın son ögesi, rend dereference edilirse ise beginden bir önceki değer dereference edilir. 
rend fonksiyonu end fonksiyonu gibi dereference edilirse undefined behavior.
reverse iteratörlerin base isimli bir sınıfı vardır. Bu sınıf iteratörün sarmaladığı sınıfı döndürür. 

begin = rend.base()
end = rbegin.base()

reverse iteratörlerin ve normal iteratörlerin türü birbirinden farklıdır.  
reeverse iteratör normal iteratöre dönüştürmek için .base() fonksiyonu çağrılabilir. Ancak bu durumda rever iteratörün 1 sonraki ögeyi tuttuğunu unutmamak gerekir. 
reverse_iter.base() - 1


ITERATOR CATEGORY
-----------------

iteratör sınıfları containerlar içinde nested sınıf olarak bulunmaktadır. Iteratör sınıflarının ortak interface'i olduğu gibi bazı sınıflar için farklı iteratör overload fonksiyonları olabiliyor. 
Bu yüzden iteratörler farklı kategorilere ayrılmıştır. Bir iteratörün hangi kategoride olduğu o iteratörün interfacinde hangi fonksiyonların olup olmadığını belirler. 

input iteratör
output iteratör
forward iteratör
bidirectional iteratör
random access iteratör 

En yetenekli iteratör kategorisi random accessiteratör. Bu iteratör raw pointer'ın yaptığı her şeyi yapabiliyor.

end fonksiyonun geri dönüş değeri olan iteratör container'ın bittiği noktayı gösteriyor. Bu nokta container içinde değil. Dereference edildiği zaman undefined behaviout oluyor.
Eğer container boş ise begin iteratörü dereference edilmemsi gerekiyor.
-------------------------------------------------------------------------------------------------------------------------------------------------------------
| 		ITERATOR KATEGORİLERİ		    |						                        OPERASYONLAR														|
-------------------------------------------------------------------------------------------------------------------------------------------------------------
|						                |						                                            |         					                    |	
|						                |	Copy constructible				                                |	ostream_iterator	    		            |	
|	 OUTPUT ITERATOR	  		        |	++it	it++	=				                                |	ostreambuf_iterator   	     		        |
|						                |	*it		it->  (sol taraf değeri)	                            |  						                        |
|						                |							                                        |					                            |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
|						                |	Copy constructible			  	                                |						                        |
|						                |	++it	it++	=		  	  	                                |	istream_iterator	      		            |
|	  INPUT ITERATOR	  		        |	*it		it->  (sağ taraf değeri)	                            |	istreambuf_iterator	      		            |
|						                |	it1 == it2		it1 != it2		                                |						                        |
|						                |							                                        |						                        |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
|						                |	Copy constructible - Default Constructible	                    |		 				                        |
|						                |	++it	it++	=				                                |	forward_list		    		            |
|	FORWARD ITERATOR	  		        |	*it    it->  (sağ taraf değeri) (sol taraf değeri)              |	unordered_set		unordered_multiset      |
|						                |	it1 == it2		it1 != it2		                                |	unordered_map		unordered_multimap      |
|						                |							                                        |						                        |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
|						                |	Copy constructible - Default Constructible	                    |						                        |
|						                |	++it	it++	--it	it--		=	                        |	list					                    |
|	  BIDIRECTIONAL		 		        |	*it    it->  (sağ taraf değeri) (sol taraf değeri)              |	set		multiset		                    |
|	    ITERATOR		  		        |	it1 == it2		it1 != it2		                                |	map		multimap		                    |
|						                |							                                        |						                        |
|						                |							                                        |						                        |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
|						                |	Copy constructible - Default Constructible                      |						                        |
|						                |	++it	it++		--it	it--	=	                        |	vector			      		                |
|						                |	*it    it->  (sağ taraf değeri) (sol taraf değeri)              |	deque			      		                |
|	  RANDOM ACCESS		  		        |	it1 == it2		it1 != it2		                                |	array			      		                |
|	    ITERATOR		  		        |	it + n		n + it		it - n		                            |	string			      		                |
|	(Pointer Interface )  			    |	it+=n		it-=n				                                |	C array			      		                |
|						                |	it1 - it2					                                    |						                        |
|						                |	it[n]						                                    |						                        |
|						                |	it1 < it2   it1 <= it2   it1 > it2   it1 >= it2                 |						                        |
-------------------------------------------------------------------------------------------------------------------------------------------------------------



Bütün iteratorlerin iterator_category isimli bir nested type ı var.

vector<int>::iterator::iterator_category 
list<int>::iterator::iterator_category 
forward_list<string>::iterator::iterator_category 

Buradaki nested type STL deki tanımlanmış empty classlardan biri.

struct output_iterator_tag
struct input_iterator_tag
struct forward_iterator_tag
struct bidirectional_iterator_tag
struct random_access_iterator_tag

using type = std::vector<int>::iterator::iterator_category;
cout << typeid(type).name() << "\n"; //random_access_iterator_tag empty classı burası

using type = std::forward_list<int>::iterator::iterator_category;
cout << typeid(type).name() << "\n"; //forward_iterator_tag

is_same template ile compile type içinde iteratör tipleri anlaşılabilir.
is_same_v<type,random_access_iterator_tag>

İteratör Kategorisi Neden Önemli?
---------------------------------
STL algoritmaları iki temel başık dosyasında yer alıyor bunlar

algorithm 
numeric 

Bu başlık dosyasındaki algoritmalar tipik olarak bir range alıyor.
Her algoritma her iteratör kategörisini kabul etmiyor. Farklı algoritmalar farklı iteratör kategorisi istiyor. 


ITERATORLER VE CONST CORRECTNES
-------------------------------

int a = 10;
int * const p = a; // top level const or right const
*p = 56; *p değiştirilebilir. ancak p başka değere atanamaz
const int * p = a; // low level const, left const
*p = 56; hata verir. ancak p =&b olabilir. 


vector<int> ivec {0,1,2,3,4,5};

const vector<int>::iterator iter = ivec.begin();
veya
vector<int>::iterator const iter = ivec.begin();

const bir nesne olduğu için bu sınıfın sadece const üyeleri çağrılabilir.
yazılan iteratör hayatı boyunca hep aynı nesnenin konumunu tutar. 
Tıpkı top level const gibi.

++iter; hata verir.
*iter = 45; hata vermez.

Low level const gibi saft okuma amaçlı kullanılabilen iteratör için const iteratörler kullanılması gerekiyor. 

 vector<int>::const_iterator iter = ivec.begin();
 ++citer; // hata vermez
 *citer = 45; //hata verir


 auto iter  = ivec.begin();
 auto citer = ivec.cbegin();


 citer = iter; sentaks hatası yok implicit convertion oluyor.
 iter = viter; sentaks hatası. 


CONST ITERATOR
--------------
Low level const gibi salt okuma amaçlı kullanılabilen iteratörlerdir. 

 vector<int>::const_iterator iter = ivec.begin();
 ++citer; // hata vermez
 *citer = 45; //hata verir

Örnek olarka bir range içerisinde yazma yapmadan dolaşmak için const iteratörler kullanılıyor. 

const iteratörlere erişmek için containerların cbegin(), cend() gibi fonksiyonlar kullanılabilir. 

ITERATOR MANIPULATION FUNCTIONS
--------------------------------
advance
-------
Bir iteratörü N position ilerletiyor.

advance(iter, N);

Eğer iteratör bidirectional iteratör türünden ise advance fonksiyonu negatif sayılar argüman olarak girilerek geri gitmesi sağlanabilir. 

distance
--------
İki iteratörün farkını verir. 

index_diff = distance(iter1, iter2);

iter1, iter2 den önceki bir pozisyon olmak zorunda. Diğer durumda undefined beheavoir.

next (C++ 11 ile geldi) 
----
new_iter next(iter, N = 1)

next fonksiyona girilen iteratör (L calue ya da R value olabilir) girilen N sayısı kadar iletletilerek aynı türde yeni iteratör döndürür.

Not: advance sadece L value reference alıp onu ilerletir. 

Elde edilecek iteratör konumunun geçerli bir konum olmasından geliştirici sorumludur. Taşırma durumunda undefined behavior oluşur.

prev (C++ 11 ile geldi)
----
new_iter prev(iter, N = 1)

prev fonksiyona girilen iteratör (L calue ya da R value olabilir) girilen N sayısı kadar geriletilerek aynı türde yeni iteratör döndürür.

Not: advance sadece L value reference alıp onu ilerletir. 

Elde edilecek iteratör konumunun geçerli bir konum olmasından geliştirici sorumludur. Taşırma durumunda undefined behavior oluşur.

iter_swap
---------
swap ve iter_swap birbiriyle karıştırılmamalıdır. swap iki nesneyi birbiryle değiştiren fonksiyon şablonudur. 
iteratör nesneleri de diğer tüm nesneler gibi swap fonksiyonu ile değiştirilebilir. 

Ancak iteratörlerin kendisini değil, gösterdiği ögeleri değiştirmek istenirse iter_swap kullanılabilir.

iter_swap(iter1, iter2)

not: const iteratör iter_swap ile kullanılamaz. 

swap(iter1*, iter2*) = iter_swap(iter1, iter2) != swap(iter1, iter2) //fonksiyon davranışı olarak


ALGORITHMS
=========
Tipik olarak parametreleri iteratörler olan ve containerlar üzerinde işlem yapan fonksiyon şablonları.

Conventions
-----------
 1.) Belirli bir range yazan algoritmalar (ör copy) en son yazdıkları konumadan bir sonraki konumu döndürürler. 
 2.) Parametrelerde kaynak range önce, hedef range sonra olur.
 3.) Arama algoritmaları konum döndürmektedir. Bulursa bulduğu konumu bulamazsa end konumunu döndürmektedir. 



*/