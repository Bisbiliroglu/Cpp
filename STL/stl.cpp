/*
https://github.com/umutkotankiran/Cpp/blob/main/29_15_08_2021/main.cpp
https://github.com/umutkotankiran/Cpp/blob/main/32_28_08_2021/main.cpp
https://www.math.colostate.edu/~bangerth/teaching/2006-spring-664/fabien/containers.html
https://www.math.colostate.edu/~bangerth/teaching/2006-spring-664/fabien/algorithms.html


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
std::list			-> doubly linked list (çifte bağlı liste)
std::forward_list	-> (C++ 11 de geldi)  singly linked list (tekli bağlı liste)
std::string			-> Yazı tutuyor.Gördük bunu.Bu da containers.Bunu daha çok STL algoritmalarıyla kullanacağız.
std::array			-> (C++ 11 de geldi) array container. Varlık nedeni C dizilerini sarmalamak.
C arrays

ASSOCIATIVE CONTAINERS
----------------------
İkili arama ağacı
Ekleme işlemi belirli bir konum değil değerle yapılıyor.
İkili arama ağacı veri yapısı kullanılıyor. Değerin ne olduğuna bağlı olarak ekleneceği yer belirleniyor.
Log N karmaşıklığa sahiptir. 

std::set	    -> Sadece anahtar tutuyor.Tamsayıların setini oluşturursak 17 nin sette olup olmadığını sorgulayabiliriz.Bir anahtardan bir tane var. ekleme, arama ve silme O(log(n))
std::multiset	-> Bir anahtardan birden fazla olabilir.Tamsayıların setinde 1 tane 12 olabilir.multisetinde 3,4,5,6 tane 12 olabilir. ekleme, arama ve silme O(log(n))
std::map	    -> Anahtarın değerle eşlendiği veri yapısı.Anahtarla erişiyoruz yine ama anahtar karşılığı bir değere erişiyoruz.Buradakiler pair gibi anahtar değer çifti
std::multimap	-> Bir anahtardan birden fazla olabilir.

Tipik olarak var mı yok mu sorgulaması yapılacaksa set grubu, varsa ona eşlenmiş bilgilere erişmek için map grubu kullanılabilir. 
Arama, ekleme işlemleri için bir karşılaştırma yapılması gerekiyor. ancak bu karşılaştırma == ile yapılmıyor. tipik olarak less (<) kullanılıyor. 
Örnek arama yapmak için karşılaştırma işleminde !(a<b) && !(b<a) kullanılıyor. buna equivalence deniliyor. 

UNORDERED ASSOCIATIVE CONTAINERS
--------------------------------
Diğer dillerdeki adı hash tablosu olan veri yapısını implemente eden sınıflar.
Associative containerslardan farklı olarak constant time karmaşıklığa sahiptirler.

std::unordered_set		    -> (C++ 11 de geldi) Sadece anahtar tutuyor.Bir anahtardan bir tane var.
std::unordered_multiset		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.
std::unordered_map	    	-> (C++ 11 de geldi) Anahtarın değerle eşlendiği veri yapısı.Buradakiler pair gibi anahtar değer çifti
std::unordered_multimap		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.

Not: stack, queue, priority_queue container değil container adaptor olarak geçiyor.

Boost içinde STL'den daha fazla container var. Örnek olarak graph veya binary map verilebilir. 

sequence continerlarda ekleme belirli bir sıra ile yapılıyor. associative continerlarda ise geliştirici eklenecek yeri değil sırayı veriyor. arkada bir karşılaştırma işlemi ypaılarak ekleme yapılıyor. 


Eklene İşlemi
-------------
Normal ekleme işlemlerinde, bir container'a bir öge eklenirken, eklenecek ögenin kendisi değil bir kopyası eklenir. 
Ancak modern C++ ile conteiner'a ekleneecek öge için taşıma semantiği kullanılabiliyor. 
Ancak perfect forwarding kullanılırsa kapta ne taşıma ne kopyalama işlemi yapılmadan conteinera o nesneyi oluşturacak argümanlar gönderilebiliyor. Bu işi yapan fonksiyonlara emplace ismi veriliyor. 



std::vector
-----------
indexi bilinen ögeye erişim sabit sürede yapılabiliyor.
Sondan, ekleme ve çıkarma işlemi sabit sürede yapılabiliyor. 
Vector ögeleri bellek üzerinde sıralı şekilde tutuyor. 
Nesnelerin tutulduğu bellek alanı dinamik olarak allocate ediliyor. Default argüman kullanılınca bu allocation new ile yapılıyor.
Tutulan öge sayısı size, tutulabilecek maksimum öge sayısı ise capacity'dir. Size ile capacity aynı olunca yeni öge almak için tekrar bellek alanı allocate edilir (re-allocation).
Vector içerisinde small buffer optimization yok.
implemantasyonu kabaca 3 pointer içeriyor. İlk pointer, allocate edilen belleğin başlangıcı, ikinci pointer eklenen son ögenin adresini, son pointer ise allocate edilen alanın sonunu tutuyor.s 
reserve fonksiyonu ile kapasite değiştirilebiliyor. Eğer tutulabilecek öge sayısı işlemin başında biliniyorsa bu fonksiyon ile gereksiz re-allocation'dan kaçınılabilir. 
vector sınıfı çoğu senaryo için container ihtiyacını karşılamaktadır. 
Bağlı liste daha düşük karmaşıklığa ship olsa da, cache hit veya cache miss durumları nedeniyle vector çoğu durumda daha performanslı olabiliyor.
Performans gerektiren durumlarda, performansı etikeleyebilecek çok fazla parametre olduğu için en iyisi profiling araçlarını kullanmak. 

template<typname T, typename A = std::allocator<T>>
class vector {

}

//T vectorde tutulacak ögenin türü
//A allocator. Default olarak standard kütüphanenin allocator sınıfı alınıyor. Bu da new operatörünü kullanarak heap üzerinde bellek allocate ediyor. 

vector<bool> partial speciliaziton, yani ikincil bir template kullanılıyor.  


+--------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                                  |
|                                                           std::vector Constructors                                                               |
|                                                                                                                                                  |
+==============================+=======================+===========================================================================================+
| Constructor                  | Name                  | Explanation                                                                               |
| ---------------------------- | --------------------- | ----------------------------------------------------------                                |
| vector<Elem> c               | Default constructor   | Creates an empty vector without any elements                                              |
| vector<Elem> c(c2)           | Copy constructor      | Creates a new vector as a copy of c2 (all elements are copied)                            |
| vector<Elem> c = c2          | Copy assignment       | Creates a new vector as a copy of c2 (all elements are copied)                            |
| vector<Elem> c(rv)           | Move constructor      | Creates a new vector, taking the content of the rvalue rv (since C++11)                   |
| vector<Elem> c = rv          | Move assignment 	   | Creates a new vector, taking the content of the rvalue rv (since C++11)                   |
| vector<Elem> c(n)            |                       | Creates a vector with n elements created by the default constructor                       |
| vector<Elem> c(n,elem)       |                       | Creates a vector initialized with n copies of element elem                                |
| vector<Elem> c(beg,end)      |                       | Creates a vector initialized with the elements of the range[beg,end)                      |
| vector<Elem> c(initlist)     |                       | Creates a vector initialized with the elements of initializer list initlist (since C++11) |
| vector<Elem> c = initlist    |                       | Creates a vector initialized with the elements of initializer list initlist (since C++11) |
| c.~vector()                  | Destructor            | Destroys all elements and frees the memory                                                |
+------------------------------+-----------------------+-------------------------------------------------------------------------------------------+

vectore öğe ekledikçe size değeri artıyor. Size değeri ile capasite değeri eşitlenince re-allocation oluyor. Bu işlem ile size'ın 1.5, 2 katı bir alan tekrar allocate ediliyor. Bu işlem derleyiciye bağlı.
vectoreden öge eksilttikçe size azalıyor ancak kapasite azalmıyor. shrink_to_fit() fonksiyonu ile kapasite size'e eşitlenebilir. Ancak bu fonksiyon da derleyiciye bağlı. Ana akım derleyiciler genelde bu fonksiyon çağrılınca hemen kapasiteyi düşürüyorlar. 

vector içerisinde veriye indeks ile erişmek için [] operatörü veya at() fonksiyonu kullanılabilir. [] kullanılırsa erişilemeyen indeks için exception throw etmez. Ancak at() fonksiyonu kullanılırsa out_of_rang exception throw eder. 
vector içerisindeki ilk ögeye erişmek için front(), son ögeye erişmek için back() fonksiyonu kullanılabilir. 

+===============================================================================================================================================================================================================================+
|                                                  std::vector Inserting, removing and assign elements                                                                                                                                  |
+=============================+=================================================================================================================================================================================================+
| Function                    | Explanation                                                                                                                                                                                     |
| --------------------------- | --------------------------------------                                                                                                                                                          |
| c.push_back(elem)           | Appends a copy of elem at the end                                                                                                                                                               |
| c.pop_back()                | Removes the last element (does not return it)                                                                                                                                                   |
| c.insert(pos,elem)          | Inserts a copy of elem before iterator position pos and returns the position of the new element                                                                                                 |
| c.insert(pos,n,elem)        | Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)                                                     |
| c.insert(pos,beg,end)       | Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first newelement (or pos if there is no new element)                         |
| c.insert(pos,initlist)      | Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element, since C++11) |
| c.emplace(pos,args...)      | Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)                                                       |
| c.emplace_back(args...)     | Appends a copy of an element initialized with args at the end (returns nothing, since C++11)                                                                                                    |
| c.erase(pos)                | Removes the element at iterator position pos and returns the position of the next element                                                                                                       |
| c.erase(beg,end)            | Removes all elements of the range [beg,end) and returns the position of the next element                                                                                                        |
| c.resize(num)               | Changes the number of elements to num (if size() grows new elements are created by their default constructor)                                                                                   |
| c.resize(num,elem)          | Changes the number of elements to num (if size() grows new elements are copies of elem)                                                                                                          |
| c.clear()                   | Removes all elements (empties the container)   
| c.assign(initlist)          | Assign a copy of all elements of the initializer list initlist                                                                                                               |
| c.assign(n,elem)            | Assigns n copies of element elem                                                                                                              
| c.assign(beg,end)           | Assigns the elements of the range [beg,end)                                                                                                              
+-----------------------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

resize fonksiyonu hem öğe silmek, hem de öğe eklemek amacıyla kullanılabilir. 
Eğer tek argüman gönderilirse ve argüman önceki size değerinden daha büyük ise aradaki fark kadar yeni öge eklenir ve bu ögeler value initialize olur. 
Eğer iki argüman girilirse ilk argüman size, ikinci argüman ise eklenen ögelerin değeridir. 
Eğer size, container'ın size değerinden daha düşükse aradaki fark kadar öge silinecektir. resize(0) girilirse tüm ögeler silinecektir. 

insert fonksiyonların hep ilk parametre iteratör. insert fonksiyonlarına girilen posizyon değeri eklenecek elemanın konumunudur. push_back gibi kullanılmak istenirse, end değeri, push_front gibi kullanılmak istenirse begin değeri girilir. 
insert fonksiyonları geri dönüş değeri olarak insert edilen ilk ögenin değerini döndürür. 

vectordeki ilk ögenin adresini elde etmek için data fonksiyonu kulanılabilir. Vector array gibi art arda belekte sıralandığı için C array isteyen C fonksiyonlarına bu değer gnderilebilir.


Emplace Fonksiyonları
---------------------
Container'lara ekleme işlemi yaparken, copy veya move constructor kullanmak yerine, perfect forwarding ile container'da tutulacak nesnenin constructoru için argümanları geçilmesi işlemi. 

vec.pushback(Date{}) // default ctor + move ctor  çağrılıyor
vec.emplace_back(); //default ctor çağrılıyor. 

push_back => emplace_back
push_front => emplace_front
insert => emplace 

çağrılabiliyorsa her zaman emplace fonksiyonlarını çağırmakta fayda var. Emplace fonksiyonları ya aynı maliyete ya da daha az maliyete sahip.

Date mudate; //default ctor

vec.push_back(mydate) //copy ctor
vec.emplace_back(mydate) //copy ctor 

aynı maliyetteler. 


CONTAINER ADAPTORSS
===================
STL kütüphanesinde 3 tane container adaptor bulunmakta
std::stack
std::queue
std::priority_queue

Bu adaptörler bir containerı member olarak alıyorlar ve bu containerı kullanarak farklı veri yapılarını implemente ediyorlar. 
Tüm adaptörler generic olarak implemente edilmiştir. 

STACK 
-----
Son girenin ilk çıktığı veri yapısı (LIFO)

QUEUE
-----
İlk girenin ilk çıktığı veri yapısı (FIFO)

PRIORITY_QUEUE
--------------
Önceliği yüksek olanın ilk başta çıktığı veri yapısı.




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

iter_swap farklı türlerdeki iteratörleri de değiştirebilir. ör bir list ve bir vectorun ögeleri değiştirilebilir.  

back_inster(), fron_insrter ve inserter() fonksiyonları ile oluşturulan iteratörler ile boş conteiner dosyalarına yenş eleman girişi yapılabilir.




ALGORITHMS
=========
Tipik olarak parametreleri iteratörler olan ve containerlar üzerinde işlem yapan fonksiyon şablonları.

Conventions
-----------
 1.) Belirli bir range yazan algoritmalar (ör copy) en son yazdıkları konumadan bir sonraki konumu döndürürler. 
 2.) Parametrelerde kaynak range önce, hedef range sonra olur.
 3.) Arama algoritmaları konum döndürmektedir. Bulursa bulduğu konumu bulamazsa end konumunu döndürmektedir. 
 4.) Alogritmalar girilen iteratörlere göre işlem yaptığı konuma eleman ekleyemez veya eleman silemezler. Zaten iteratörden container'ın kendisine erişelemeyeceği için bu işlem mümkün değildir. 
 5.) Sonunda copy olan algoritmalar, işlemini yaptıkran sonra sonucu başka bir yere kopyalıyor.  



*/