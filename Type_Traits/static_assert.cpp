/*

https://en.cppreference.com/w/cpp/language/static_assert

STATIC_ASSERT
-------------
Asertion         : Programın derleme veya çalışma zamanında bir durumun programlama hatalarının bulunması için doğrulama.
Dynamic Asertion : Programın çalışma zamanında yapılan doğrulama.
Static Asertion  : Programın derleme zamanında yapılan doğrulama. Bir takım parametreler doğru değilse doğrulama işlemi hiç yapılmasın

static_asser C++11 ile gelen bir keyword. Dolayısıyla kullanmak için herhangi bir header dosyası include etmek gerekmiyor.

static_assert ( bool-constexpr , message )


*/

#include<type_traits>

static_assert(03301 == 1729); // since C++17 the message string is optional

template <class T>
void swap(T& a, T& b) noexcept
{
    static_assert(std::is_copy_constructible_v<T>, "Swap requires copying");
    static_assert(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_assignable_v < T>, "Swap requires nothrow copy/assign");
    auto c = b;
    b = a;
    a = c;
}

template <class T>
struct data_structure {
    static_assert(std::is_default_constructible_v<T>, "Data structure requires default-constructible elements");
};

class Noctor
{
public:
    Noctor() = delete;
};

class Nocopy
{
public:
    Nocopy() = default;
    Nocopy(const Nocopy& other) = delete;
};


int main()
{
    
    data_structure<Noctor> nctor;
    Nocopy a, b;
    swap(a, b);
}
