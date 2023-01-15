/*
Dequeue (Double ended queue)
========

chunk
-------
dequeue işlemlerindeki bellek blokları. 


Hem baştan hem de sondan ekleme işlemlerinde amortized time'da, indeks ile erişimlerde constant time kompleksliğe sahip.
vectorün aksine tek bir ardışık bellek alanına ihtiyaç duymuyor. 

reallocation yok.Dolayısıyla vectorün re-allocationdan kaçınamadığı durumlarda kullanmak mantıklı olabilir.

stack ve queue default template argument olarak dequeue kullanıyor.

dequueu iteratörleri random access iteratörlerdir. 

vectorün interface'i iledequeue interface'i hemen hemen aynı. sadece re-allocation içeren kısımlar farklı.


+--------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                                  |
|                                                           std::dequeue Constructors                                                               |
|                                                                                                                                                  |
+==============================+=======================+===========================================================================================+
| Constructor                  | Name                  | Explanation                                                                               |
| ---------------------------- | --------------------- | ----------------------------------------------------------                                |
| dequeue<Elem> c              | Default constructor   | Creates an empty dequeue without any elements                                              |
| dequeue<Elem> c(c2)          | Copy constructor      | Creates a new dequeue as a copy of c2 (all elements are copied)                            |
| dequeue<Elem> c = c2         | Copy assignment       | Creates a new dequeue as a copy of c2 (all elements are copied)                            |
| dequeue<Elem> c(rv)          | Move constructor      | Creates a new dequeue, taking the content of the rvalue rv (since C++11)                   |
| dequeue<Elem> c = rv         | Move assignment 	   | Creates a new dequeue, taking the content of the rvalue rv (since C++11)                   |
| dequeue<Elem> c(n)           |                       | Creates a dequeue with n elements created by the default constructor                       |
| dequeue<Elem> c(n,elem)      |                       | Creates a dequeue initialized with n copies of element elem                                |
| dequeue<Elem> c(beg,end)     |                       | Creates a dequeue initialized with the elements of the range[beg,end)                      |
| dequeue<Elem> c(initlist)    |                       | Creates a dequeue initialized with the elements of initializer list initlist (since C++11) |
| dequeue<Elem> c = initlist   |                       | Creates a dequeue initialized with the elements of initializer list initlist (since C++11) |
| c.~dequeue()                 | Destructor            | Destroys all elements and frees the memory                                                |
+------------------------------+-----------------------+-------------------------------------------------------------------------------------------+



+===============================================================================================================================================================================================================================+
|                                                  std::dequeue Inserting, removing and assign elements                                                                                                                                  |
+=============================+=================================================================================================================================================================================================+
| Function                    | Explanation                                                                                                                                                                                     |
| --------------------------- | --------------------------------------                                                                                                                                                          |
| c.push_back(elem)           | Appends a copy of elem at the end   
| c.push_fron(elem)           | Appends a copy of elem at the begin                                                                                                                                                               |
| c.pop_back()                | Removes the last element (does not return it)                                                                                                                                                   |
| c.pop_front()               | Removes the first element (does not return it)                                                                                                                                                   |
| c.insert(pos,elem)          | Inserts a copy of elem before iterator position pos and returns the position of the new element                                                                                                 |
| c.insert(pos,n,elem)        | Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)                                                     |
| c.insert(pos,beg,end)       | Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first newelement (or pos if there is no new element)                         |
| c.insert(pos,initlist)      | Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element, since C++11) |
| c.emplace(pos,args...)      | Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)                                                       |
| c.emplace_back(args...)     | Appends a copy of an element initialized with args at the end (returns nothing, since C++11)                                                                                                    |
| c.emplace_front(args...)    | Appends a copy of an element initialized with args at the begin (returns nothing, since C++11)                                                                                                    |
| c.erase(pos)                | Removes the element at iterator position pos and returns the position of the next element                                                                                                       |
| c.erase(beg,end)            | Removes all elements of the range [beg,end) and returns the position of the next element                                                                                                        |
| c.resize(num)               | Changes the number of elements to num (if size() grows new elements are created by their default constructor)                                                                                   |
| c.resize(num,elem)          | Changes the number of elements to num (if size() grows new elements are copies of elem)                                                                                                          |
| c.clear()                   | Removes all elements (empties the container)   
| c.assign(initlist)          | Assign a copy of all elements of the initializer list initlist                                                                                                               |
| c.assign(n,elem)            | Assigns n copies of element elem                                                                                                              
| c.assign(beg,end)           | Assigns the elements of the range [beg,end)                                                                                                              
+-----------------------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

shrink_to_fit fonksiyonu: chunkları geri vermek için kullanılıyor. 

*/