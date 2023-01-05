/*
FIND_IF
------

Bir range'de tutulan öğelerden belrili koşulu sağlayan ilk konumu döndürür. Eğer hiç bulunamazsa range'in end konumu döndürülür.

minimum input kategorisinde iteratör alır.

SENTAKS
-------

find_iter find_if(begin_iter, end_iter, Pred f)

Pred f =  bool dönüşlü ve bir girişli bir fonksiyonun adresi 

parametre olarak verilen f fonksiyonu yerine lambda ifadesi verilebilir. 

*/

#include<algorithm>
#include<iostream>
#include<vector>
#include<string>

bool is_len_3(const std::string& s)
{
    return s.length() == 3;
}

template<size_t n>
bool is_len_same(const std::string& s)
{
    return s.length() == n;
}


class LenPred
{
public:
    explicit LenPred(std::size_t len): mlen{ len }{}
    bool operator()(const std::string & s) const{
        return s.length() == mlen;
    }

private:
    std::size_t mlen;
};


int main()
{
    std::vector<std::string> svec = { "aa", "ab","ac", "abc","acd","abcd" };

    size_t len = 3;

    if (auto find_iter = find_if(svec.begin(), svec.end(), is_len_3); find_iter != svec.begin())
    {
        std::cout << "Bulundu : " << *find_iter << "\n";
    }
    else
    {
        std::cout << "Bulunamadi";
    }

    /*
    OUTPUT
    -----
    Bulundu : abc
    */


    if (auto find_iter = find_if(svec.begin(), svec.end(), is_len_same<4>); find_iter != svec.begin())
    {
        std::cout << "Bulundu : " << *find_iter << "\n";
    }
    else
    {
        std::cout << "Bulunamadi";
    }

    /*
    OUTPUT
    -----
    Bulundu : abcd
    */


    if (auto find_iter = find_if(svec.begin(), svec.end(), LenPred(len)); find_iter != svec.begin())
    {
        std::cout << "Bulundu : " << *find_iter << "\n";
    }
    else
    {
        std::cout << "Bulunamadi";
    }
    /*
    OUTPUT
    -----
    Bulundu : abc
    */


    if (auto find_iter = find_if(svec.begin(), svec.end(),[len](const std::string s) {return s.length() == len;} ); find_iter != svec.begin())
    {
        std::cout << "Bulundu : " << *find_iter << "\n";
    }
    else
    {
        std::cout << "Bulunamadi";
    }
    /*
    OUTPUT
    -----
    Bulundu : abc
    */
    return 0;
}