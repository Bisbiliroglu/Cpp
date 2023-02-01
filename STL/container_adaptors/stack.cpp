/*
STACK
-----
Son girenin ilk çıktığı veri yapısı (LIFO)

template<
    class T,
    class Container = std::deque<T>
> class stack;

stack içerisinde protected olarka container class member olarak bulunaktadır. Bu sayede stackten kalıtım yoluyla geliştirici kendi stack sınıfını oluşturuabilir.

push fonksiyonu veri eklemek için kullanılıyor.
size fonksiyonu tutulan öge sayısına erişmek için kullanılıyor.
pop fonksiyonu son alınan veriyi stackten çıkartmak için kullanılıyor.
top fonksiyonu son eklenen veriyi almak için kullanılıyor. (remove etmiyor)

initializer list ctor ve C++ 23 e kadar iteratör parametreli ctor yok. Ancak stack'in kullandığı container için (default dequeue) parametresi alan bir ctoru var. 
swap iki ögeyi swap ediyor. 
*/

#include <stack>
#include <iostream>
#include<vector>

bool parenthesisChecker(std::string text)
{
    std::stack<int> st;

    const std::vector<std::pair<char,char>> paranthesis
    {
        {'(',')'},
        {'[',']'},
        {'{','}'},
        {'<','>'}
    };

    for(auto & ch : text)
    {
        for(auto & p_ch : paranthesis)
        {
            if(ch == p_ch.second)
            {
                if(st.size() == 0)
                {
                    return false;
                }
                else if (st.top() == p_ch.first && ch == p_ch.second)
                {
                    st.pop();
                }

            }
            else if (ch == p_ch.first)
            {
                st.push(ch);
            }            
        }
    }

    if(st.size() > 0)
        return false;
    return true;
}


int main()
{
    std::stack<int> st;

    //std::cout << "size: " << st.size() << " top: " << st.top() << '\n';


    for (int i = 0; i < 100; i++)
    {
        st.push(i);
    }

    std::cout << "size: " << st.size() << " top: " << st.top() << '\n';

    for (int i = 0; i < 50; i++)
    {
        st.pop();
    }
    std::cout << "size: " << st.size() << " top: " << st.top() << '\n';
    /*
    OUTPUT
    ------
    size: 100 top: 99
    size: 50 top: 49
    */

   auto check1  = parenthesisChecker("testtext");
   auto check2  = parenthesisChecker("t{e(s[tt<>e]x)t}");
   auto check3  = parenthesisChecker("t{e(s[tt<>e]xt}");

   std::cout<<std::boolalpha<<"check1:  "<<check1<<" check2: "<<check2<<" check3: "<<check3<<"\n";
    //check1:  true check2: true check3: false


}