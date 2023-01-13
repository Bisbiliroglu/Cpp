/*
HEAP ALGORITHMS
===============
hep her düğümün çocuklarndan büyük olduğu binary tree şeklinde bir veri yapısıdır.
Heap'in kullanıldığı en önemli yer öncelik kuyruğudur.

make_heap
----------
vectorel bir veri yapısını heap haline getiriyor. default olarak max heap üretir.
lineer karmaşıklıktadır. (O(n))

sentaks
-------
template< class RandomIt, class Compare >
constexpr void make_heap( RandomIt first, RandomIt last, Compare comp = less);



pop_heap
--------
heapten çıkarılacak veriyi en sonra getirir. pop_back ile bu veri alınabilir.

sentaks
------
template< class RandomIt, class Compare >
constexpr void pop_heap( RandomIt first, RandomIt last, Compare comp = less );


push_heap
---------
heap'e veri eklemek için kullanılır. push heap yapmak için vectore push_back yapmak gerekir.

sentaks
------
template< class RandomIt, class Compare >
constexpr void push_heap( RandomIt first, RandomIt last, Compare comp = less );



sort_heap
--------
heap sıralamaya yarar

sentaks
-------
template< class RandomIt, class Compare >
constexpr void sort_heap( RandomIt first, RandomIt last, Compare comp );


is_heap
-------
girlen container'ın heap olup olmadığını döndürür.

sentaks
-------
template< class RandomIt, class Compare >
constexpr bool is_heap( RandomIt first, RandomIt last, Compare comp );


is_heap_until
--------------
heap durumunu bozan ögenin indeksini döndürür. Heap olan vontainerlarda end konumunu döndürür.

sentaks
--------

template< class RandomIt, class Compare >
constexpr RandomIt is_heap_until( RandomIt first, RandomIt last, Compare comp );

*/

#include<iostream>
#include<algorithm>
#include<vector>

template <typename T>
void printContainer(std::string containerName, const T& container)
{
    std::cout << containerName << ": ";
    for (const auto& item : container)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";
}


int main()
{
    {
        std::vector<int> ivec = { 17, 14, 26, 90,20,1,5,3,7,16,75,112 };
        printContainer("ivec", ivec);
        std::make_heap(ivec.begin(), ivec.end());
        printContainer("ivec", ivec);
        /*
        OUTPUT
        ------
        ivec: 17 14 26 90 20 1 5 3 7 16 75 112
        ivec: 112 90 26 14 75 17 5 3 7 16 20 1

                 112
            90        26
          14   75   17  5
        23 7 16 20 1
        */

        std::pop_heap(ivec.begin(), ivec.end());
        printContainer("ivec", ivec);
        //ivec: 90 75 26 14 20 17 5 3 7 16 1 112 


    }

    {
        std::vector<int> ivec = { 17, 14, 26, 90,20,1,5,3,7,16,75,112 };
        printContainer("ivec", ivec);
        std::make_heap(ivec.begin(), ivec.end());
        printContainer("ivec (after make heap)", ivec);
        while (!ivec.empty())
        {
            std::pop_heap(ivec.begin(), ivec.end());
            std::cout << "ivec.back : " << ivec.back() << "\n";
            ivec.pop_back();
        }
        /*
        OUTPUT
        ------
        ivec: 17 14 26 90 20 1 5 3 7 16 75 112
        ivec (after make heap): 112 90 26 14 75 17 5 3 7 16 20 1
        ivec.back : 112
        ivec.back : 90
        ivec.back : 75
        ivec.back : 26
        ivec.back : 20
        ivec.back : 17
        ivec.back : 16
        ivec.back : 14
        ivec.back : 7
        ivec.back : 5
        ivec.back : 3
        ivec.back : 1
        */
    }


    {
        std::vector<int> ivec = { 17, 14, 26, 90,20,1,5,3,7,16,75,112 };
        printContainer("ivec", ivec);
        std::make_heap(ivec.begin(), ivec.end(), std::greater{});
        printContainer("ivec (after make heap)", ivec);
        while (!ivec.empty())
        {
            std::pop_heap(ivec.begin(), ivec.end(), std::greater{});
            std::cout << "ivec.back : " << ivec.back() << "\n";
            ivec.pop_back();
        }
        /*
        OUTPUT
        ------
        ivec: 17 14 26 90 20 1 5 3 7 16 75 112
        ivec (after make heap): 1 3 5 7 16 26 17 90 14 20 75 112
        ivec.back : 1
        ivec.back : 3
        ivec.back : 5
        ivec.back : 7
        ivec.back : 14
        ivec.back : 16
        ivec.back : 17
        ivec.back : 20
        ivec.back : 26
        ivec.back : 75
        ivec.back : 90
        ivec.back : 112
        */
    }

    {
        std::vector<int> ivec = { 17, 14, 26, 90,20,1,5,3,7,16,75,112 };
        printContainer("ivec", ivec);
        std::make_heap(ivec.begin(), ivec.end());
        printContainer("ivec (after make heap)", ivec);
        ivec.push_back(20);
        std::push_heap(ivec.begin(), ivec.end());
        printContainer("ivec (after 20 pushed)", ivec);
        /*
        OUTPUT
        -----
        ivec: 17 14 26 90 20 1 5 3 7 16 75 112
        ivec (after make heap): 112 90 26 14 75 17 5 3 7 16 20 1
        ivec (after 20 pushed): 112 90 26 14 75 20 5 3 7 16 20 1 17
        */
    }



    {
        std::vector<int> ivec = { 17, 14, 26, 90,20,1,5,3,7,16,75,112 };
        printContainer("ivec", ivec);
        std::make_heap(ivec.begin(), ivec.end());
        printContainer("ivec (after make heap)", ivec);
        sort_heap(ivec.begin(), ivec.end());
        printContainer("ivec (after sort heap)", ivec);
        /*
        OUTPUT
        ------
        ivec: 17 14 26 90 20 1 5 3 7 16 75 112
        ivec (after make heap): 112 90 26 14 75 17 5 3 7 16 20 1
        ivec (after sort heap): 1 3 5 7 14 16 17 20 26 75 90 112
         */

    }

    return 0;
}