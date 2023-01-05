/*
Kaynakca
https://github.com/umutkotankiran/Cpp/blob/main/17_27_06_2021/main.cpp
https://github.com/necatiergin/cpp_odev/blob/main/038_STD_STRING

*/


/*
Notlar:

	String sınıfı, amacı yazıları tutmak ve manipüle etmek olan bir STL (Standart template library) container sınıfıdır.
	Container veri yapılarını (verileri organize bir şekilde saklayan yapılar) temsil eden sınıflara verilen isim.
	dinamik dizi, bağlı liste, ikili arama ağacı ... bunlar çeşitli container veri yapılarıdır..

	STL sınıfı içerisinde birden fazla amaçlı kullanılabilen container sınıfları vardır. Bunlar;
	vector, deque, list, forward_list, string, array,set...

	STL içerisinde tutulan bu container sınıflarının ortak arayüzü vardır.
	Yani bu sınıfların öyle fonksiyonları vardır ki tüm container sınıfları için aynı anlama gelir.

	CSTRING: Null terminated byte stream. Bazı string sınıfı üye fonksiyonu parametreleri "const char *" şeklindedir ve yanlarında size parametreleri yoktur.
	Bunun anlamı, bu sınıflar Null karakter görene kadar (\0) girilen adresten yazıyı okur. Eğer yazı sonunda null karakter yoksa undefined behavior olur.

	std::string str; // aşağıdaki ile aynı.
	std::basic_string<char, std::char_traits<char>, std::allocator<char> str;

	String sınıfı bir dinamik dizi 3 adet pointer'ı var
	A - Pointerlardan biri dinamik bellek bloğunun adresini tutuyor.
	B - İkinci pointer yazının sonunu tutuyor.
	C - üçüncü pointer ise dinamik bellek bloğunun sonunu tutuyor.

	Dinamik dizi veri yapısının bir numaralı avantajı index bilgisiyle dinamik dizide tutulan öğelere constant time O(1) karmaşıklığında erişmek.
	Sondan ekleme ve sondan silme işlemlerininde constant time da yapılmasıda avantaj.

	Modern İmplementasyonlarda sadece 3 pointer tutmuyorlar. Birde buffer tutuyorlar.
	Eğer string nesnesindeki yazı küçükse dinamik bellek yönetimine girmeden yazıyı bu bufferda tutuyor.
	Böylece bir allocation yapılmıyor. Bu yazı sonradan büyütülürse dinamik bellek yönetimi çalışıyor.
	Bu tekniğe	"Small String Optimization" deniyor

	Capacity: Allocate edilen bellek alanının byte cinsinden büyüklüğü.
	Size: Yazının byte cinsinden büyüklüğü. Her byte bir karakter olduğu için dolayısıyla yazının uzunluğu.

	Tutulan yazı büyütüldükçe (Size arttıkça), tekrar memory allocate yapılarak capacity de otomatik büyütülüyor.
	Yazının nihai uzunluğu belliyse ve 	yazıyı yavaş yavaş büyütülürse sürekli yeni allocation yapılıyor. Bu durum ciddi zaman maliyetine neden olabilir.
	Bu durumda en başında "reverse"  isimli fonksiyon ile gerekli allocation işlemi yapılabilir.

	Yazı küçüldükçe tutulan kapasite otomatik verilmiyor. Eğer tutulan bellek alanını tekrar sisteme vermek istersek
	"shrinktofit" fonksiyonu ile fazla kapasite sisteme verilebilir.

	Member Functions

	[1]  size()									: Yazı boyutunu verir.
	[2]  length()								: Yazı boyutunu verir. Size ile aynı görevi yerine getirir.
	[3]  empty()								: Dönüş değeri boolean'dir. String boş mu sorusuna cevap verir. String boş ise false, değil ise true döner.
	[4]  capacity()								: Allocate edilen bellek alanını byte cinsinden döner.
	[5]  reserve(size_t )						: Allocate edilen bellek alanını set eder.
	[6]  find(char)								: Girilen karakteri yazı içinde arar. Bulamazsa "string::npos" döner.
	[7]	 find(char, const size_t)				: Girilen karakteri yazı içinde girilen indeksten itibaren arar. Bulamazsa "string::npos" döner
	[7]	 find(string)							: Girilen yazıyı, yazı içinde arar. Bulamazsa "string::npos" döner.
	[8]  begin()								: Yazının ilk karakterinin adresinin konumu. Diğer adıyla başlangıç adresi
	[9]  end()									: Yazının son karakterinden bir sonraki adresin konumu. Diğer adıyla bitiş adresi
	[10] resize(size_t )						: Yazının size değerini değiştirir. Boş olan kısımlara null karakter atar
	[11] at(size_t )							: Argüman olarak girilen karaktere gider. "[ ]" operatörü ile aynı işi yapar.
	[12] compare(string)						: Argüman olarak girilen string ile karşılaştırma yapar. Kaynak büyükse pozitif, argüman büyükse negatif, eşit ise 0 döner.
	[13] front()								: İlk ögenin referansını döner.
	[14] back()									: Son ögenin referansını döner.
	[15] push_back(const char)					: Yazının sonuna bir karakter ekler. += operatörü ile de yazının sonuna ekleme (hem karakter hem string) yapılabilir.
	[16] insert(size_t,size_t,char)				: Girilen indekse (ilk parametre), girilen sayı kadar(ikinci parametre), girilen karakteri (üçüncü parametre) ekler. insert(0,10,'a') 0 indeksine 10 adet a karakteri ekler
	[17] insert(size_t,string )					: Girilen indekse (ilk parametre), girilen yazıyı ekler.
	[18] insert(size_t,string, size_t )			: Girilen indekse (ilk parametre), girilen yazıyı ekler, girilen indeksten ekler. (string s = "Baris") s.insert(0,"123",2) = çıktı olarak 12Baris verir
	[19] insert(size_t,string, size_t , size_t)	: Girilen indekse (ilk parametre), girilen yazıyı ekler, girilen indeksten, girilen boyut kadar ekler. (string s = "Baris") s.insert(0,"123",2,1) = çıktı olarak "3Baris" verir
	[20] append(string)							: Argüman olarak girilen yazıyı, kaynak yazının sonuna ekler.
	[20] append(size_t, char)					: Argüman olarak girilen sayı kadar (ilk parametre), karakteri yazının sonuna ekler
	[21] append(string, size_t, size_t)			: Yazının (ilk paramtere), girilen indeksinden (ikinci paramtre), girilen sayı kadar (üçüncü paramtre) karakterini ekler.  (string s = "Baris")	s.append("123",1,2); = Baris23
	[21] assign(string)							: Parametre olarak girilen yazıyı, kaynak yazı yerine atar.
	[21] assign(const char *, size_t)			: Parametre olarak girilen yazıyı, kaynak yazı yerine girilen boyutta atar.	s.assign("Baris",2); kaynaga Ba atar.
	[22] erase()								: Tüm karakterleri siler (1. parametre default argument 0, ikinci paramtre default argument npos)
	[22] erase(iterator)						: Girilen indeksten başlayıp geriye kalan tüm karakterleri siler.
	[22] erase(iterator, iterator)				: Girilen indeksten başlayıp (ilk parametre), girilen sayı kadar (ikinci parametre) karakter siler.	(string s = "Baris") s.erase(1, 2); = Bis
	[23] pop_back()								: Son karakteri siler.
	[24] find_first_of(string)					: Yazı içinde girilen yazıdaki herhangi bir karakteri arar. İlk bulduğu indeksi döner. Bulamazsa "string::npos" döner. find_first_of("0123456789") sayı olan ilk indeksi döner.
	[24] find_last_of(string)					: Yazı içinde girilen yazıdaki herhangi bir karakteri arar. Son bulduğu indeksi döner. Bulamazsa "string::npos" döner.
.	[24] find_first_not_of(string)				: Yazı içinde girilen yazıdaki herhangi bir karakteri arar. İlk bulunmadığı indeksi döner. Bulamazsa "string::npos" döner. find_first_not_of("0123456789") sayı bulunmayan ilk indeksi döner.
	[24] find_first_not_of(string)				: Yazı içinde girilen yazıdaki herhangi bir karakteri arar. Son bulunmadığı indeksi döner. Bulamazsa "string::npos" döner.
	[25] rfind									: find ile aynı ancak aramayı sondan başa yapar. indeks döndürür.
	[26] substr(size_t)							: Girilen sayıdan sonraki her şeyi string olarak döndürür.
	[26] substr(size_t, size_t)					: Girilen aralıktaki her şeyi string olarak döndürür.
	[27] replace(size_t, size_t, string)		: Girilen indekse (1. parametre), girilen uzunluktaki  yere (2. parametre)  girilen yazıyı (3. parametre) ekler. (string s = "Baris") s.replace(1,2,"123"); = B123is
	[28] clear()								: Tüm stringi siler

	Genel yapı, ilk argüman aranan varlık, son argüman aramanın hangi indexten başlayarak yapılacağı(genelde default oluyor bu)

	String Function									Effect
	--------------------------------------------------------------------------------------
	stoi(str,idxRet=nullptr, base=10)				Converts str to an int
	stol(str,idxRet=nullptr, base=10)				Converts str to a long
	stoul(str,idxRet=nullptr, base=10)				Converts str to an unsigned long
	stoll(str,idxRet=nullptr, base=10)				Converts str to a long long
	stoull(str,idxRet=nullptr, base=10)				Converts str to an unsigned long long
	stof(str,idxRet=nullptr)						Converts str to a float
	stod(str,idxRet=nullptr)						Converts str to a double
	stold(str,idxRet=nullptr)						Converts str to a long double
	to_string(val)									Converts val to a string
	to_wstring(val)									Converts val to a wstring


	to_string: fonksayoni ile string olmayan yapılar string'e dönüştürülebilir.
		int ival = 2345;
		to_string(ival);
*/


