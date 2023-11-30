#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;
//enum Kurs {};
enum Spec { KN = 0, IT, M_end_E, Ph_end_I, L_E };
string SpecStr[] = { "КН", "ІТ","М_і_Екон", "Ф_і_Інф", "Труд" };

union Mark
{
	double prog_mark;
	double chys_mark;
	double ped_mark;
};

struct Student
{
	string prizv;
	int kurs;
	Spec spec;
	double physics_mark;
	double math_mark;
	Mark third_mark;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Student_Who_have_5(Student* p, const int N);
double LineSearch(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, double math_mark);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;
	Student* p = new Student[N];

	double proc;

	Spec spec;
	string prizv;
	int ispec;
	double math_mark;
	int found;


	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ  студентів," << endl;
		cout << " які отримали з фізики оцінку 5 " << endl;

		cout << " [4] - вивід прізвищ і процент студентів які вчаться на відмінно" << endl;

		cout << " [5] - фізичне впорядкування даних" << endl;

		cout << " [6] - індексне впорядкування та вивід даних" << endl;

		cout << " [7] - бінарний пошук студента за прізвищем спеціальністю і оцінкою :" << endl << endl;

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
			cout << "Студенти які отримали з фізики 5:" << endl;
			Student_Who_have_5(p, N);
			break;
		case 4:
			proc = LineSearch(p, N);
			cout << "Процент студентів які вчаться на відмінно:" << endl;
			cout << proc << "%" << endl;
			break;
		case 5:
			Sort(p, N);
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 7:


			cout << "Введіть ключі пошуку:" << endl;
			cout << "  Спеціальність (0 - КН, 1 - ІТ, 2 - М_і_Екон, 3 - Ф_і_Інф, 4 - Труд): ";
			cin >> ispec;
			spec = (Spec)ispec;

			cin.get();
			cin.sync();

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;

			cout << "Оцінка з Математики :";
			cin >> math_mark;
			cout << endl;

