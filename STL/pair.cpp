/*
İkili veri tutmak için kullanılan veri yapısı
ilk tutulan veri first ile
ikinci tutulan veriye second ile ulaşılıyor. 

kullanılan yapılar value initialize ediliyorlar. 
eğer sınıf türünden veri girişi yapılırsa default constructor çağrılıyor.

SENTAKS
---------------
std::pair<t,u> 
 


*/


#include<iostream>
#include<utility>


template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& pair )
{
    return os<<"pair.first: "<<pair.first<<" pair.second: "<<pair.second<<"\n";
}

int main()
{

std::pair<int,double> p (12,4.5);
std::cout<<"p.first: "<<p.first<<" p.second: "<<p.second<<"\n";
//p.first: 12 p.second: 4.5


//c++ 17 sonrası için CTAD yararlanılabilir.

std::pair q (4.7,4.5);
std::cout<<"q.first: "<<q.first<<" q.second: "<<q.second<<"\n";
//q.first: 4.7 q.second: 4.5


std::pair<int,double> x;
std::cout<<"x.first: "<<x.first<<" x.second: "<<x.second<<"\n";
//x.first: 0 x.second: 0


//pair oluşturmanın bir başka yolu ise make_pair fonksiyonu kullanmak
auto a = std::make_pair(15,"test");
//std::cout<<"a.first: "<<a.first<<" a.second: "<<a.second<<"\n";
//a.first: 15 a.second: test

std::cout<<a;
//pair.first: 15 pair.second: test

std::cout<<std::make_pair(std::make_pair(std::make_pair(4,5),"pair2"),5.6);
/*

pair.first: pair.first: pair.first: 4 pair.second: 5
 pair.second: pair2
 pair.second: 5.6

*/




}
