/*
std::move
---------
Bir conteinerdaki ögelerin başka bir conteinara taşınması için kullanılan algoritmadır. 


Not: utility header dosyasında bulunan ve değişkenlerin value categorysinin L valuedab R value'e cast eden, move fonksiyonu ile karıştıtılmamalıdır. 


template<class InputIt, class OutputIt>
OutputIt move(InputIt first, InputIt last, OutputIt d_first)
{
    for (; first != last; ++d_first, ++first)
        *d_first = std::move(*first);
 
    return d_first;
}

sentaks
move(source.beg, source.end, dest.beg)
*/


