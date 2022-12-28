/*

POSITIVE LAMBDA IDIOM
---------------------
Eğer işaret ooperatoru + kullanılırsa bir dönüşüm gerçekleşir. Burada lambda closure type'ı function pointer olur.

auto f = +[](int a) {return a*a;}; // f function pointer
auto f = [](int a) {return a*a;}; // f bir sınıf türü. 



*/

#include <iostream>

int main()
{

auto f1 = +[](int a) {return a*a;}; // f function pointer
auto f2 = [](int a) {return a*a;}; // f bir sınıf türü. 

std::cout<<"typename f1 : "<<typeid(f1).name()<<"\n";
std::cout<<"typename f2 : "<<typeid(f2).name()<<"\n";

/*
output
------
typename f1 : PFiiE
typename f2 : Z4mainE3$_1


*/


return 0;
}