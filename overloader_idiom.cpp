#include <iostream>

//overloader idiom
template<typename... Ts> //variadic template
struct Overloader : Ts... // inherit classes by pack expantion
{
	using Ts::operator()...; // to solve ambiguity 
};

class foo
{
    public:
    void print()
    {
        std::cout<<"foo class print function \n";
    }
};

int main()
{
    Overloader overloader = Overloader
    {
        [](int a){std::cout<<"int : "<< a << '\n'; },
        [](double a){std::cout<<"double : "<< a << '\n';},
        [](std::string a){std::cout<<"string : "<< a << '\n';},
        [](foo a){std::cout<<"foo :"; a.print();},
        [](auto) { std::cout<<"unknown type\n"; }
    };

    overloader(23);
    overloader(3.14);
    overloader("test");
    overloader((foo{}));
    overloader(3L);
}

/*
OUTPUT:
int : 23
double : 3.14
unknown type
foo :foo class print function 
unknown type
*/
