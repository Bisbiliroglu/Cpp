# Optional

[std::optional - cppreference.com](https://en.cppreference.com/w/cpp/utility/optional)

C++ 17 ile birlikte gelen `**std::optional**`, bir nesnenin var olup olmadığını belirlemek için kullanılan bir sınıftır. Özellikle, bir değerin olup olmadığına dair belirsizlik durumlarında kullanılabilir.

 Eğer geri dönüş değeri `**std::optional**` olan bir fonksiyonun, geri dönüş değeri varsa, `**std::optional**` nesnesi değerin kendisini saklar. Eğer fonksiyonun geri dönüş değeri yoksa, `**std::optional**` nesnesi değerin yokluğunu gösterir.

## std::optional Örnekleri

```cpp
#include <iostream>
#include <optional>

std::optional<int> get_value(bool condition)
{
    if (condition)
        return 42;
    else
        return {};
}

int main()
{
    auto value1 = get_value(true);
    auto value2 = get_value(false);

    if (value1)
        std::cout << "value1 is " << *value1 << '\n';
    else
        std::cout << "value1 is empty\n";

    if (value2)
        std::cout << "value2 is " << *value2 << '\n';
    else
        std::cout << "value2 is empty\n";
}

```

### emplace

`**std::optional**`nesnesinin tuttğu nesnesinin constructor’ı çağrılarak nesne oluşturmak için kullanılır. Eğer `**std::optional**`nesnesi hali hazırda bir nesne tutuyorsa emplace fonksiynu çağrıldığında o nesnenin hayatı biter ve yeni nesne oluşturulur. 

```cpp
#include <iostream>
#include <vector>
#include <optional>

int main() {
    std::optional<std::vector<int>> vec_opt;

    vec_opt.emplace(); // vector nullopt'tan oluşturuldu

    vec_opt->emplace_back(1);
    vec_opt->emplace_back(2);
    vec_opt->emplace_back(3);

    for (const auto& val : *vec_opt) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}

//OUTPUT: 1 2 3
```

### std::nullopt

**`std::nullopt`** değeri, **`std::optional`** nesneleri için bir standart boş değerdir. Bu değeri kullanarak, bir **`std::optional`** nesnesini boş olarak tanımlanabilir.

```cpp
#include <iostream>
#include <optional>

std::optional<int> getValue(bool return_value) {
  if (return_value) {
    return 42;
  }
  else {
    return std::nullopt;
  }
}

int main() {
  std::optional<int> value = getValue(false);

  if (value) {
    std::cout << "Value is " << *value << '\n';
  } else {
    std::cout << "Value is not available\n";
  }

   value = getValue(true);
  
    if (value) {
    std::cout << "Value is " << *value << '\n';
  } else {
    std::cout << "Value is not available\n";
  }

  return 0;
}

/*
OUTPUT:
Value is not available
Value is 42

*/
```

### std::in_place

**`std::in_place`** C++11'de tanıtılan bir C++ özelliğidir ve bir **`std::optional`** nesnesinin yerinde (in-place) oluşturulmasını sağlayan bir argüman olarak kullanılır.

**`std::in_place`** kullanarak, bir **`std::optional`** nesnesinin bir türdeki değeri doğrudan yerinde oluşturulabilir. Bu, özellikle büyük veya hareket edilemeyen nesneler için performans artışı sağlayabilir.

Aşağıdaki örnekte, **`std::in_place`** ile bir **`std::optional`** nesnesinin yerinde oluşturulması gösterilmektedir:

```cpp
#include <iostream>
#include <optional>
#include <string>

struct Person {
Person(std::string _name, int _age) : name(_name), age(_age) {};
    std::string name;
    int age;
};

int main() {
    std::optional<Person> p(std::in_place, "Barış", 29);

    if (p) {
        std::cout << "Name: " << p->name << std::endl;
        std::cout << "Age: " << p->age << std::endl;
    }
    
    return 0;
}

/*
OUTPUT:
Name: Barış
Age: 29
*/
```

### make_optional

optional nesneni oluşturmak için kullanılabilecek bir factory fonksiyonudur. 

```cpp
#include <iostream>
#include <optional>
#include <string>

struct Person {
Person(std::string _name, int _age) : name(_name), age(_age) {};
    std::string name;
    int age;
};

int main() {
    std::optional<Person> p = std::make_optional<Person>("Barış", 29);

    if (p) {
        std::cout << "Name: " << p->name << std::endl;
        std::cout << "Age: " << p->age << std::endl;
    }
    
    return 0;
}

/*
OUTPUT:
Name: Barış
Age: 29
*/
```