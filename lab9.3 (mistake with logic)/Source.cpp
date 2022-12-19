#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
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
{ // ������������ ����������� ��������:
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	int N = 0;
	int n = 26; //������� �������� � �����

	Visitor* v = new Visitor[n];
	char filename[100];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - ��������� ����������" << endl;
		cout << " [2] - ������ ���������" << endl;
		cout << " [3] - �������� ���������" << endl;
		cout << " [4] - ���������� ���������� ��� ���������" << endl;
		cout << " [5] - ����� ������ � ����� ���� ��������" << endl;
		cout << " [6] - ����� ����� � ����" << endl;
		cout << " [7] - ���������� ����� � �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			cout << "������ ������� ����������: "; cin >> N;
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
			cout << "�����, � ����� ���� ��������: " << NomerOf(v) << endl;
			break;
		case 6:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			SaveToFile(v, n, filename);
			break;
		case 7:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			LoadFromFile(v, n, filename);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
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
		cout << "³������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
		cout << " �������: "; getline(cin, v[i].prizv);
		cout << " �������: "; getline(cin, v[i].initials);
		do {
			cout << " ����� (1 - ���������, 2 - ��������): ";
			cin >> typeofnomer;
		} while (typeofnomer != 1 && typeofnomer != 2);
		v[i].type_of_nomer = (Type_Of_Nomer)typeofnomer;
		do {
			switch (v[i].type_of_nomer)
			{
			case SINGLES:
				cout << " ����� (������� ������ 1-5) : "; cin >> nomer;
				if (nomer > 5 || nomer < 1)
				{
					cout << "����������� ������ ���";
					error = 0;
					break;
				}
				if (Cheack(v, nomer, SINGLES, second) != -1)
				{
					cout << " ����� �������";
					error = 0;
					break;
				}
				v[i].SiglNomer = nomer;
				error = 1;
				break;
			case DOUBLES:
				cout << " ����� (������ ������ 6-15) : "; cin >> nomer;
				if (nomer > 15 || nomer < 6)
				{
					cout << "����������� ������ ���";
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
					cout << " ����� ��������";
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
	cout << "������ ��������� � " << i + 1 << ":" << endl;
	cin.get(); // ������� ����� ��������� � �� ����������� �������
	cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
	cout << " �������: "; getline(cin, v[i].prizv);
	cout << " �������: "; getline(cin, v[i].initials);
	do {
		cout << " ����� (1 - ���������, 2 - ��������): ";
		cin >> typeofnomer;
	} while (typeofnomer != 1 && typeofnomer != 2);
	v[i].type_of_nomer = (Type_Of_Nomer)typeofnomer;
	do {
		switch (v[i].type_of_nomer)
		{
		case SINGLES:
			cout << " ����� (������� ������ 1-5) : "; cin >> nomer; cout << endl;
			if (nomer > 5 || nomer < 1)
			{
				cout << "����������� ������ ���"; cout << endl;
				error = 0;
				break;
			}
			if (Cheack(v, nomer, SINGLES, second) != -1)
			{
				cout << " ����� �������"; cout << endl;
				error = 0;
				break;
			}
			v[i].SiglNomer = nomer;
			error = 1;
			break;
		case DOUBLES:
			cout << " ����� (������ ������ 6-15) : "; cin >> nomer;
			if (nomer > 15 || nomer < 6)
			{
				cout << "����������� ������ ���"; cout << endl;
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
				cout << " ����� ��������"; cout << endl;
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
	cout << "����� ���������:" << endl;
	cin.get(); // ������� ����� ��������� � �� ����������� �������
	cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
	cout << " �������: "; getline(cin, fprizv);
	for (int i = 0; i < 27; i++)
	{
		if (v[i].prizv == fprizv && v[i].initials == finitials)
		{
			return i;
		}
		if (visitors > 1)
		{
			cout << " ʳ���� ����������, ��������� ������ �������" << endl;
			cin.get();
			cin.sync();
			cout << " �������: "; getline(cin, finitials); cout << endl;
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
		cout << " ³�������� �� ��������" << endl;
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
	int K = 26; // ������� ��������, �� ������� ��������
	int Visit = 0;
	Visitor* t = new Visitor[K]; // ���������� �����
	int j = 0; // ������ � ����������� �����
	for (int i = 0; i < 26; i++) // ������� ������� �����
		if (i != deleted) // � ������� ��������,
			t[j++] = a[i]; // �� ������� ��������
	delete[] a; // ������� ������� �����
	a = t; // ����������� �������� �� ���������� �����
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
	ofstream fout(filename, ios::binary); // ������� ������� ���� ������
	fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
	for (int i = 0; i < N; i++)
		fout.write((char*)&v[i], sizeof(Visitor)); // �������� �������� ������
	fout.close(); // ������� ����
}
void LoadFromFile(Visitor*& v, int& N, const char* filename)
{
	delete[] v; // ������� �������� ���
	ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
	fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
	v = new Visitor[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		fin.read((char*)&v[i], sizeof(Visitor)); // ��������� �������� ������
	fin.close(); // ������� ����
}