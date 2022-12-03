/*
Kaynakça
https://github.com/umutkotankiran/Cpp/blob/main/25_01_08_2021/main.cpp


Derleyicinin bizim yerimize kod yazmasını istersek templateler kullanırız.
Derleyiciye template ile bir şablon verilir ve bu şablonlar ile türden bağımsız şekilde kod yazılabilir.
Yani geliştirici proram yazarken template yazar ve derleyici bu templatei kullanarak gereken her örnek için kendi kodunu yazar ve kullanır.
Dolayısıyla template'ler çalışan kodun kendisi değildir. Derleyici templateler ile çalışan kodu yazarlar.
Türden bağımsız yazıldığı için algoritmalar daha üst düzey bir soyutlama yapılır. 
Örnek olarak iki int nesnenin swap edilmesi değil de iki nesnenin swap edilmesi gibi.
Programcı template yazdıktan sonra derleyici bu template'i kullanarak kendi gerçek kodu her örneği için compile time'da yazıyor. 
Bu işleme template instantiation denir. Yazılan her bir gerçek koda ise templatein o tür için template specialization'ı denir. 
C++ ın çok büyük kısmını STL oluşturuyor. STL açılımı Standard Template Library. 
string, vector veya unique_ptr sınıfı gibi bir çok sınıf template'dir ve derleyici, derleme zamanında kodları yazarlar. 


Temel Kategorilere ayrılıyor.
- Function Templates
- Class Templates
- Alias Template		C++11 ile geldi
- Variable Template		C++11 ile geldi
- Concept Template		C++20 ile geldi


int main()
{
	std::vector <int>x; 
}
Standart vector sınıfını kullanırken ismi vector olan sınıf şablonundan tür olarak int türünü
kullanması ve bizim için int türünden bir konteyner sınıfı yazmasını istiyoruz. 

FONKSIYON VE SINIF ŞABLONLARI
-----------------------------
Template kullanırken keyword olarak "template" ve hemen ardından  açısal parantez "<>"" kullanılır. 

Açısal parantez içindeki bildirimlere template parametreleri denir.
template <typename T >  veya template <class T >  

Template parametreleri,
	a - Type/Tür parametresi olabilir
		Bir isim kullanıyoruz ve bu bir türe karşılık geliyor.

            template <typename T >  veya template <class T >  
            template <typename T, typename U>

	
	b - non-type parameter olabilir.(sabit parametre)
        Bir isim kullanılıyor ve bu bir sabite karşılık geliyor.
            template <int x>
	
	c - template template parameter olabilir. 


TYPE PARAMETER
--------------

Tür parametresi, derleyiciye bir isim veriliyor ve bu isim int, double veya bir class ismi gibi bir türe karşılık geliyor.

Tür parametresi geçerken kullanılabilecek 2 adet keyword var.
1. class
2. typename

template <class T>   T ismi burada sınıf veya primitive bir türü temsil ediyor
Daha sonra eklenen ise typename keyword. Bu keywordun eklenme sebebi class çok uygun bir keyword olmadığı düşünüldüğü için.
Mesela T burada bir int veya pointer veya enum türü olabilir. Bunlar sınıf türü değil. Ama başında class var. Çok uygun bir keyword olmadığı için typename eklendi.


template <typename T>
template <class T>	

ikiside geçerli ve aynı. 

Tür parametresinin ne olduğunu derleyicisin bilmesi gerekiyor. Bu bilgiyi geliştirici açısaln parantez içinde yazarak kendi de verebilir veya tür çıkarım (deduction) mekanizması kullanılabilir.
	template <typename T>
	void func(T x);

    func<int>(10) şeklinde fonksiyon çağrılırsa bu explicit oluyor ve T int türden olduğu derleyiciye söylenmiş oluyor.
    func(3.4) olursa burada type deduction (tür çıkarım) mekanizması devreye giriyor ve T double oluyor.  



NON-TYPE PARAMETER
-------------------
Template'e bir sabit ifadesi vermek içink ullanılıyor. 
template <int x>	Burada x int türden sabit olmak üzere anlamına geliyor. 

int main()
{
	std::array<int, 2> ar;		arrayde ilk argüman tür argümanı ikincisi ise sabit parametreye karşılık gelen sabit argümanı.
}

array sınıf şablonu aağıdaki gibi.
template <typename T, size_t size> birincisi tür ikincisi boyut olarak kullanılacak
struct array{
};

*/