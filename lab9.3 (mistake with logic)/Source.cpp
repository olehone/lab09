#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Type_Of_Nomer { SINGLES = 1, DOUBLES = 2 };
struct Visitor
{
	string prizv;
	string initials;
	Type_Of_Nomer type_of_nomer;
	union {
		int SiglNomer;
		int DoublNomer;
	};
};
int Cheack(Visitor* v, int searchnomer, Type_Of_Nomer type_of_nomer, int& second);
void Create(Visitor* v, int N);
void Add(Visitor* v, int N);
int Find(Visitor* v);
void Delete(Visitor*& a, Visitor* v);
int NomerOf(Visitor* v);
void SaveToFile(Visitor* v, const int N, const char* filename);
void LoadFromFile(Visitor*& v, int& N, const char* filename);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	int N = 0;
	int n = 26; //кількість елементів в масиві

	Visitor* v = new Visitor[n];
	char filename[100];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - Заселення відвідувачів" << endl;
		cout << " [2] - Додати відвідувача" << endl;
		cout << " [3] - Видалити відвідувача" << endl;
		cout << " [4] - Редагувати інформацію про відвідувача" << endl;
		cout << " [5] - Пошук номера в якому живе відвідувач" << endl;
		cout << " [6] - Запис даних у файл" << endl;
		cout << " [7] - Зчитування даних з файлу" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			cout << "Введіть кількість відвідувачів: "; cin >> N;
			Create(v, N);
			break;
		case 2:
			Add(v, N++);
			break;
		case 3:
			Delete(v, v);
			break;
		case 4:
			Delete(v, v);
			Add(v, N++);
			break;
		case 5:
			cout << "Номер, в якому живе відвідувач: " << NomerOf(v) << endl;
			break;
		case 6:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(v, n, filename);
			break;
		case 7:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(v, n, filename);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
