/*
USING TYPE ALIAS

SENTAKS
using alias = type

int yerine Word kullanmak istersek
using Word = int

using FCMP = int(*)(const char *, constchar *)
using INTA10 = int[10]
using CIPTR = const int *

using tür eş ismi verilirken templatelerle beraber kullanılanbilir. 
template <typename T>
using eq_pair = std::pair<T,T>

template <typename T>
using int_pair = std::pair<int,T>

*/

#include<utility>

int func(const char *, const char *)
{
    return 1;
}

template <typename T>
using eq_pair = std::pair<T,T>;

template <typename T>
using int_pair = std::pair<int,T>;



int main()
{
using Word = int;
Word a = 6;
using FCMP = int(*)(const char *, const char *);
FCMP fcmpr = func;

using INTA10 = int[10];
INTA10 ia;

using CIPTR = const int *;
const CIPTR p = &a;
// pointer türüne eş isim verilir ve eş isme const anahtar kullanılırsa top level const olur. yani pointer'a başka pointee atanamaz.

return 0;
}