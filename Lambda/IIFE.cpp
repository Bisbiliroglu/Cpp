/*
IIFE
----

Immediately Invoked Function Expression

Lambdanın bulundğu yerde doprudan fonksiyon çağrısı işlemini gerçekleştirmektedir. 

Bir hesaplama gerektiren ilklendirme işleminde lambdanın bulunduğu yerde doğrudan fonksiyon çağırsı kullanılabilir.
*/

#include<iostream>


int main()
{

    int x = 13 , y = 14;

    const double z = [](int a, int b){
    int x = a*a + b*b;
    int y  = a* a* a -1;
    int z = b*b*b -3;
    return 0.965 * (x+y+z);
    }(x,y);

    std::cout<<"z: "<<z<<"\n";
    //z: 5116.43

    return 0;
}