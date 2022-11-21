
class ErrA{
};
class ErrB{
};
class ErrC{
};
void handle_exception()
{
	try
	{
		throw; // rethrow	
	}
	catch(ErrA &ex)
	{
	}
	catch(ErrB &ex)
	{
	}
	catch(ErrC &ex)
	{
	}
}
void func()
{
	try{
		//hata	
	}
	catch(...)
	{
		handle_exception();
	}
}

/*

Burada oluşan tüm hataları ellipsis ile yakalamışız.Handle exceptiondan bu hata rethrow edilmiş ve tanımlanan 3 hata
sınıfı türünden biriyse yakalanacak, bunlardan biri değilse, burada rethrow edilen hata daha yüksek katmanlarda yakalanabilecek.


*/