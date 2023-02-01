/*
QUEUE 
========================
İlk girenin ilk çıktığı veri yapısı (FIFO)

default template argümanı dequeue

queue içerisinde vector kulanılamıyor. Bunun sebebi baştan çıkartma işlemi kulllanılması.


QUEUE
-----
İlk girenin ilk çıktığı veri yapısı (FIFO)
template<
    class T,
    class Container = std::deque<T>
> class queue;

emplace, empty size ve swap fonksiyonları var.





*/


#include <queue>
#include <iostream>

int main()
{
    {
        std::queue<int> q;
        for (int i = 0; i < 100; i++)
        {
            q.push(i);
        }

        std::cout << "kuyruk basi: " << q.front() << "\n";
        std::cout << "kuyruk sonu: " << q.back() << "\n";

        q.front() += 0;
        q.back() += 100;

        std::cout << "kuyruk basi: " << q.front() << "\n";
        std::cout << "kuyruk sonu: " << q.back() << "\n";


        for (int i = 0; i < 50; i++)
        {
            q.pop();
        }
        std::cout << "kuyruk basi: " << q.front() << "\n";
        std::cout << "kuyruk sonu: " << q.back() << "\n";

        /*
        OUTPUT
        ------
        kuyruk basi: 0
        kuyruk sonu: 99
        kuyruk basi: 0
        kuyruk sonu: 199
        kuyruk basi: 50
        kuyruk sonu: 199
        */

    }

}