/*
string_01.md

	[01] Yazının ilk karakterini silin.
	[02] Yazının son karakterini silin.
	[03] Yazının ilk ve son karakterleri dışında tüm karakterlerini silin.
	[04] Yazının ikinci karakterini silin.
	[05] Yazının sondan ikinci karakterini silin.
	[06] idx yazının geçerli bir indeksi olmak üzere yazının idx indisli karakterini silin.
	[07] Yazıdaki ilk a karakterini silin.
	[08] Yazıdaki son a karakterini silin.
	[09] Yazıdaki tüm a karakterlerini silin.
	[10] Yazıdaki ilk a karakteri ile başlayan ve son a karakteri ile biten yazıyı silin.
	[11] Yazıdaki ilk a karakterinden önce gelen ve sonra gelen 2 karakteri silin.
	[12] Yazıda bulunan ilk "kan" yazısını silin
	[13] Yazıda bulunan son "kan" yazısını silin
	[14] Yazıda bulunan tüm "kan" yazılarını silin
	[15] Yazıda bulunan ilk rakam karakterini silin
	[16] Yazıda bulunan son rakam karakterini silin
	[17] Yazıdaki tüm rakam karakterlerini silin.
	[18] Yazının uzunluğu 1'den büyükse ve yazının ilk karakteri ile son karakteri aynı ise bunları silin.
	[19] Yazının uzunluğu 5'ten büyükse ve yazının ilk 3 karakteri ile son 3 karakteri aynı ise bunları silin.
	[20] Yazıdaki ardışık eşit karakterlerden sadece bir tane kalacak şekilde silme işlemi yapın. (unique)
	[21] Yazıdaki tüm boşluk (whitespace) karakterlerini silin.


*/

