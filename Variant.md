# Variant

[std::variant - cppreference.com](https://en.cppreference.com/w/cpp/utility/variant)

**`std::variant`**, C++17'de standart kütüphaneye eklenen bir sınıftır ve birden fazla türdeki verileri tek bir bellek alanında saklamak için kullanılır. Yani, **`std::variant`** aynı anda birden fazla türde değerleri tutabilir. Bu işlemi yapmak için **`std::variant`** nesnesi iki farklı bellek alanı tutar. Bunlardan bir tanesi `**std::variant**`'ın tuttuğu nesnenin bulunduğu bellek alanı. Diğeri ise tutulan bu nesnenin indeksinin tutulduğu bellek alanı. Bu yüzden sizeof(variant) içerisinde alternatiflerinden en büyük boyutlu obje + 4 (indeks) şeklinde çıkacaktır. 

Bu sınıf, birleşim türü olarak da bilinir, çünkü birden fazla farklı türün birleştirilmesine izin verir. Örneğin, bir **`std::variant<int, double, std::string>`** nesnesi, bir tamsayı, bir ondalık sayı veya bir dize olabilir.

**`std::variant`**, kullanıcılara, **`if-else`** veya **`switch`** blokları gibi program kontrol yapılarına ihtiyaç duymadan, farklı türlerdeki verileri depolama ve kullanma esnekliği sunar. Ayrıca, verilerin yanlış türde atanmasını önlemek için statik tür denetimi yapar.

```cpp
#include <iostream>
#include <variant>
#include <string>

int main() {
  std::variant<std::string, int, float> my_variant;
  my_variant = "Elma";
  std::cout << "Degeri: " << std::get<std::string>(my_variant) << std::endl;
  my_variant = 12;
  std::cout << "Degeri: " << std::get<int>(my_variant) << std::endl;
  my_variant = 3.14f;
  std::cout << "Degeri: " << std::get<float>(my_variant) << std::endl;

  return 0;
}

/*
OUTPUT:
Degeri: Elma
Degeri: 12
Degeri: 3.14

*/
```

default constuct edilmiş bir **`std::variant`** nesnesi her zaman ilk alternatifini tutar. Tutulan bu 0 indeksli alternatif ise  initialize edilir. 

**`std::variant`** constructor’ına  alternatiflerinin constructorlarına giden argümanlar kullanılarak construct edilemez. 

### index fonksiyonu

**`std::variant`** sınıfının **`index()`** üye fonksiyonu, şu an seçilmiş olan alternatifin indeksini döndürür. Alternatiflerin indeksi, türlerin belirtilme sırasına göre 0'dan başlayarak artar.

Örneğin, aşağıdaki kod **`std::variant`** sınıfının **`index()`** fonksiyonunu kullanarak, **`myVar`** değişkenindeki şu anki alternatifin indeksini belirler:

```cpp
#include <variant>
#include <iostream>
#include <string>

int main() {
  std::variant<int, std::string> myVar = "Hello World!";
  
  if (myVar.index() == 0) {
    std::cout << "myVar is an int with value " << std::get<0>(myVar) << std::endl;
  } else {
    std::cout << "myVar is a string with value " << std::get<1>(myVar) << std::endl;
  }
  
  return 0;
}

/*
OUTPUT:
myVar is a string with value Hello World!
*/
```

### get fonksiyonu

`std::variant`'ın `get` fonksiyonu, `std::variant` içinde saklanan değeri almak için kullanılır. `get` fonksiyonu, sabit referansını ve bir indeks değeri veya tür belirteci şablon argümanı olarak alır. İstenen tür veya indeks, `std::variant`'ın şablon argümanları arasında olmalıdır.

`get` fonksiyonu kullanımında, belirtilen tür veya indeks `std::variant` içindeki tür ile eşleşiyorsa, `std::variant`'ın içindeki değer get fonksiyonu ile referans olarak geri döndürülür. Aksi takdirde, `std::bad_variant_access` exception throw edilir.

`get` fonksiyonunun iki kullanım çeşidi vardır: indeks veya tür belirteci şablon argümanı kullanarak çağırma.

**İndeksle getirme:**

Bu kullanım çeşidinde, `std::variant`'ın türlerinin indeks numaraları kullanılır. Bu indeks numarası 0'dan başlar.

```cpp
#include <variant>
#include <iostream>

int main() {
    std::variant<int, double, std::string> my_var = 3.14;

    std::cout << "Index: " << my_var.index() << '\n'; // 1

    double val = std::get<1>(my_var);
    std::cout << "Value: " << val << '\n'; // 3.14

    return 0;
}

/*
OUTPUT:
Index: 1
Value: 3.14
*/
```

**Tür belirteci şablon argümanı kullanarak getirme:**

Bu kullanım çeşidinde, `std::variant`'ın türleri şablon argümanı olarak belirtilir.

```cpp
#include <variant>
#include <iostream>

int main() {
    std::variant<int, double, std::string> my_var = "hello world";

    std::cout << "Index: " << my_var.index() << '\n'; // 2

    std::string str = std::get<std::string>(my_var);
    std::cout << "Value: " << str << '\n'; // "hello world"

    return 0;
}

/*
OUTPUT:
Index: 2
Value: hello world
*/
```

### holds_alternative

[std::holds_alternative - cppreference.com](https://en.cppreference.com/w/cpp/utility/variant/holds_alternative)

`std::variant` sınıfının `holds_alternatives` üye fonksiyonu, içinde belirtilen alternatif türlerden birini içerip içermediğini kontrol etmek için kullanılır. Fonksiyon, bir `bool` değer döndürür; `true` sonucu, `std::variant` nesnesinin  alternatif değer içerdiği, `false` sonucu ise `std::variant` nesnesinin  alternatif değer içermediği anlamına gelir.

```cpp
#include <variant>
#include <string>
#include <iostream>
int main()
{
    std::variant<int, std::string> v = "abc";
    std::cout << std::boolalpha
              << "variant holds int? "
              << std::holds_alternative<int>(v) << '\n'
              << "variant holds string? "
              << std::holds_alternative<std::string>(v) << '\n';
}

/*
OUTPUT:
variant holds int? false
variant holds string? true
*/

```

### in_place_index ve in_place_type

std::variant’ nesnesi oluştururken, std::variant nesnesinin tutacağı alternatif için constructor çağrılması için std::in_place_index ve std::in_place_type kullanılabilir. std::in_place_index alternatifi tutulan index için, std::in_place_type ise tutulan alternatif type için kullanılır.

```cpp
// https://github.com/necatiergin/cpp-kursu-kodlar/blob/main/2930_VARIANT/basic/in_place_type.cpp

#include <variant>
#include <complex>
#include <iostream>

int main()
{
	using namespace std;
	//variant<complex<double>, char, int> v1{ 3.0, 4.0 }; // gecersiz
	//variant<complex<double>> v2{ {3.0, 4.0} }; // ERROR
	variant<string, complex<double>, char, int> v11{in_place_type<complex<double>>, 3.0, 4.0 };
	variant<string, complex<double>, char, int> v12{in_place_index<1>, 3.0, 4.0 };
	
	cout << get<1>(v11) << '\n';
	cout << get<complex<double>>(v12) << '\n';

}

/*
OUTPUT:
(3,4)
(3,4)
*/
```

### get_if

get fonksiyonuna tutulan indeks haricinde yanlış indeks verilirse exception throw ediyor. get_if fonksiyonu pointer döndürüyor. eğer tutulan alternatif dışında başka bir alternatif ile get_if fonksiyonu çağrılırsa nullptr döndürülüyor. 

**`std::variant`**'ın **`get_if`** üye fonksiyonu, belirli bir alternatif türünün değerini, güvenli bir şekilde erişmek veya kontrol etmek için kullanılır. Bu fonksiyon, belirtilen alternatif türünün var olup olmadığını kontrol eder ve varsa, ilgili değeri bir pointer olarak döndürür. Eğer alternatif tür varsa işaretçi, yoksa **`nullptr`** döner. 

`get` fonksiyonu,**`get_if`**  fonksiyonundan farklı olarak belirtilen tür veya indeks `**std::variant**` içindeki tür ile eşleşiyorsa alternatifi referans olarak geri döndürülür. Aksi takdirde, `**std::bad_variant_access**` exception throw edilir. **`get_if`** fonksiyonu exception throw etmez.

```cpp
#include <variant>
#include <iostream>

int main() {
    std::variant<int, double, std::string> var = 3.14;

    if (auto* value = std::get_if<double>(&var)) {
        std::cout << "Double value: " << *value << std::endl;
    } else {
        std::cout << "Not a double value!" << std::endl;
    }

    return 0;
}

//OUTPUT: Double value: 3.14
```

### visit

[std::visit - cppreference.com](https://en.cppreference.com/w/cpp/utility/variant/visit)

`std::Visit` fonksiyonu, C++17 standardında tanımlanan bir fonksiyon şablonudur. Bu fonksiyon şablonu, bir dizi veri yapısını veya veri yapılarını dolaşarak her bir eleman üzerinde belirli bir işlemi gerçekleştirmek için kullanılır. `std::Visit`, C++ standart kütüphanesinin `<variant>` başlık dosyasında bulunan `std::variant` veya `std::variant` benzeri veri yapılarıyla birlikte kullanılmak üzere tasarlanmıştır.

`std::Visit` fonksiyonu, verilen işlev nesnesini, `std::variant` veya benzeri bir veri yapısı içindeki mevcut alternatif türüyle uyumlu olan değerler üzerinde çağırmak için kullanılır. Bu fonksiyon şablonu, `std::variant`'ın alternatif türlerini dolaşırken doğru işlevi seçmek için function overload kullanır.

`std::Visit` işlevinin genel kullanımı şu şekildedir:

```cpp
std::visit(visitor, var);

```

Burada `visitor`, her bir alternatif türü için uygun işlemi gerçekleştiren fonksiyon nesnesini temsil eder. `var`, `std::variant` veya benzeri bir veri yapısıdır ve dolaşılacak veriyi içerir. Bu nesne bir callable nesnedir yani “()” operatörü implemente edilmiştir. 

```cpp
#include <variant>
#include <iostream>
#include <typeinfo>

struct Visitor
{
    template <typename T>
    void operator()(const T& value) const {
        std::cout << "Type: " << typeid(T).name() << "Value: " << value << "\n";
    }
    
};

int main()
{
    std::variant<char, int, double> var = 'a';
    Visitor visitor;
    std::visit(visitor, var);
    var = 123;
    std::visit(visitor, var);
    var = 4.7;
    std::visit(visitor, var);
}

/*
OUTPUT:
Type: cValue: a
Type: iValue: 123
Type: dValue: 4.7
*/
```

```cpp
//https://github.com/necatiergin/cpp-kursu-kodlar/blob/main/2930_VARIANT/visit/visit_01.cpp
#include <variant>
#include <iostream>

int main()
{
    std::variant<char, int, double> var = 'a';
    const auto f{ [](auto x) { std::cout << x << '\n'; } };
    std::visit(f, var);
    var = 123;
    std::visit(f, var);
    var = 4.7;
    std::visit(f, var);
}

/*
OUTPUT:
a
123
4.7
*/
```

### Variant ve Polymorphism

Variant kullanımı polymorphism için bir alternatif olarak kullanılabilir. 

**Standart Kalırım Örneği:**

```cpp
#include <iostream>

class Pet
{
    public:
    virtual ~Pet() = default;
    virtual void sound() = 0;
};

class Dog : public Pet
{
    public:
    virtual void sound() override
    {
        std::cout<< "Hav Hav\n";
    }
};

class Cat : public Pet
{
    public:
    virtual void sound() override
    {
        std::cout<< "Miyav Miyav\n";
    }
};

class Bird : public Pet
{
    public:
    virtual void sound() override
    {
        std::cout<< "Cik Cik\n";
    }
};

void pet_sound(Pet & pet)
{
    pet.sound();
}

int main()
{
    Dog pet1;
    Cat pet2;
    Bird pet3;

    pet_sound(pet1);
    pet_sound(pet2);
    pet_sound(pet3);
}

/*
Output:
Hav Hav
Miyav Miyav
Cik Cik
*/
```

**Variant alternatifi**

```cpp
#include <variant>
#include <iostream>

class Dog 
{
    public:
     void sound() const
    {
        std::cout<< "Hav Hav\n";
    }
};

class Cat 
{
    public:
     void sound() const
    {
        std::cout<< "Miyav Miyav\n";
    }
};

class Bird 
{
    public:
     void sound() const
    {
        std::cout<< "Cik Cik\n";
    }
};

using Pet = std::variant<Dog, Cat, Bird>;

struct PetVisitor
{
    template <typename T>
    void operator()(const T& value) const {
        value.sound();
    }
};

int main()
{
    Pet pet;
    PetVisitor petVisitor;

    Dog pet1;
    Cat pet2;
    Bird pet3;
    
    pet = pet1;
    std::visit(petVisitor, pet);
    
    pet = pet2;
    std::visit(petVisitor, pet);
    
    pet = pet3;
    std::visit(petVisitor, pet);

}

/*
Output:
Hav Hav
Miyav Miyav
Cik Cik
*/
```

### monostate

**`std::monostate`**, C++17 standardıyla birlikte tanıtılan bir sınıftır. Bu sınıf, boş durumu temsil etmek için kullanılır. `**std::variant**` nesnesinde boş bir alternatif istendiği durumlarda kullanılabilir. Ayrıca default ctoru olmayan sınıfların variant içerisinde kullanılması durumda hata ile karşılaşmamak için kullanılabilir. Bu kullanım içinde monostate nesnesinin `**std::variant**` nesnesinin 0. indeksi altında tanımlanması gerekmektedir. 

```cpp
//https://github.com/necatiergin/cpp-kursu-kodlar/blob/main/2930_VARIANT/basic/mono_state_01.cpp

// std::monostate

#include <variant>
#include <iostream>

class Data {
public:
	Data(int x) : mx{ x } {}
private:
	int mx;
};

int main()
{
	using namespace std;

	//variant<Data, int, double> v1;  //error: class Data has no default cto
	variant<monostate, Data, int, double> v2; //valid

	cout << "index = " << v2.index() << '\n';  // 0

	if (holds_alternative<std::monostate>(v2))
		cout << "empty (monostate)\n";
	else
		cout << "not empty\n";

	if (get_if<std::monostate>(&v2))
		cout << "empty (monostate)\n";
	else
		std::cout << "not empty\n";

	v2 = Data{ 13 };
	cout << "index = " << v2.index() << '\n';
	v2 = 23;
	cout << "index = " << v2.index() << '\n';
	v2 = 4.5;
	cout << "index = " << v2.index() << '\n';
	v2 = std::monostate{};
	cout << "index = " << v2.index() << "\n";
	v2 = {};
	cout << "index = " << v2.index() << "\n";
}

/*
OUTPUT:

index = 0
empty (monostate)
empty (monostate)
index = 1
index = 2
index = 3
index = 0
index = 0

*/
```
