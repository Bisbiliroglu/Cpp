/*

Input Output Operations
========================

Programın dış dünya ile iletişimi
Stream: dış dünyayadan programa veya programdan dış dünyaya çıkan bilgiler (akım).

    +--------+        +----------+
    |        |  in    |          |
----| Input  |------->|          |
    | Source |        |          |
    +--------+        |    C++   |
                      |  Program |
    +--------+        |          |
    |        |  out   |          |
<---| Output |<-------|          |
    |  Sink  |        |          |
    +--------+        +----------+


Gelen ve giden veri bytestream şeklinde geliyor ve bir akış halidnde.
Input, klavye olabilir, network olabilir, başka program veya dosya olabilir.
Çıkış kaynağı output sink olarak adlandırılıyor. bu konsol, network başka program olabilir.

Giriş çıkış kütüphanesi iostream kütüphanesinde tutulamktadır

STREAMS
-------

basic_ostream: çıkış interfaceini sunuyor
basic_istream: giriş interfaceini sunuyor.

Bu iki sınıf virtual olarak basic_ios sınıfından kalıtım yoluyla elde ediliyor.


basic_iostream: basic_ostream ve basic_istream sınıflarından ortak kalıtım yoluyla elde edilen sınıf bu sınıftan kalıtım yoluyla basic_stringstream ve basic_fstream sınıfları elde ediliyor.
Hem giriş hem
basic_ofstream, basic_fstream ve basic_ifstream sınıfları dosya işlemleri için kullanılıyor.
basic_ostringstream, basic_stringstream ve basic_istringstream sınıfları bellek üzerinden işlemler yapmak için kullanılıyor. Bunlar C içerisinde sprintf, sscanf fonksiyonlarına benzetilebilir.


bu stream sınıfları byteları kullanılıyor ve bu bytler bir kere kullanılabiliyor. Arkada bir buffer mekanizması olmazsa okuma işlemi sonrasında siliniyor. Dolayısıyla arkada bufferlama işlemini yapan sınıflar
Bu sıfı ismi basic_streambuf sınıfları. Üste yazılan stream nesneleri composition yoluyla basic_streambuf nesnesini tutuyor.


iostreams and locales (Angelika langer ve klaus krest)


Formatlama İşlemleri
--------------------
Gönderilen ve alınan dataların istenilen formatlara çevrilmesi
Çıkış için formatlama işlemleri tipik olarak operator<< fonksiyonun overloadları ile yapılıyor.
Tüm operator<< fonksiyonların dönüş değeri stream nesnesinin kendisi. Dolayısıyla chaining yapılabiliyor.

cout<<ival<<dval
ivali yazdıran fonksiyonun parametresi int iken dvali yazdıranınki double

State: Sınıf nesneleri nasıl davranacağı state bilgisinden alıyor. State objenin tüm üye bilgilerine göre davranışına karar vermesi denilebilir.
Giriş çıkış stream sınıfları nesneleri bir format state tutuyorlar. Bu format state değişirse strema davranışı da değişir. Bu format state get, set edilebilir.

cout<< (10 > 5) ==> çıktısı 1 olur. Eğer bool değeri true, false olarak yazdımak istersek format durumunu değiştirmek gerekir.
cout.setf(ios::boolalpha) ==> setf format set için kulanılıyor. boolalpha durumu girilirse cout<< (10 > 5) çıktısı true olur.
format stati değiştirilene kadar bu şekilde yazdırmaya devam eder.
cout.unsetf(ios::boolalpha) çağrılırsa boolalpha statei unset olur ve eski haline döner


 _____________________________________________________________________________________________________________________________________________________
| Format State  | Description                                                                                                                         |
|---------------|-------------------------------------------------------------------------------------------------------------------------------------|
| boolalpha     | Displays bool values as "true" or "false" instead of 1 or 0.                                                                        |
| showbase      | Shows the base prefix for octal and hexadecimal values (0 or 0x).                                                                   |
| showpoint     | Always displays the decimal point for floating-point values.                                                                        |
| showpos       | Shows a plus sign before positive numeric values.                                                                                   |
| skipws        | Skips leading whitespace when reading input.                                                                                        |
| unitbuf       | Flushes the output buffer after each insertion operation.                                                                           |
| uppercase     | Uses uppercase letters for hexadecimal values and floating-point exponents.                                                         |
| dec           | Sets the number base to decimal (10).                                                                                               |
| hex           | Sets the number base to hexadecimal (16).                                                                                           |
| oct           | Sets the number base to octal (8).                                                                                                  |
| fixed         | Sets floating-point output to fixed-point notation.                                                                                 |
| scientific    | Sets floating-point output to scientific notation.                                                                                  |
| left          | Left-aligns output within the specified field width.                                                                                |
| right         | Right-aligns output within the specified field width.                                                                               |
| internal      | Pads output with fill characters to align with the field width, with the sign or radix point in the center.                         |
 -----------------------------------------------------------------------------------------------------------------------------------------------------

fixed       : 7634.980909090
scientific  : 0.76e7
hexfloat    : setf(fixed | scientific) : gerçek sayıları hexadecimal formatta yazdırıyor.

default fixed veya sceintific sayının büyüklüğüne göre kendi karar veriyor.
Eğer
setf(fixed | scientific) girilirse gerçek sayıları hxadecimal olarak kedi yazdırıyor.

ios_base::fmtflags
------------------
Derleyiciye bağlı bir tür.
Formatlama bilgisi bitlerde tutuluyor.

her stream sınıfının setf isimli fonksiyonu var. Bu fonksiyona ios_base maskeleri gönderilirse set edilmiş oluyor.

cout.setf(ios_base::boolalpha)

eğer gönderilen fmtflagler geri alınmak istenirse unsetf fonksiyonu kullanılabilir.
fmtflags değerleri almak için ise flags fonksiyonu kullanılabilir.

 Function            |  Meaning
------------------------------------------------------------------
unsetf(flag)        |  Clears the specified flag(s) from the format control
setf(flag)          |  Sets the specified flag(s) in the format control
flags()             |  Returns the current format control flags

cout.stf(ios::boolaplpha | ios::uppercase | ios::showbase) şeklinde birden fazla flag set edilebilir.

rdbuff
------
akım nesnesinin bufferının adresini veriyor. Bu adres ile yeni akım nesneleri oluşturulabilir.
Bu özelliği ile geçici stream nesneleri oluşturularak istenilen formatlarda çıkış akımı yapılandırılabilir ve bu durumda orijinal kaım format özellikleri korunur.



output width
-------------
Yazma alanı genişliğini ayarlar.
Bir sayı değeri olarak girilir.
belirli bir alana yazılması gereken alanı belirtir.
Bu alandan küçük değerler girilirse fill character ile alanı doldurur

int ival = 12345,
output with : 9
fill character: _
____12345 // saga dayali
12345____ // sola dayal

width(int) fonksiyonu ile output width set edilebilir.
fill(char) fonksiyonu ile doldurma karakteri set edilebilir.

cout.width(9);
cout.fill(_)

sola veya sağa dayalı için ios::left veya ios::last fmtflagleri kullanılabilir.
Bunların haricinde ios::internal bulunmaktadır. Bu ise işaret solda sayının kendisi fill character ile sağa geçmesini sağlar.
+______12345
-______12345

yazma alanı girilen değerden düşük girilirse ekstra bir truncate (budama) işlemi yapılmıyor. normalde nasıl yazılacaksa o şekilde yazılıyor.


cout.width(3)
cout<<12345


ondalık sayılarda noktadan sonra kaç basamağın yazdırılacağını bildirmek için precision fonksiyonu var.

cout.precision(int )
Argüman olarak girilen sayı noktadan sonra gösterielcek dijit sayısıdır. default 6
Eğer parametre girilmezse get fonksiyonu olarak kullanılır.


OSTREAM Manipulators
--------------------

std::ostream& Hex(std::ostream& os)
{
    os.setf(std::ios::hex, std::ios::nasefield)
    return os;
}

böyle bir fonksiyon yazılırsa

cout<< ival << " " <<Hex << " ";
şeklinde yazılabiliyor.

her format state flag için bu tür manipulator fonksiyonları stl içinde yazılmış durumda
cout<< ival << " " <<hex << " "; kullanılabilir
cout<< boolalpha << " " <<true << " "; kullanılabilir

set eden manipulatorlari geri almak için (unset) no öneki kullanılabilir.
cout<< noboolalpha << " " <<true << " "; kullanılabilir


STREAM NESNESİ TESTLERİ
-----------------------
Bir akımm nesnesinin format state gibi condition state bilgileride vardır. Bu condition state
1.) Hata durumunda


ios:iostate
------------

+---------------------------+-------------+------------------------------------------------------------+
| Function                  | Return Type | Meaning                                                    |
+---------------------------+-------------+------------------------------------------------------------+
| good()                    | bool        | Returns true if none of the stream's flags are set         |
| bad()                     | bool        | Returns true if the stream's badbit flag is set            |
| fail()                    | bool        | Returns true if the stream's failbit or badbit flag is set |
| eof()                     | bool        | Returns true if the stream's eofbit flag is set            |
| clear()                   | void        | Clears all the stream's flags                              |
| clear(flag = goodbit)     | void        | Clears the specified flag(s)                               |
| setstate(flag)            | void        | Sets the specified flag(s)                                 |
| rdstate()                 |             | Get stream conditions flags                                |
+---------------------------+-------------+------------------------------------------------------------+

+---------------+---------------------------+---------------------------------------------------------+
| Flag          | Symbolic Constant         | Meaning                                                 |
+---------------+---------------------------+---------------------------------------------------------+
| goodbit       | `std::ios_base::goodbit`  | No errors occurred                                      |
| badbit        | `std::ios_base::badbit`   | A non-recoverable error occurred                        |
| failbit       | `std::ios_base::failbit`  | A recoverable error occurred                            |
| eofbit        | `std::ios_base::eofbit`   | End of file reached on input stream                     |
+---------------+---------------------------+---------------------------------------------------------+

clear
------

Bir stream nesnesi fail duruma düştüğü zaman onun ile okuma yapmak için tekrar good duruma getirmek gerekiyor.
Bu yüzden fail durumda bir nesne varsa clear fonksiyonu ile tekrar good duruma getirilip kullanılmaıs gerekir.
clear fonksiyonu
condition state = flag

setstate ise
condition state |= flf


Bellek İşlemleri
-----------------

Bellek üzerinde okuma yazma dosyalarının başlık dosyası sstream

istream     ===>  istringstream
ostream     ===>  ostringstream
iostream    ===>  stringstream

str fonksiyonu stream nesnesi buffer içerisindekileri std::string olarak döndürüyor


Dosya İşlemleri
-----------------
Okuma veya yazma işlemleri bir stream objesi ile beraber kullanılıyor.
Dosyanın açılması ctor ile sağlanabilir veya open fonksiyonu ile açılabilir.
Dosyanın kapanması stream objesi destructorı ile kapatılabilir veya close fonksiyonu kullanılabilir.
Başlık dosyası adı fstream

dosya açış modeu bilgisi, yazma amaçlı modlar ifstream ile okuma amaçlı modlar ise ofstream ile kullanılamaz.
ios_base:openmode isimli bir değişken var.
ios::in
ios::out
ios::app
ios::binary
ios::ate        : dosya konum göstericisini dosyanın sonunda açıyor.
ios::trunc      : dosyayı sıfırlıyor

ifstream ctor ikinci parametre olarak girilebilir

ifstream ifs{ "test.txt", ios:in | ios::binary}; // binary amaçlı okuma modunda test.txt dosyası açılıyor.

ofstream ofs{"test.txt , ios::out | ios::trunc"} //ofstream için ios::out ve ios::trunc default mod argümanıdır. yani default modda açılınca hali hazırda var olan dosya silinecektir.

fstream modunda default değeri ios::in | ios::out | ios::binary

aynı stream nesnesi ile farklı zamanlarda farklı dosyalar açılabilir. Ancak bu işlemler için open ve close fonksiyonlarının kullanılması gerekmektedir.

is_open
--------
bir stream nesnesine bağlı bir dosya olup olmadığını kontrol ediyor.
no:is_open fonksiyonu akım condition state değeri good olup olmadığını kontrol etmez!

text binary mod farkı
-----------------------
Çoğunlukla işletim sistemine dayalı farklılıklar var
linux kökenli sistemlerde pek fark yok ama windows için
text modunda newline 2 karakter olarak yazılıyor 13(CR) ve 10(LF)
okuma yaparken line sonunu 13 ve 10 görünce line tamamlanacak ancak sadece 10 dönecek
açılan dosya text değilse (ör image) ve kopyalama benzeri işlemler yapılıyorsa binary olarak açmak gerekiyor.

ikinci farklılık 26 byte number gelen (ctrl+z) eof muamelesi yapılacaktır.

<< veya >> operatörleri ile formatlı yazma (girilen değer karşılığı karakter (ASCII)) yazlıyor.

 ___________________________________________________________________________________________________________
|  ifstream function         | Description                                                                  |
|____________________________|______________________________________________________________________________|
|  open()                    | Opens a file                                                                 |
|  is_open()                 | Checks if a file is open                                                     |
|  close()                   | Closes a file                                                                |
|  operator>>()              | Extracts data from a file                                                    |
|  getline()                 | Reads a line from a file                                                     |
|  read()                    | Reads a block of data from a file                                            |
|  seekg()                   | Sets the position of the get pointer                                         |
|  tellg()                   | Returns the current position of the get pointer                              |
|  peek()                    | Returns the next character without extracting it from the stream             |
|  ignore()                  | Extracts and discards characters from the stream                             |
|  gcount()                  | Returns the number of characters extracted by the last unformatted input     |
|  sync()                    | Synchronizes the file buffer with the associated file                        |
|____________________________|______________________________________________________________________________|


 _______________________________________________________________________________
|  ofstream function         | Description                                      |
|____________________________|__________________________________________________|
|  open()                    | Opens a file                                     |
|  is_open()                 | Checks if a file is open                         |
|  close()                   | Closes a file                                    |
|  operator<<()              | Inserts data into a file                         |
|  write()                   | Writes a block of data to a file                 |
|  seekp()                   | Sets the position of the put pointer             |
|  tellp()                   | Returns the current position of the put pointer  |
|  flush()                   | Flushes the associated output stream             |
|____________________________|__________________________________________________|



getline
-------
template< class CharT, class Traits, class Allocator >
std::basic_istream<CharT, Traits>&
getline( std::basic_istream<CharT, Traits>& input, std::basic_string<CharT, Traits, Allocator>& str, CharT delim );

Parameters
input	-	the stream to get data from | cin
str	-	the string to put the data into | std::string
delim	-	the delimiter character     | '\n'


Positioning (Seek ve Tell fonksiyonları)
------------------------------------------

Okuma tarafında olan fonksiyonlar için seekg, yazma tarafında olan fonksiyonlar için seekp kullanılıyor.
dosya üzerinde istenilen noktaya cursor ekliyor.

basic_istream& seekg( pos_type pos );
basic_istream& seekg( off_type off, std::ios_base::seekdir dir );

 _______________________________________________________________________________________________________________________
|  Member function           | Description                                                                              |
|____________________________|__________________________________________________________________________________________|
|  seekg(pos)                | Sets the get pointer to a specific position in the input stream                          |
|  seekg(off, way)           | Moves the get pointer by a relative offset from a specific position in the  input stream |
|  tellg()                   | Returns the current position of the get pointer in the input stream                      |
|  seekp(pos)                | Sets the put pointer to a specific position in the output stream                         |
|  seekp(off, way)           | Moves the put pointer by a relative offset from a specific position in the output stream |
|  tellp()                   | Returns the current position of the put pointer in the output stream                     |
|____________________________|__________________________________________________________________________________________|

Parameters
pos	-	absolute position to set the input position indicator to.
off	-	relative position (positive or negative) to set the input position indicator to.
dir	-	defines base position to apply the relative offset to. It can be one of the following constants:
Constant	Explanation
beg	the beginning of a stream
end	the ending of a stream
cur	the current position of stream position indicator
Return value: *this

*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>


std::ostream& starline(std::ostream& os)
{
    os << "\n************************************\n";
    return os;
}

int main()
{
    using namespace std;

    ifstream ifs{ "io_operations.cpp" };
    if (ifs)
    {
        cout << ifs.rdbuf(); //bu dosyayı yazdırır. ifs ve cout format yapısı farklı olabilir.
        cout << "\n";
    }


    ofstream ofs{ "test.txt" };
    if (!ofs)
    {
        cout << "test.txt olusturulamadi\n";
    }
    else
    {
        cout << "test.txt olusturuldu\n";

        for (int i = 1; i < 101; i++)
        {
            ofs << setw(8) << i;
            if (i % 10 == 0)
                ofs << "\n";

        }

        ofs << starline << endl;
    }

    /*
    OUTPUT
    ------
       1       2       3       4       5       6       7       8       9      10
      11      12      13      14      15      16      17      18      19      20
      21      22      23      24      25      26      27      28      29      30
      31      32      33      34      35      36      37      38      39      40
      41      42      43      44      45      46      47      48      49      50
      51      52      53      54      55      56      57      58      59      60
      61      62      63      64      65      66      67      68      69      70
      71      72      73      74      75      76      77      78      79      80
      81      82      83      84      85      86      87      88      89      90
      91      92      93      94      95      96      97      98      99     100

************************************
    */



    cout.fill('_');
    cout.width(20);
    cout.setf(ios::left);

    cout << 1234 << "\n";
    //1234________________

    std::cout << boolalpha << true << "\n";
    std::cout << noboolalpha << true << "\n";
    //true
    //1

    cout << hex << uppercase << showbase << left << 17806 << "\n"; //0X458E

    cout << starline << "test" << starline;
    /*
    ************************************
    test
    ************************************
    */
    cout << dec;


    int a;
    std::cout << "Hex sayi girin: \n";
    std::cin >> hex >> a;
    std::cout << a << "\n";


    ostringstream oss;
    oss << "oss: " << 76 << " | " << 3.1415 << " " << hex << 76 << " " << dec << 76;
    std::cout << oss.str() << endl;
    //oss: 76 | 3.1415 4c 76
    oss << "ikinci yazi";
    std::cout << oss.str() << endl;
    //oss: 76 | 3.1415 4c 76ikinci yazi
    oss.str("");
    oss << "Ucuncu yazi";
    std::cout << oss.str() << endl;
    //Ucuncu yazi

    std::string str{"1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"};
    istringstream iss{ str };

    int ival;
    int sum{};

    std::vector<int> ivec{ istream_iterator<int>{iss}, {}};



    for (const auto& val : ivec)
    {
        std::cout << dec << val << " ";
    }

    std::cout << "\n" << std::accumulate(ivec.begin(), ivec.end(), 0) << "\n";

    /*
   OUTPUT
   ------
   1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
   136
   */

    while (iss >> ival)
    {
        std::cout << dec << ival << " ";
        sum += ival;
    }
    std::cout << "\n" << sum << "\n";
    /*
    OUTPUT
    ------
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    136
    */

    copy(istream_iterator<int>(cin), istream_iterator<int>{}, ostream_iterator<int>(cout, "\n")); // girilen degeri cikisa yazdirir

    //cout<< * max_element(istream_iterator<int>(cin), {})<<"\n"; //girilen degerlerden en buyugunu cikisa yazdirir







}