int Cheack(Visitor* v, int searchnomer, Type_Of_Nomer type_of_nomer, int& second)
{
	int two = 0;
	if (type_of_nomer == SINGLES)
		for (int i = 0; i < 26; i++)
		{
			if (v[i].SiglNomer == searchnomer)
				return i;
		}
	if (type_of_nomer == DOUBLES)
		for (int i = 0; i < 26; i++)
		{
			if (v[i].DoublNomer == searchnomer)
			{
				if (two != 1)
				{
					second = i;
					two++;
				}
				else return i;
			}
		}
	return -1;
}
void Create(Visitor* v, int N)
{
	int typeofnomer;
	unsigned nomer;
	int error;
	for (int i = 0; i < N; i++)
	{
		int first = -1;
		int second = -1;
		cout << "Відвідувач № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		cout << " Прізвище: "; getline(cin, v[i].prizv);
		cout << " Ініціали: "; getline(cin, v[i].initials);
		do {
			cout << " Номер (1 - одномісний, 2 - двомісний): ";
			cin >> typeofnomer;
		} while (typeofnomer != 1 && typeofnomer != 2);
		v[i].type_of_nomer = (Type_Of_Nomer)typeofnomer;
		do {
			switch (v[i].type_of_nomer)
			{
			case SINGLES:
				cout << " Номер (одномісні номери 1-5) : "; cin >> nomer;
				if (nomer > 5 || nomer < 1)
				{
					cout << "Неправильно введені дані";
					error = 0;
					break;
				}
				if (Cheack(v, nomer, SINGLES, second) != -1)
				{
					cout << " Номер зайнято";
					error = 0;
					break;
				}
				v[i].SiglNomer = nomer;
				error = 1;
				break;
			case DOUBLES:
				cout << " Номер (двомісні номери 6-15) : "; cin >> nomer;
				if (nomer > 15 || nomer < 6)
				{
					cout << "Неправильно введені дані";
					error = 0;
					break;
				}
				nomer = nomer - 6;
				first = Cheack(v, nomer, DOUBLES, second);
				if (second == -1)
				{
					v[i].DoublNomer = nomer;
					error = 1;
					break;
				}
				if (second != -1 && first == -1)
				{
					v[i].DoublNomer = nomer;
					error = 1;
					break;
				}
				if (first != -1 && second != -1)
				{
					cout << " Номер зайнятий";
					error = 0;
				}
			}
		} while (error != 1);
		cout << endl;
	}
}
void Add(Visitor* v, int N)
{
	int typeofnomer;
	unsigned nomer;
	int error;
	int i = N;
	int first = -1;
	int second = -1;
	cout << "Додати відвідувача № " << i + 1 << ":" << endl;
	cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
	cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
	cout << " Прізвище: "; getline(cin, v[i].prizv);
	cout << " Ініціали: "; getline(cin, v[i].initials);
	do {
		cout << " Номер (1 - одномісний, 2 - двомісний): ";
		cin >> typeofnomer;
	} while (typeofnomer != 1 && typeofnomer != 2);
	v[i].type_of_nomer = (Type_Of_Nomer)typeofnomer;
	do {
		switch (v[i].type_of_nomer)
		{
		case SINGLES:
			cout << " Номер (одномісні номери 1-5) : "; cin >> nomer; cout << endl;
			if (nomer > 5 || nomer < 1)
			{
				cout << "Неправильно введені дані"; cout << endl;
				error = 0;
				break;
			}
			if (Cheack(v, nomer, SINGLES, second) != -1)
			{
				cout << " Номер зайнято"; cout << endl;
				error = 0;
				break;
			}
			v[i].SiglNomer = nomer;
			error = 1;
			break;
		case DOUBLES:
			cout << " Номер (двомісні номери 6-15) : "; cin >> nomer;
			if (nomer > 15 || nomer < 6)
			{
				cout << "Неправильно введені дані"; cout << endl;
				error = 0;
				break;
			}
			nomer = nomer - 6;
			first = Cheack(v, nomer, DOUBLES, second);
			if (second == -1)
			{
				v[i].DoublNomer = nomer;
				error = 1;
				break;
			}
			if (second != -1 && first == -1)
			{
				v[i].DoublNomer = nomer;
				error = 1;
				break;
			}
			if (first != -1 && second != -1)
			{
				cout << " Номер зайнятий"; cout << endl;
				error = 0;
			}
		}
	} while (error != 1);
	cout << endl;
}
int Find(Visitor* v)
{
	int visitors = 0;
	int index = -1;
	string fprizv;
	string finitials;
	cout << "Пошук відвідувача:" << endl;
	cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
	cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
	cout << " Прізвище: "; getline(cin, fprizv);
	for (int i = 0; i < 27; i++)
	{
		if (v[i].prizv == fprizv && v[i].initials == finitials)
		{
			return i;
		}
		if (visitors > 1)
		{
			cout << " Кілька відвідувачів, необхідно ввести ініціали" << endl;
			cin.get();
			cin.sync();
			cout << " Ініціали: "; getline(cin, finitials); cout << endl;
			i = 0;
			visitors = 0;
		}
		if (v[i].prizv == fprizv)
		{
			index = i;
			visitors++;
		}
	}
	switch (visitors)
	{
	case 0:
		cout << " Відвідувача не знайдено" << endl;
		return -1;
	case 1:
		return index;
	default:
		return -1;
	}
}
void Delete(Visitor*& a, Visitor* v)
{
	int deleted = Find(v);
	if (deleted == -1)
		return;
	int K = 26; // кількість елементів, які потрібно залишити
	int Visit = 0;
	Visitor* t = new Visitor[K]; // тимчасовий масив
	int j = 0; // індекс в тимчасовому масиві
	for (int i = 0; i < 26; i++) // скануємо заданий масив
		if (i != deleted) // і копіюємо елементи,
			t[j++] = a[i]; // які потрібно залишити
	delete[] a; // знищуємо заданий масив
	a = t; // налаштовуємо вказівник на тимчасовий масив
}
int NomerOf(Visitor* v)
{
	int index = Find(v);
	if (index == -1)
		return -1;
	switch (v[index].type_of_nomer)
	{
	case SINGLES:
		return v[index].SiglNomer;
	case DOUBLES:
		return 6 + v[index].DoublNomer;
	}

}
void SaveToFile(Visitor* v, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
		fout.write((char*)&v[i], sizeof(Visitor)); // записали елементи масиву
	fout.close(); // закрили файл
}
void LoadFromFile(Visitor*& v, int& N, const char* filename)
{
	delete[] v; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	v = new Visitor[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&v[i], sizeof(Visitor)); // прочитали елементи масиву
	fin.close(); // закрили файл
}