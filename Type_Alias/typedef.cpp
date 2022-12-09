/*

1. Hangi türe eş isim vereceksen o türden bir değişken tanımla
2. başına typedef .... koy
3. değişkeninin ismini tür eş ismi olarak değiştir.

örnek int yerine word eş ismi vermek
1. int a;
2. typedef int a;
3. typedef int word;

örnek int[10] türüne INtA10 ismini vermek

1. int[10] a;
2. typedef int a[10];
3. typedef int INTA10[10] ;

örnek int (*)(double, double) türüne fptr eş ismi verilmesi
1. int (*a)(double, double) 
2. typedef int (*a)(double, double) 
3. typedef int (*fptr)(double, double) 

Not: typedef ile yapılan tür eş isimleri template haline getirilemiyor. using keywordu ile yapılan tür eş isimleri templateler ile kullanılabiliyor. 

*/

int main()
{
    typedef int word;
    word w = 5;

    typedef int INTA10[10] ;
    INTA10 ia;

    typedef int (*fptr)(double, double) ;
    fptr func;

    return 0;
}