			if ((found = BinSearch(p, N, prizv, spec, math_mark)) != -1)
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
	return 0;
}
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;

		cin.get();
		cin.sync();

		cout << " Прізвище: "; getline(cin, p[i].prizv);
		cout << "Курс: "; cin >> p[i].kurs;
		cout << " Спеціальність (0 - КН, 1 - ІТ, 2 - М_і_Екон, 3 - Ф_і_Інф, 4 - Труд):  ";
		cin >> spec;
		p[i].spec = static_cast<Spec>(spec);

		cout << "Оцінка з Фізики: ";
		cin >> p[i].physics_mark;
		cout << "Оцінка з Математики: ";
		cin >> p[i].math_mark;
		switch (p[i].spec)
		{
		case KN:
			cout << "Оцінка з Програмування :";
			cin >> p[i].third_mark.prog_mark;
			break;
		case IT:
			cout << "Оцінка з Чис. метод :";
			cin >> p[i].third_mark.chys_mark;
			break;
		case M_end_E:
		case Ph_end_I:
		case L_E:
			cout << "Оцінка з Педагогіки :";
			cin >> p[i].third_mark.ped_mark;
			break;
		}

	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================================================="
		<< endl;
	cout << "| № | Прізвище  | Курс | Спеціальність  | Фізика | Математика | Програмування | Чис. мед  | Педагогіка |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(10) << left << p[i].prizv
			<< "| " << setw(5) << right << p[i].kurs
			<< "| ";
		switch (p[i].spec)
		{
		case KN: cout << setw(15) << "КН";
			break;
		case IT: cout << setw(15) << "ІТ";
			break;
		case M_end_E: cout << setw(15) << "М_і_Екон";
			break;
		case Ph_end_I: cout << setw(15) << "Ф_і_Інф";
			break;
		case L_E: cout << setw(15) << "Труд";
			break;
		}
		cout << "| " << setw(7) << right << p[i].physics_mark << "| "
			<< setw(11) << p[i].math_mark;
		switch (p[i].spec)
		{
		case KN:
			cout << "|" << setw(16) << left << p[i].third_mark.prog_mark;
			cout << "|" << setw(12) << left << "Н/О";
			cout << "|" << setw(12) << left << "Н/О";
			break;
		case IT:
			cout << "|" << setw(16) << left << "Н/О";
			cout << "|" << setw(12) << left << p[i].third_mark.chys_mark;
			cout << "|" << setw(12) << left << "Н/О";
			break;
		case M_end_E:
		case Ph_end_I:
		case L_E:
			cout << "|" << setw(16) << left << "Н/О";
			cout << "|" << setw(12) << left << "Н/О";
			cout << "|" << setw(12) << left << p[i].third_mark.ped_mark;
			break;
		}
		cout << "|" << endl;

	}
	cout << "========================================================================================================="
		<< endl;
	cout << endl;
}
double LineSearch(Student* p, const int N)
{
	cout << "Прізвища студентів які вчаться на відмінно:" << endl;
	int  n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].physics_mark == 5 && p[i].math_mark == 5 && (p[i].third_mark.chys_mark == 5
			|| p[i].third_mark.ped_mark == 5
			|| p[i].third_mark.prog_mark == 5))
		{
			n++;

			cout << setw(3) << right << n
				<< " " << p[i].prizv << endl;

		}
	}
	return n * 100.0 / N;
}
void Student_Who_have_5(Student* p, const int N)
{
	for (int i = 0; i < N; i++)
	{

		if (p[i].physics_mark == 5)
		{
			cout << p[i].prizv << endl;
		}
	}
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].spec == p[i1 + 1].spec &&
					p[i1].math_mark > p[i1 + 1].math_mark)
				||
				(p[i1].spec == p[i1 + 1].spec &&
					p[i1].math_mark == p[i1 + 1].math_mark &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
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
			j >= 0 && ((p[I[j]].spec > p[value].spec)
				||
				(p[I[j]].spec == p[value].spec &&
					p[I[j]].math_mark > p[value].math_mark)
				||
				(p[I[j]].spec == p[value].spec &&
					p[I[j]].math_mark == p[value].math_mark &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "========================================================================================================="
		<< endl;
	cout << "| № | Прізвище  | Курс | Спеціальність  | Фізика | Математика | Програмування | Чис. мед  | Педагогіка |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(10) << left << p[I[i]].prizv
			<< "| " << setw(5) << right << p[I[i]].kurs
			<< "| ";
		switch (p[I[i]].spec)
		{
		case KN: cout << setw(15) << "КН";
			break;
		case IT: cout << setw(15) << "ІТ";
			break;
		case M_end_E: cout << setw(15) << "М_і_Екон";
			break;
		case Ph_end_I: cout << setw(15) << "Ф_і_Інф";
			break;
		case L_E: cout << setw(15) << "Труд";
			break;
		}
		cout << "| " << setw(7) << right << p[I[i]].physics_mark << "| "
			<< setw(11) << p[I[i]].math_mark;
		switch (p[I[i]].spec)
		{
		case KN:
			cout << "|" << setw(16) << left << p[I[i]].third_mark.prog_mark;
			cout << "|" << setw(12) << left << "Н/О";
			cout << "|" << setw(12) << left << "Н/О";
			break;
		case IT:
			cout << "|" << setw(16) << left << "Н/О";
			cout << "|" << setw(12) << left << p[I[i]].third_mark.chys_mark;
			cout << "|" << setw(12) << left << "Н/О";
			break;
		case M_end_E:
		case Ph_end_I:
		case L_E:
			cout << "|" << setw(16) << left << "Н/О";
			cout << "|" << setw(12) << left << "Н/О";
			cout << "|" << setw(12) << left << p[I[i]].third_mark.ped_mark;
			break;
		}
		cout << "|" << endl;
	}

	cout << "========================================================================================================"
		<< endl;
	cout << endl;
}
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const double math_mark)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].spec == spec && p[m].math_mark == math_mark)
			return m;
		if ((p[m].math_mark < math_mark)
			||
			(p[m].math_mark == math_mark &&
				p[m].spec < spec)
			||
			(p[m].math_mark == math_mark &&
				p[m].spec == spec &&
				p[m].prizv < prizv))
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

