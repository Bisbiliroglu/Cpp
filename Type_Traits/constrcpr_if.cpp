/*

constexpr if (static if)(C++ 17)
---------------------------------
Normal if içinde koşul compile time'da değil runtime'da kontrol ediliyor. 

compile time zamanında koşul kontrol edildiği için doğru durumda doğru kısımda kod derlenir yanlış ise yanlış kısımda kod derleniyor. 
diğer kısımdaki kod hiç derlenmiyor dolayısıyla tür için yanlışlık varsa derleyici herhangi bir hata vermiyor. 

if constexpr için redundant else olmuyor. Çünkü else olup olmaması derleme seçeneklerini değiştiriyor. 


*/

#include <iostream>
#include<type_traits>

template<typename T>
void foo(T x)
{
    if constexpr (std::is_pointer_v<T>)
    {
        std::cout<<"pointer type\n";
    }
    else
    {
        std::cout<<"not pointer type\n"; 

    }
}

template<typename T>
auto get_value(T x)
{
    if constexpr (std::is_pointer_v<T>)
    {
        return *x;
    }
    else
    {
        return x;
    }

}




int main()
{
    int a = 5;
    int* b = &a;

    foo(a);
    foo(b);
    /*
    OUTPUT
    ------
    not pointer type
    pointer type
    */


   std::cout<<"get_value(a): "<<get_value(a)<<" get_value(b): "<<get_value(b)<<"\n";
   //get_value(a): 5 get_value(b): 5

}