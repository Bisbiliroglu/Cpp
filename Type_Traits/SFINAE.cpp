/*

https://github.com/necatiergin/cpp-kursu-kodlar/tree/main/0774_SFINAE


SFINAE (Substitution failure is not an error)
---------------------------------------------
Substitution: Template argümanları fonksiyonların yerine sağlanma aşaması.
Substitution aşamsında türlere yönelik olan error hard error şeklinde derleme bitiren error olmamaktadır. Derleyici o fonksiyonu overloadların set içerisinden çıkartılabilir. .
Bu overloading set içerisinden çıkarma işlemi türe göre compile zamanda kod seçme işlemi yapılabilir.
*/

#include <type_traits>
#include <iostream>
#include <vector>

template<typename T, unsigned N>
std::size_t len(T(&)[N])
{
    std::cout << "a";
    return N; //size_type nested type sahip olmayan kodlar için bu alan seçildi
}

template<typename T>
typename T::size_type len(T const& t)
{
    std::cout << "b";
    return t.size(); //size_type nested type sahip olan kodlar için bu alan seçildi
}

/*
template <typename T>
std::enable_if_t<std::is_integral<T>::type, T> func(T t)
{
    std::cout << "func<integral T> " << '\n';
    return t;
}
*/

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> func(T t)
{
    std::cout << "func<integral T> " << '\n';
    return t;
}

int main()
{
    int a[10]{};
    std::vector<int> b(11);
    std::cout << "len(a): " << len(a) << " len(b): " << len(b) << "\n";
    //len(a): a10 len(b): b11

    func(10); //gecerli
    //func(3.14); //error: no matching function for call to 'func' func(3.14); SFINAE out 
}