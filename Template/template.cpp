/*
Kaynakça
https://github.com/umutkotankiran/Cpp/blob/main/25_01_08_2021/main.cpp


Derleyicinin bizim yerimize kod yazmasını istersek templateler kullanırız.
Derleyiciye templateler ile bir şablon verilir ve bu şablonlar ile türden bağımsız şekilde kod yazılabilir.
Türden bağımsız yazıldığı için algoritmalar daha üst düzey bir soyutlama yapılır. 
Örnek olarak iki int nesnenin swap edilmesi değil de iki nesnenin swap edilmesi gibi.
Programcı template yazdıktan sonra derleyici bu template'i kullanarak kendi gerçek kodu her örneği için compile time'da yazıyor. 
Bu işleme template instantiation denir. Yazılan her bir gerçek koda ise templatein o tür için template specialization'ı denir. 
C++ ın çok büyük kısmını STL oluşturuyor. STL açılımı Standard Template Library. 


Temel Kategorilere ayrılıyor.
- Function Templates
- Class Templates
- Alias Template		C++11 ile geldi
- Variable Template		C++11 ile geldi
- Concept Template		C++20 ile geldi



*/