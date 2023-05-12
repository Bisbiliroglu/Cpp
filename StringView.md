# StringView

[std::basic_string_view - cppreference.com](https://en.cppreference.com/w/cpp/string/basic_string_view)

**`std::string_view`** sınıfı, C++17'de standart kütüphaneye eklenmiştir ve bir karakter dizisi verilerinin (std::string, c_str olabilir ve hatta bellekte ardışık tutulan karakterler de olabilir) başka bir yerde saklandığı durumlarda salt erişim için kullanılır.

**`std::string_view`** sınıfı, bir **`std::string`** nesnesi gibi davranır ancak bellekteki bir veriyi doğrudan sahiplenmez. Bunun yerine, bir karakter dizisi veya **`std::string`** nesnesi gibi bir kaynağı referans alır ve bu kaynağın içeriğine bir salt erişim sağlar.

Bu sınıf, bir karakter dizisi üzerinde işlem yapmanız gerektiğinde bellekte yeni bir nesne oluşturmadan, özellikle de bu işlemler sırasında okuma işlemlerinin daha verimli olmasını sağlar. **`std::string_view`**, bir **`std::string`** nesnesine benzer şekilde kullanılabilir ve **`std::string`** nesneleri ile uyumlu olarak kullanılabilir.

| Defined in header https://en.cppreference.com/w/cpp/header/string_view |  |
| --- | --- |
| Type | Definition |
| std::string_view (C++17) | std::basic_string_view<char> |
| std::wstring_view (C++17) | std::basic_string_view<wchar_t> |
| std::u8string_view (C++20) | std::basic_string_view<char8_t> |
| std::u16string_view (C++17) | std::basic_string_view<char16_t> |
| std::u32string_view (C++17) | std::basic_string_view<char32_t> |

**`std::string_view`**kullanılarak, salt okuma amaçlı işlemler için kopyalama işlemini önler. Dolayısıyla performans açısından fayda sağlar. 

**`std::string_view`** sınfının implemantasyonu bir karakter dizinin başlangıcını ve bitişini gösteren iki pointer şeklinde düşünülebilir. Gösterrdiği stringleri bu pointerlar aracılığı ile gösterir.  

`**std::string_view**` nesnesi içerisinde tutulan pointerlar(yazıyı gösteren) dangling hale gelebilir. Bu durum çeşitli hatalara neden olabilir. 

```cpp

#include <iostream>
#include <string_view>
#include <string>

int main() 
{
    using namespace std;
    string str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    
    string_view sv {str};
    
    std::cout << sv <<'\n';
    //OUTPUT Lorem ipsum dolor sit amet, consectetur adipiscing elit.
    
    str[0] = 'Y';
    
    std::cout << sv <<'\n';
    //OUTPUT: Yorem ipsum dolor sit amet, consectetur adipiscing elit.

    str+= "Integer et neque et dolor facilisis suscipit. Aliquam posuere sagittis orci id ultrices. ";
    //Realocation olacagi icin undefined behaovior. dangling pointer
    std::cout << sv <<'\n'; 
    //OUTPUT: ���Z
    return 0;
}
```

```cpp
//https://github.com/necatiergin/cpp-kursu-kodlar/tree/main/0950_STRING_VIEW

#include <string_view>
#include <iostream>
#include <array>

int main()
{
	char str[] = "Bjarne Stroustrup";
	std::string s{ "cpp is the best programming language" };
	std::array<char, 6> ar{ 'n', 'e', 'c', 'a', 't', 'i' };

	std::string_view sv1;
	std::cout << "(sv1.length : " << sv1.length() << ")    |" << sv1 << "|\n";

	std::string_view sv2 = "Necati Ergin";
	std::cout << "(sv2.length : " << sv2.length() << ")   |" << sv2 << "|\n";

	std::string_view sv3{ str, 6 };
	std::cout << "(sv3.length : " << sv2.length() << ")   |" << sv3 << "|\n";

	std::string_view sv4{ s };
	std::cout << "(sv4.length : " << sv4.length() << ")   |" << sv4 << "|\n";

	std::string_view sv5{s.data() + 11, 4 };
	std::cout << "(sv5.length : " << sv5.length() << ")    |" << sv5 << "|\n";

	std::string_view sv6{ar.data(), size(ar) };
	std::cout << "(sv6.length : " << sv6.length() << ")    |" << sv6 << "|\n";

	std::string_view sv7{ str, (str + 3) };
	std::cout << "(sv7.length : " << sv7.length() << ")    |" << sv7 << "|\n";
}

/*
OUTPUT
(sv1.length : 0)    ||
(sv2.length : 12)   |Necati Ergin|
(sv3.length : 12)   |Bjarne|
(sv4.length : 36)   |cpp is the best programming language|
(sv5.length : 4)    |best|
(sv6.length : 6)    |necati|
(sv7.length : 3)    |Bja|

*/
```

### Remove Fonksiyonları

**`remove_prefix`** ve **`remove_suffix`** fonksiyonları, C++'ın **`string_view`** sınıfında bulunan ve bir `**string_view`**  sınıfının gösterdiği yazının, ****başındaki veya sonundaki karakterleri kaldırmak için kullanılan işlevlerdir. Burada kaldırma işlemi pointerların kaydırılması ile yapılır.

**`remove_prefix`** fonksiyonu, **`string_view`**'ın başındaki belirtilen sayıda karakteri kaldırırken, **`remove_suffix`** fonksiyonu sonundaki belirtilen sayıda karakteri kaldırır. Bu fonksiyonlar, orijinal stringi değiştirmezler.

Örneğin, aşağıdaki kod örneği, "Hello, World!" metninin başındaki "Hello, " ifadesini kaldırmak için **`remove_prefix`** fonksiyonunu kullanmaktadır:

```cpp
#include <iostream>
#include <string_view>

int main() {
    std::string_view text = "Hello, World!";
    text.remove_prefix(7); // "Hello, " ifadesini kaldırır
    std::cout << text << '\n'; // "World!" yazdırır
    return 0;
}
```

Benzer şekilde, aşağıdaki kod örneği, "Hello, World!" metninin sonundaki "World!" ifadesini kaldırmak için **`remove_suffix`** fonksiyonunu kullanmaktadır:

```cpp
#include <iostream>
#include <string_view>

int main() {
    std::string_view text = "Hello, World!";
    text.remove_suffix(7); // "World!" ifadesini kaldırır
    std::cout << text << '\n'; // "Hello, " yazdırır
    return 0;
}
```