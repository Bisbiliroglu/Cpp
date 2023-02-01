/*
PRIORITY QUEUE
==============

Önceliği yüksek olanın ilk başta çıktığı veri yapısı. sadece vector ve dequeue container olarak kullanılabiliyor.

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;

arkaplanda heap algoritmalarını kullanıyor.

default olarka less kulanıldığı için default olarka max hesap kullanılıyor. Dolayısıyla değerce büyük olan önceliğe sahip oluyor.
*/




#include <queue>
#include <iostream>

int main()
{
    {
        std::priority_queue<int> pq;

        for (int i = 0; i < 100; i++)
        {
            pq.push(i);
        }
        std::cout << "top: " << pq.top() << "\n";

        for (int i = 0; i < 50; i++)
        {
            pq.pop();
        }
        std::cout << "top: " << pq.top() << "\n";

        /*
        OUTPUT
        -----
        top: 99
        top: 49
        */
    }

        {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        for (int i = 0; i < 100; i++)
        {
            pq.push(i);
        }
        std::cout << "top: " << pq.top() << "\n";

        for (int i = 0; i < 50; i++)
        {
            pq.pop();
        }
        std::cout << "top: " << pq.top() << "\n";

        /*
        OUTPUT
        -----
        top: 0
        top: 50
    */
    }
}