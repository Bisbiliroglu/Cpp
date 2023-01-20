/*
FORWARD LIST
------------
Single linked list veri yapısını implemente ediyor.

Diğer conteiner yapılarından daha az kullanılan bir conteiner.

Her node'da bir tane pointer tutuluyor. her bir pointer bir sonraki node'u gösteriyor. 

forward iteratör kullanıyor. Bi-directional veya random access iteratör isteyen algoritmalarda kullanılamazlar. 

sinle linked list veri yapısından dolayı bazı fonksiyonlar farklı isimlendirilmiş. emplace yerine emplace after, erase yerine erase_after gibi.

Bunun nedeni ekleme ve silme işlemi sadece berilen konumdan sonraki konuma (tek pointer'ı olduğu için) erişebilmesidir. 

Sadece başlangıç durumunu gösteren anchor'u var dolayısıyla size fonksiyonu bulunmuyor. Liste boyutunu öğrenmek için tüm listeyi traverse etmek gerekiyor. 

Fron fonksiyonları var back fonksiyonları var.

insert fonksiyonu yok insert_after var.

erase fonksiyonu yok erase_after var.

begin fonksiyonu yok begin_before var. 

push_front fonksiyonu ile başa ekleme yapılabilir. 

*/