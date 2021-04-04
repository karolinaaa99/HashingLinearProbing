#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

class HashTable1
{
private:
	string* t;  //tablica z haszowaniem
	int* searchTo; //tablica zawierajaca informacje na temat tego, gdzie w tablicy z haszowaniem znajduje sie string, potrzebna do metody del
	int capacity; //maksymalna pojemnosc tablicy z haszowaniem
	int ht_size; //liczba elementow w tablicy z haszowaniem
public:
	HashTable1(int c); //konstruktor tworzący pustą tablicę z haszowaniem o pojemności c
	int hashF(string s); //funkcja haszująca dla ciągu s, wyznacza jego indeks w tablicy z haszowaniem, czyli wyznacza hasz tego stringa s
	void insert(string s); //wstawienie ciągu s do tablicy z haszowaniem
	string search(string s);//wyszukuje i zwraca s
	int searchs(string s);//wyszukuje i zwraca t[s], czyli zwraca wartosc haszu dla stringa s
	void del(string s); //usuwa lancuch s z tablicy z haszowaniem
	friend ostream& operator<<(ostream& out, HashTable1& ht); //wypisuje tablicę z haszowaniem (z numerami pól), pozostawia puste dla wolnych pól
};

HashTable1::HashTable1(int c)
{
	capacity = c;
	t = new string[capacity];
	ht_size = 0;
	searchTo = new int[capacity];
	for (int i = 0; i < capacity; i++)
	{
		searchTo[i] = -1; //-1 mowi, ze w tablicy z haszowaniem nie ma stringa o okreslonym haszu(indeksie)
	}

	/**t = new string[c];
	searchTo = new int[c];
	this->ht_size = 0;
	this->capacity = c;**/
	for (int i = 0; i < capacity; ++i)
	{
		t[i] = "";
		searchTo[i] = -1;
	}
}

int HashTable1::hashF(string s)
{
	unsigned long int wynik = 0;

	for (int n = 0; n < s.size(); n++)
	{
		wynik += (unsigned)(s[n] * (int)pow(11, s.size() - n));
		wynik %= capacity;
	}

	return (int)wynik;
	
	/**int d = s.length(); //zwraca liczbe liter wchodzaca w sklad stringa
	unsigned long long int suma; //unsigned, bo indeksy w tablicy nie moga byc ujemne
	suma = 0;
	for (int i = 0; i < d; i++) //tyle razy ile jest liter w stringu
		suma += (unsigned int)(pow(13, d - i - 1) * s[i]);
	return suma % capacity; //return hash**/

}

void HashTable1::insert(string s)
{
	int konflikt = 0; //mowi ile bylo konfliktow
	int temp; //w zmiennej temp zapisujemy wartosc haszu dla stringa s
	temp = hashF(s);
	int perm = temp;
	if (t[temp] != "") //pod tym indeksem juz jest jakis string
	{
		++konflikt; //wystepuje konflikt
		++temp; //wykonujemy probkowanie liniowe, czyli szukamy pierwszego wolnego miejsca w tablicy z haszowaniem
		while (t[temp] != "")
		{
			temp = (temp + 1) % capacity;
		}
		t[temp] = s; //wstawiamy stringa do tablicy z haszowaniem
		searchTo[perm] = temp+1;

		ht_size++; //zwiekszamy liczbe elementow tablicy z haszowaniem
	}
	else //jesli jest miejsce pod tym haszem(indeksem)
	{
		t[temp] = s;
		searchTo[temp] = temp;
		ht_size++;
	}
}

string HashTable1::search(string s)
{
	int wart;
	wart = hashF(s);
	int hLast = searchTo[wart];

	if (s == t[wart])
		return s;
	else
	{
		for (int i = 0; i < capacity; i++)
		{
			if ((wart+i)%capacity == hLast)
			{
				break;
			}
			if (s == t[(wart + i) % capacity])
				return s;
		}
		return "-1"; //elemetu nie ma w tablicy z haszowaniem
	}
}

int HashTable1::searchs(string s)
{
	int wart;
	wart = hashF(s);
	int hLast = searchTo[wart];

	if (s == t[wart])
		return wart;
	else
	{

		for (int i = 0; i < capacity; i++)
		{
			if (((wart+i)%capacity) == hLast) //przerwanie, jesli takiego stringa nie ma w tablicy z haszowaniem
			{
				break;
			}
			if (s == t[(wart + i) % capacity])
				return (wart + i) % capacity;
		}
		return -1;
	}
}

void HashTable1::del(string s)
{
	if (ht_size == 0) //jesli tablica z haszowaniem jest pusta
	{
		return;
	}

	int wart = searchs(s); //gdzie ten string sie znajduje

	if (wart != -1) 
	{
		t[wart].clear(); //za pomoca metody clear dla stringow usuwamy stringa z tablicy pod indeksem wart
		searchTo[wart] = -1;
		ht_size--;
	}
}

ostream& operator<<(ostream& out, HashTable1& ht)
{
	for (int i = 0; i < ht.capacity; i++)
	{
		out << "[" << i << "] "
			<< ht.t[i] << endl;
	}
	return out;
}

int main()
{
	/**int n=40;
	string tab[n] = { "Julia", "Zuzanna",
"Zofia", "Lena", "Maja", "Hanna",
	"Amelia", "Alicja", "Maria",
"Aleksandra", "Oliwia", "Natalia",
"Wiktoria", "Emilia",
	"Antonina", "Laura", "Pola",
"Iga","Anna","Liliana",
"Antoni","Jakub", "Jan", "Szymon",

"Franciszek","Filip","Aleksander","Mikolaj",
"Wojciech", "Kacper", "Adam",
"Michal",
	"Marcel", "Stanislaw", "Wiktor",
"Piotr", "Igor","Leon","Nikodem",
"Mateusz" };
	HashTable1 H(40);
	for(int i=0; i<n; i++){
		H.insert(tab[i]);
	}**/

	//HashTable1 h(41);
	HashTable1 h(40);

	h.insert("Julia");
	h.insert("Zuzanna");
	h.insert("Zofia");
	h.insert("Lena");
	h.insert("Maja");
	h.insert("Hanna");
	h.insert("Amelia");
	h.insert("Alicja");
	h.insert("Maria");
	h.insert("Aleksandra");
	h.insert("Oliwia");
	h.insert("Natalia");
	h.insert("Wiktoria");
	h.insert("Emilia");
	h.insert("Antonina");
	h.insert("Laura");
	h.insert("Pola");
	h.insert("Iga");
	h.insert("Anna");
	h.insert("Liliana");
	h.insert("Antoni");
	h.insert("Jakub");
	h.insert("Jan");
	h.insert("Szymon");
	h.insert("Franciszek");
	h.insert("Filip");
	h.insert("Aleksander");
	h.insert("Mikołaj");
	h.insert("Wojciech");
	h.insert("Kacper");
	h.insert("Adam");
	h.insert("Michal");
	h.insert("Marcel");
	h.insert("Stanislaw");
	h.insert("Wiktor");
	h.insert("Piotr");
	h.insert("Igor");
	h.insert("Leon");
	h.insert("Nikodem");
	h.insert("Mateusz");

	cout << h << endl;
	cout << h.search("Antoni") << " ";
	cout << h.searchs("Antoni") << endl;

	h.del("Nikodem");
	cout << h << endl;

	return 0;
}