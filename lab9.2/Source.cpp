#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Spec { COMPSCIENCE, IT, ECONOMY, PHYSICS, ART };
string specStr[] = { "комп. науки", "інформатика", "мат. та ек.", "фіз. та інф.", "труд. навч." };
struct Student
{
	string prizv;
	unsigned kurs;
	Spec spec;
	double rat_physics;
	double rat_math;
	union
	{
		double rat_prog;
		double rat_numba;
		double rat_peda;
	};
	double rat_mid;    //середній бал студента
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int LineSearch(Student* p, const int N); //для пошуку студентів з оцінками 4 та 5 а також тих хто має 5 з фізики
void Sort(Student* p, const int N);
double MiddBal(Student* p, const int i);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const double rat_mid);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	int stud_with_fif_phys;
	int ispec;
	double imid_rat;
	Spec spec;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ студентів, які вчаться без трійок" << endl;
		cout << " [4] - фізичне впорядкування даних" << endl;
		cout << " [5] - бінарний пошук студента за прізвищем, спеціальністю та середнім балом" << endl;
		cout << " [6] - індексне впорядкування та вивід даних" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			stud_with_fif_phys = LineSearch(p, N);
			cout << "Кількість студентів з оцінкою \"5\" по фізиці: " << stud_with_fif_phys << endl;
			break;
		case 4:
			Sort(p, N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			cout << " середній бал: ";
			cin >> imid_rat;
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec, imid_rat)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
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
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << "спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання): ";
		cin >> spec;
		while (spec < 0 || spec>4)
		{
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер спеціальності" << endl;
			cout << "спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання): ";
			cin >> spec;
		}
		p[i].spec = (Spec)spec;
		cout << " Оцінка з фізики: "; cin >> p[i].rat_physics;
		cout << " Оцінка з математики: "; cin >> p[i].rat_math;
		switch (p[i].spec)
		{
		case COMPSCIENCE:
			cout << " Оцінка з програмування: "; cin >> p[i].rat_prog;
			break;
		case IT:
			cout << " Оцінка з чисельних методів: "; cin >> p[i].rat_numba;
			break;
		case ECONOMY:
		case PHYSICS:
		case ART:
			cout << " Оцінка з педагогіки: "; cin >> p[i].rat_peda;
			break;
		}
		p[i].rat_mid = MiddBal(p, i);
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "=============================================================================================="
		<< endl;
	cout << "| № | Прізвище      | Курс | Спеціальність | Оцінки з: | фіз. | мат. | прог. | ч.мет. | пед. |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(3) << right << i + 1;
		cout << "| " << setw(13) << left << p[i].prizv
			<< " | " << setw(4) << right << p[i].kurs
			<< " | " << setw(13) << left << specStr[p[i].spec]
			<< " |           | " << setw(4) << p[i].rat_physics
			<< " | " << setw(4) << p[i].rat_math;
		switch (p[i].spec)


		{
		case COMPSCIENCE:
			cout << " | " << setw(5) << p[i].rat_prog << " |        |      |" << endl;
			break;
		case IT:
			cout << " |       | " << setw(6) << p[i].rat_numba << " |      |" << endl;
			break;
		case ECONOMY:
		case PHYSICS:
		case ART:
			cout << " |       |        | " << setw(4) << p[i].rat_peda << " |" << endl;
			break;
		}
	}
	cout << "=============================================================================================="
		<< endl;
	cout << endl;
}
int LineSearch(Student* p, const int N)
{
	cout << "Прізвища студентів, у яких немає трійок: " << endl;
	int n = 0, k = 0;
	for (int i = 0; i < N; i++)
	{
		if ((p[i].rat_math >= 4) && (p[i].rat_physics >= 4) && (p[i].rat_numba >= 4))
		{
			n++;
			cout << setw(2) << left << n << " :  " << p[i].prizv << endl;
		}
		if (p[i].rat_physics == 5)
			k++;
	}
	return k;
}
double MiddBal(Student* p, const int i)
{
	return (p[i].rat_math + p[i].rat_physics + p[i].rat_prog) / 3;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].spec == p[i1 + 1].spec && p[i1].rat_mid < p[i1 + 1].rat_mid)
				||
				(p[i1].spec == p[i1 + 1].spec && p[i1].rat_mid == p[i1 + 1].rat_mid && p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const double rat_mid)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].spec == spec && p[m].rat_mid == rat_mid)
			return m;
		if ((p[m].prizv < prizv)
			||
			(p[m].prizv == prizv &&
				p[m].spec < spec)
			||
			(p[m].prizv == prizv && p[m].spec == spec && p[m].rat_mid < rat_mid)
			)
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[j].spec > p[value].spec)
				||
				(p[j].spec == p[value].spec && p[j].rat_mid < p[value].rat_mid)
				||
				(p[j].spec == p[value].spec && p[j].rat_mid == p[value].rat_mid && p[j].prizv < p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "=============================================================================================="
		<< endl;
	cout << "| № | Прізвище      | Курс | Спеціальність | Оцінки з: | фіз. | мат. | прог. | ч.мет. | пед. |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(3) << right << i + 1;
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< " | " << setw(4) << right << p[I[i]].kurs
			<< " | " << setw(13) << left << specStr[p[I[i]].spec]
			<< " |           | " << setw(4) << p[I[i]].rat_physics
			<< " | " << setw(4) << p[I[i]].rat_math;
		switch (p[I[i]].spec)


		{
		case COMPSCIENCE:
			cout << " | " << setw(5) << p[I[i]].rat_prog << " |        |      |" << endl;
			break;
		case IT:
			cout << " |       | " << setw(6) << p[I[i]].rat_numba << " |      |" << endl;
			break;
		case ECONOMY:
		case PHYSICS:
		case ART:
			cout << " |       |        | " << setw(4) << p[I[i]].rat_peda << " |" << endl;
			break;
		}
	}
	cout << "=============================================================================================="
		<< endl;
}