#include <string>
#include <iostream>


void print(const std::string& s)
{
	std::cout << "'" << s << "' [" << s.length() << "]\n";
}

void print_divider()
{
	std::cout << "---------------------------------------------------------------\n";
}

int main()
{
	std::string s;
	std::string s_ori = s = "llll tugggkkan1233 ataaaakkan 456baaris llll";

	{
		std::cout << "[1] Yazinin ilk karakterini silin\n";
		print(s_ori);

		s.erase(s.begin(), s.begin() + 1);
		//	s.erase(0,  1);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[2] Yazinin son karakterini silin\n";
		print(s_ori);

		//s.erase(s.end()-1);
		//	s.erase(s.size() - 1);
		s.pop_back();

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[3] Yazinin ilk ve son karakterleri disinda tum karakterlerini silin\n";
		print(s_ori);

		//s.erase(s.begin(), s.begin() + 1);
		//s.erase(s.end() - 1);
		s = s.substr(1, s.size() - 2);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[4] Yazinin ikinci karakterini silin\n";
		print(s_ori); 

		s.erase(s.begin() + 1, s.begin() + 2);
		//s.erase(1,  2);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[5] Yazinin sondan ikinci karakterini silin\n";
		print(s_ori);

		s.erase(s.end() - 2, s.end() - 1);
		//s.erase(s.size()-2,  1);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[6] idx yazinin gecerli bir indeksi olmak uzere yazinin idx indisli karakterini silin\n";
		print(s_ori);

		int idx = 3;
		std::cout << "idx = " << idx << "\n";
		//s.erase(s.begin() + idx, s.begin() + (idx +1));
		s.erase(idx, 1);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[7] Yazidaki ilk a karakterini silin\n";
		print(s_ori);

		int first_a_idx = s.find('a');
		s.erase(first_a_idx, 1);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[8] Yazidaki son a karakterini silin\n";
		print(s_ori);

		int last_a_idx = s.rfind('a');
		s.erase(last_a_idx, 1);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[9] Yazidaki tum a karakterlerini silin\n";
		print(s_ori);

		int idx_of_a = 0;
		while (idx_of_a = s.find('a', idx_of_a), idx_of_a != std::string::npos)
		{
			s.erase(idx_of_a, 1);
		}

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[10] Yazidaki ilk a karakteri ile baslayan ve son a karakteri ile biten yaziyi silin\n";
		print(s_ori);

		int first_idx_of_a = s.find('a');
		int last_idx_of_a = s.rfind('a');
		s.erase(s.begin() + first_idx_of_a, s.end() - (s.size() - (last_idx_of_a +1)));

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[11] Yazidaki ilk a karakterinden once gelen ve sonra gelen 2 karakteri silin.\n";
		print(s_ori);

		int first_idx_of_a = s.find('a');
		//s.erase(s.begin() + (first_idx_of_a -1), s.begin() + (first_idx_of_a +2));
		s.erase(first_idx_of_a, 3);

		print(s);
		s = s_ori;
		print_divider();
	}

	


	{
		std::cout << "[12] Yazida bulunan ilk \"kan\" yazisini silin\n";
		print(s_ori);

		std::string target = "kan";
		int first_idx_of_target = s.find(target);
		s.erase(first_idx_of_target, target.size());

		print(s);
		s = s_ori;
		print_divider();
	}


	{
		std::cout << "[13] Yazida bulunan son \"kan\" yazisini silin\n";
		print(s_ori);

		std::string target = "kan";
		int first_idx_of_target = s.rfind(target);
		s.erase(first_idx_of_target, target.size());

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[14] Yazida bulunan tum \"kan\" yazilarini silin\n";
		print(s_ori);

		std::string target = "kan";
		int first_idx_of_target = 0;
		while (first_idx_of_target = s.find(target, first_idx_of_target), first_idx_of_target != std::string::npos)
		{
			s.erase(first_idx_of_target, target.size());
		}

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[15] Yazida bulunan ilk rakam karakterini silin\n";
		print(s_ori);

		s.erase(s.find_first_of("0123456789"), 1);

		print(s);
		s = s_ori;
		print_divider();
	}


	{
		std::cout << "[16] Yazida bulunan son rakam karakterini silin\n";
		print(s_ori);

		s.erase(s.find_last_of("0123456789"), 1);

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[17] Yazidaki tum rakam karakterlerini silin\n";
		print(s_ori);

		size_t idx = 0;
		while (idx = s.find_first_of("0123456789", idx), idx != std::string::npos)
		{
			s.erase(idx, 1);
		}

		print(s);
		s = s_ori;
		print_divider();
	}


	{
		std::cout << "[18] Yazinin uzunlugu 1'den buyukse ve yazinin ilk karakteri ile son karakteri ayni ise bunlari silin\n";
		print(s_ori);

		if (s.size() > 1 && (s.at(0) == s.at(s.size() - 1)))
		{
			s.erase(0, 1);
			s.erase(s.size() - 2, 1);
		}

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[19] Yazinin uzunlugu 5'ten buyukse ve yazinin ilk 3 karakteri ile son 3 karakteri ayni ise bunlari silin\n";
		print(s_ori);

		if (s.size() > 5 && (s.substr(0, 3).compare(s.substr(s.size() - 3, s.size() - 1)) == 0))
		{
			s.erase(0, 3);
			s.erase(s.size() - 4, 3);
		}

		print(s);
		s = s_ori;
		print_divider();
	}


	{
		std::cout << "[20] Yazidaki ardisik esit karakterlerden sadece bir tane kalacak sekilde silme islemi yapin. (unique)\n";
		print(s_ori);

		char ch_old = s.at(0);
		for (int i = 1; i < s.size(); i++)
		{
			if (s.at(i) == ch_old)
			{
				s.erase(i, 1);
				i--;
			}

			ch_old = s.at(i);
		}

		print(s);
		s = s_ori;
		print_divider();
	}

	{
		std::cout << "[21] Yazidaki tum bosluk (whitespace) karakterlerini silin.\n";
		print(s_ori);

		size_t idx = 0;
		while (idx = s.find_first_of(" ", idx), idx != std::string::npos)
		{
			s.erase(idx, 1);
		}

		print(s);
		s = s_ori;
		print_divider();
	}

}



