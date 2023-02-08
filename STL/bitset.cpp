/*
BITSET
------

Bitsel işlemleri kolaylaştırmak için kullanılıyor.

template<std::size_t N>
class bitset;

İçerisinde boolean tutulmuyor gerçekten bitlere erişiliyor.

inserter ve extractor var. giriş ve çıkış akımına bitler gönderilebiliyor.

default ctor tüm bitleri 0 yapıyor.

count fonksiyonu doğrudan set edilmiş bitlerin sayısını döndürür. 
set fonksiyonu ile belirli sıradaki bit ile 1 yapılabilir. *this döndürür
reset fonksiyonu ile belirli sıradaki bit ile 0 yapılabilir. *this döndürür.
test fonksiyonu pozisyon alarak bool döndürüyor. bit 1 ise true döner
all fonksiyonu bütün bitlerin set edilip edilmediğini kontrol ediyor. tüm bitler 1 ise true döner
any fonksiyonu herahngi bir bitin set edilip edilmediğini kontrol ediyor. herhangi bir bit 1 ise true döner
none fonksiyonu bütün bitlerin 0 olup olmadığını kontrol ediyor. tüm bitler 0 ise true döner
flip, girilen pozsiyon için bitin değerini tersi ile değiştirir. Eğer indeks değeri argüman olarak girilmezse tüm bitleri flip eder. 
[] operatör fonksiyonu, girilen pozisyon bilgisine erişim sağlar. Bu erişim değeri reference türünden bir değişkendir. bu durum type deduction kullanılırken dikkat edilmelidir. 
*/


#include <bitset>
#include <iostream>


int main()
{
    std::bitset<6> bit6{ 27u };
    std::bitset<8> byte;

    std::cout << "bit6: " << bit6 << " byte: " << byte << "\n";
    //bit6: 011011 byte: 00000000

    byte.set(3);

    std::cout << "bit6: " << bit6 << " byte: " << byte << "\n";
    //bit6: 011011 byte: 00001000

    int a = byte.to_ulong();

    std::cout<<"a : "<<a<<"\n";
    //a : 8

    std::bitset<16> half_world{000011};
    std::cout<<"half_world.count(): "<<half_world.count()<<"\n";
    //half_world.count(): 2




}