#include"hash.h"
void Test1()
{
	HashTable<int,int> ht;
	
		ht.Insert(1,1);
		ht.Insert(11,11);
		ht.Insert(21,21);
		ht.Insert(23,23);
		ht.Insert(54,57);
		ht.Insert(42,12);
		ht.Remove(11);
		ht.Print();
	 // HashTable<int,int> ht1(ht);
	 // ht1.Print();
	  

	/*HashTable<int,int> ht1(ht);
	ht1.Print();
	HashTable<int,int> ht2;
	ht2 = ht1;
	ht2.Print();*/
}
void Test2()
{
	HashTable <string,string> ht;
	ht.Insert("dirtory","×Öµä");
	ht.Insert ("eat","³Ô·¹");
	ht.Insert ("sleep","Ë¯¾õ");
	ht.Print();
}
int main()
{
	Test1();
	system("pause");
	return 0;
}