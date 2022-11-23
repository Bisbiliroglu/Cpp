/*
Function try block ile tüm function için try bloğuna alınabilir
Bunun için function scope curly bracket ({) öncesi try bloğu ardından catch yazmak gerekir
Fonksiyon parametresine hem try hem catch içinden ulaşılabilir
hem try hem catch içinden return yapılabilir.

Bir constructor function try blok içerisine alınırsa (bkz. function_try_block.cpp) memberlardan gönderilen hataları yakalayabilir.
function try blok içerisindeki constructor hata yakalnırsa otomatik rethrow ediliyor. 



*/

#include <iostream>
#include <stdexcept>


int func(int x)
try {
    throw 1;

    return x;
}
catch(int e)
{
    x=5;
    std::cout<<"Exception caught for int x = "<<x<<"\n";
    return -1;

}
catch (double e)
{
    x=4;
    std::cout<<"Exception caught for double x = "<<x<<"\n";
    return -2;
}


int main()
{

int a = func(5);

std::cout <<"a = "<<a<<"\n";

return 0;

}

/*
OUTPUT
_______________________
Exception caught for int x = 5
a = -1


*/