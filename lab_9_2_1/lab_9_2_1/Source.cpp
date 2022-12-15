#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec { COMPUTERSCIENCE, IT, ECONOMY, PHYSICS, ART };

string specStr[] = { "комп'ютерні науки", "інформатика", "математика та економіка", "фізика та інформатика", "трудове навчання" };
struct Student
{
	string prizv;
	unsigned kurs;
	Spec spec;
	unsigned physicsGrades;
	unsigned mathsGrades;
	unsigned ITGrades;
	double AvGrade;

};

void Create(Student* s, const int N);
void Sort(Student* s, const int N);
void Print(Student* s, const int N);
double Average(Student* s, const int i);
int BinSearch(Student* s, const int N, const string prizv, unsigned ITGrades, const double AvGrade);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть N: "; cin >> N;

	Student* s = new Student[N];

	unsigned ITGrades;
	string prizv;
	int found;
	double AvGrade;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних"
			<< endl << endl; 
		cout << " [5] - бінарний пошук студента" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 3:
			Sort(s, N);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Бал з третього предмету: ";
			cin >> ITGrades;
			cin.get(); 
			cin.sync(); 
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			cout << " середній бал: ";
			cin >> AvGrade;
			cout << endl;
			if ((found = BinSearch(s, N, prizv, ITGrades, AvGrade)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	Create(s, N);
	Sort(s, N);
	Print(s, N);
	return 0;
}

void Create(Student* s, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, s[i].prizv);
		cout << " курс: "; cin >> s[i].kurs;
		cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання): ";
		cin >> spec;
		cout << " оцінки з фізики: "; cin >> s[i].physicsGrades;
		cout << " оцінки з математики: "; cin >> s[i].mathsGrades;
		cout << " оцінки з інформатики: "; cin >> s[i].ITGrades;
		s[i].spec = (Spec)spec;
		s[i].AvGrade = Average(s, i);
		cout << endl;
	}
}
void Print(Student* s, const int N)
{
	cout << "=================================================================================================================="
		<< endl;
	cout << "| №  | Прізвище    | курс| спеціальність          | оцінка з фізики | оцінка з математики | оцінка з інформатики |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s[i].prizv
			<< "| " << setw(3) << right << s[i].kurs << " "
			<< "| " << setw(23) << left << specStr[s[i].spec]
			<< "| " << setw(15) << right << s[i].physicsGrades << " "
			<< "| " << setw(19) << left << s[i].mathsGrades << " "
			<< "| " << setw(20) << right << s[i].ITGrades << " " << "|";
		cout << endl;
	}
	cout << "================================================================================================================="
		<< endl;
	cout << endl;
}

double Average(Student* s, int i) {
	double av;
	av = (s[i].mathsGrades + s[i].ITGrades + s[i].physicsGrades) / 3;
	return av;
}

void Sort(Student* s, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((s[i1].ITGrades > s[i1 + 1].ITGrades)
				||
				(s[i1].ITGrades == s[i1 + 1].ITGrades &&
					Average(s, i1) > Average(s, i1+1))
						||
						(s[i1].ITGrades == s[i1 + 1].ITGrades &&
							Average(s, i1) == Average(s, i1 + 1) &&
								(s[i1].prizv > s[i1 + 1].prizv)))
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
}

int* IndexSort(Student *s, const int N)
{
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value;
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((s[I[j]].ITGrades > s[value].ITGrades)
				||
				(s[I[j]].ITGrades == s[value].ITGrades &&
				(Average(s, I[j]) > Average(s, value)))
				||
				(s[I[j]].ITGrades == s[value].ITGrades &&
				(Average(s, I[j]) == Average(s, value))) &&
				(s[I[j]].prizv > s[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{
	cout << "=================================================================================================================="
		<< endl;
	cout << "| №  | Прізвище    | курс| спеціальність          | оцінка з фізики | оцінка з математики | оцінка з інформатики |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s[I[i]].prizv
			<< "| " << setw(3) << right << s[I[i]].kurs << " "
			<< "| " << setw(23) << left << specStr[s[I[i]].spec]
			<< "| " << setw(15) << right << s[I[i]].physicsGrades << " "
			<< "| " << setw(19) << left << s[I[i]].mathsGrades << " "
			<< "| " << setw(20) << right << s[I[i]].ITGrades << " " << "|";
		cout << endl;
	}
	cout << "================================================================================================================="
		<< endl;
	cout << endl;
}

int BinSearch(Student* s, const int N, const string prizv, unsigned ITGrades, const double AvGrade)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].prizv == prizv && s[m].ITGrades == ITGrades && s[m].AvGrade == AvGrade)
			return m;
		if ((s[m].prizv < prizv)
			||
			(s[m].prizv == prizv &&
				s[m].ITGrades < ITGrades)
			||
			(s[m].prizv == prizv && s[m].ITGrades == ITGrades && s[m].AvGrade < AvGrade)
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