/*
std::vector
==========

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

*/