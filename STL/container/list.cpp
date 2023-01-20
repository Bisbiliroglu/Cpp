/*
LIST
----
double linkedlist veri yapısını implemente ediyor. 
her bir ögesinde bir node tutuyor. 
her node veriyi, öncekin ve sonraki nodun adreslerini tutuyor. 
her bir node dinamik olarak allocate ediliyor. 
Tipik olarak son node'un next pointerı nullptr oluyor. 

Dezavantajları
--------------
- Algoritmaların karmaşıklığı düşük olmasına rağmen, nodeların bellek içerisinde farklı yerlerde olması (caching frendy değil) daha düşük bir performansa neden olabiliyor. 
- Bağlı listede data haricinde iki pointer tuutlduğu için ekstra alan allocate ediliyor. örnek int tutulmak istenirse sizeof(int) + 2*sizeof(pointer) kadar alan tutulması gerekiyor.
  Ancak vector içerisinde sadece sizeof(int) tutuluyor. Üstelik her bir allocation için ekstra allocate edilen header kısmı'da ekstra yer  kaplıyor.
-Index ile erişimde vectöre göre çok dezavantajlı. Lineer complexity'e sahip. (vector constant time)

Avantajları
-----------
- Fragmante olmuş belleğe daha uygunlar. 
- konumu bilinen herhangi bir yerden ekleme ve silme yapmak constant time.
- swap yapan algoritmalar (bir çok algoritma swap yapmakta) için vector ve dequeue göre daha performanslı. Çünkü tüm bellek bloğu swwap edilmesi yerine sadece node'ta tutulan pointerlar swap ediliyor. 

list için iteratör kategorisi bidirectional iteratör. Ancak sindle linkedlist veri yapısını tutan forward list forward iteratör kullanmakta.

listin kendi içinde , reverse, unique merge gibi fonksiyonları vardır. 
Her zaman alogirtma fonksiyonlarını çağırmak yerine conteiner fonksiyonun kendi üye algoritmalarını çağırmak daha avantajlı. çünkü konteynerın kendi üyelerine direkt erişebiliyor. algoritma fonksiyonları iteratörler ile erişebiliyor.  

bağlı listede ögeler düğüm şeklinde olduğu için, düğüm bir listeden çıkartılıp başka bir listeye eklemek mümkün. Bu işlemi list içerisinde splice fonksiyonları yapıyor. 


+--------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                                  |
|                                                           std::list Constructors                                                                 |
|                                                                                                                                                  |
+==============================+=======================+===========================================================================================+
| Constructor                  | Name                  | Explanation                                                                               |
| ---------------------------- | --------------------- | ----------------------------------------------------------                                |
| list<Elem> c                 | Default constructor   | Creates an empty list without any elements                                                |
| list<Elem> c(c2)             | Copy constructor      | Creates a new list as a copy of c2 (all elements are copied)                              |
| list<Elem> c = c2            | Copy assignment       | Creates a new list as a copy of c2 (all elements are copied)                              |
| list<Elem> c(rv)             | Move constructor      | Creates a new list, taking the content of the rvalue rv (since C++11)                     |
| list<Elem> c = rv            | Move assignment 	   | Creates a new list, taking the content of the rvalue rv (since C++11)                     |
| list<Elem> c(n)              |                       | Creates a list with n elements created by the default constructor                         |
| list<Elem> c(n,elem)         |                       | Creates a list initialized with n copies of element elem                                  |
| list<Elem> c(beg,end)        |                       | Creates a list initialized with the elements of the range[beg,end)                        | 
| list<Elem> c(initlist)       |                       | Creates a list initialized with the elements of initializer list initlist (since C++11)   |
| list<Elem> c = initlist      |                       | Creates a list initialized with the elements of initializer list initlist (since C++11)   |
| c.~list()                    | Destructor            | Destroys all elements and frees the memory                                                |
+------------------------------+-----------------------+-------------------------------------------------------------------------------------------+



+===============================================================================================================================================================================================================================+
|                                                  std::list Inserting, removing and assign elements                                                                                                                           |
+=============================+=================================================================================================================================================================================================+
| Function                    | Explanation                                                                                                                                                                                     |
| --------------------------- | --------------------------------------                                                                                                                                                          |
| c.push_back(elem)           | Appends a copy of elem at the end                                                                                                                                                               |
| c.push_fron(elem)           | Appends a copy of elem at the begin                                                                                                                                                             |
| c.pop_back()                | Removes the last element (does not return it)                                                                                                                                                   |
| c.pop_front()               | Removes the first element (does not return it)                                                                                                                                                  |
| c.insert(pos,elem)          | Inserts a copy of elem before iterator position pos and returns the position of the new element                                                                                                 |
| c.insert(pos,n,elem)        | Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)                                                     |
| c.insert(pos,beg,end)       | Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first newelement (or pos if there is no new element)                         |
| c.insert(pos,initlist)      | Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element, since C++11) |
| c.emplace(pos,args...)      | Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)                                                       |
| c.emplace_back(args...)     | Appends a copy of an element initialized with args at the end (returns nothing, since C++11)                                                                                                    |
| c.emplace_front(args...)    | Appends a copy of an element initialized with args at the begin (returns nothing, since C++11)                                                                                                  |
| c.erase(pos)                | Removes the element at iterator position pos and returns the position of the next element                                                                                                       |
| c.erase(beg,end)            | Removes all elements of the range [beg,end) and returns the position of the next element                                                                                                        |
| c.resize(num)               | Changes the number of elements to num (if size() grows new elements are created by their default constructor)                                                                                   |
| c.resize(num,elem)          | Changes the number of elements to num (if size() grows new elements are copies of elem)                                                                                                         |
| c.clear()                   | Removes all elements (empties the container)                                                                                                                                                    |
| c.assign(initlist)          | Assign a copy of all elements of the initializer list initlist                                                                                                                                  |
| c.assign(n,elem)            | Assigns n copies of element elem                                                                                                                                                                |
| c.assign(beg,end)           | Assigns the elements of the range [beg,end)                                                                                                                                                     |
| c.remove                    | Remove algorithm member function                                                                                                                                                                |
| c.remove_if                 | Remove_if algorithms member function                                                                                                                                                            |
| c.sort                      | Sort algorithm member function (stable_sort)                                                                                                                                                                 |
| c.merge                     | Merge algorithm member function                                                                                                                                                                 |
| c.splice                    | Transfer a range from source list to destination list                                                                                                                                        |
| c.unique                    | Unique algorithm member function                                                                                                                                                                |
| c.reverse                   | Reverse algorithm member function                                                                                                                                                               |
+-----------------------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


*/