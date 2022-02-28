#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <ctime>
#include <random> 
using namespace std;


bool createFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumberValue)
{
	mt19937 gen(time(0));
	uniform_int_distribution <int> uid(0, maxNumberValue);
	int rand_num;

	fstream File(fileName + ".txt", ios::out);

	if (!File.is_open()) 
	{
		return false;
	}

	for (int i = 0; i < numbersCount; i++) {
		rand_num = uid(gen);
		File << rand_num << " ";
	}

	File.close();

	File.open(fileName + ".txt");

	if (!File.is_open()) 
	{
		return false;
	}


	if ( File.peek() == EOF) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

bool isFileContainsSortedArray(const string& fileName) 
{

	fstream File(fileName + ".txt");
	if (!File.is_open()) 
	{
		return false;
	}

	int x, xn;

	File >> x;
	while (!File.eof()) 
	{
		File >> xn;

		if (x > xn) 
		{
			return false;
		}

		x = xn;
	}
	return true;
}







bool sort(const string& fileName)
{
	fstream file1(fileName + "1.txt", ios::out);
	if (!file1.is_open()) {
		cerr << "Can't create 'test1.txt'!" << endl;
		return false;
	}

	fstream file2(fileName + "2.txt", ios::out);
	if (!file2.is_open()) {
		cerr << "Can't create 'test2.txt'!" << endl;
		return false;
	}

	fstream file3(fileName + "3.txt", ios::out);
	if (!file3.is_open()) {
		cerr << "Can't create 'test3.txt'!" << endl;
		return false;
	}

	fstream file4(fileName + "4.txt", ios::out);
	if (!file4.is_open()) {
		cerr << "Can't create 'test4.txt'!" << endl;
		return false;
	}

	fstream file = fstream(fileName + ".txt");
	if (!file.is_open()) {
		cerr << "Can't open 'test.txt'!" << endl;
		return false;
	}

	fstream Fold[2];
	for (int i = 0; i < 2; i++) {
		Fold[i] = fstream(fileName + to_string(i + 1) + ".txt", ios:: in);
	}

	int x[2];
	int y[2];
	int x1, x2, FileNum, ElementNum;


	file >> x1; //Считываем первый элемент из файла
	FileNum = 0;
	while (!file.eof()) // Разбиение
	{
		Fold[FileNum] << x1 << " ";
		file >> x2;
		if (x1 > x2)
		{
			FileNum = 1 - FileNum; //Меняем файл, в который складываем упорядоченные последовательности 
		}
		x1 = x2;
	}
	Fold[0].close();
	Fold[1].close();
	file.close();




	for (int i = 0; ; i++) 
	{

		for (int i = 0; i < 2; i++) {
			Fold[i] = fstream(fileName + to_string(i + 1) + ".txt", ios::in);
		}


		if (Fold[1].peek() == EOF) // Проверили на отсортированность 
		{
			file = fstream(fileName + ".txt", ios::out);
			Fold[0] >> x1;

			while (!Fold[0].eof()) 
			{
				file << x1 << " ";
				Fold[0] >> x1;
			}

			file.close();
			return true;
		}

		Fold[1].close();
		Fold[0].close();


		fstream Take[2];
		for (int i = 0; i < 2; i++) {
			Take[i] = fstream(fileName + to_string(i + 1) + ".txt", ios::in);
		}

		for (int i = 0; i < 2; i++) {
			Fold[i] = fstream(fileName + to_string(i + 3) + ".txt", ios::out);
		}

		Take[0] >> x[0];
		Take[1] >> x[1];

		FileNum = 0; // Номер файла для записи
		ElementNum = 0; // Номер чтения

		while ((!Take[0].eof()) && (!Take[1].eof())) 
		{
			if (x[ElementNum] > x[1 - ElementNum]) 
			{
				ElementNum = 1 - ElementNum;
			}

			Fold[FileNum] << x[ElementNum] << " ";
			Take[ElementNum] >> y[ElementNum];

			if ((Take[ElementNum].eof()) || (x[ElementNum] > y[ElementNum])) 
			{
				ElementNum = 1 - ElementNum;
				Fold[FileNum] << x[ElementNum] << " ";
				Take[ElementNum] >> y[ElementNum];

				while ((!Take[ElementNum].eof()) && (x[ElementNum] <= y[ElementNum])) 
				{
					x[ElementNum] = y[ElementNum];
					Fold[FileNum] << x[ElementNum] << " ";
					Take[ElementNum] >> y[ElementNum];
				}

				x[1 - ElementNum] = y[1 - ElementNum];
				FileNum = 1 - FileNum;
			}

			x[ElementNum] = y[ElementNum];
		}

		while (!Take[0].eof()) 
		{
			Fold[FileNum] << x[0] << " ";
			Take[0] >> y[0];

			if (x[0] > y[0]) 
			{
				FileNum = 1 - FileNum;
			}

			x[0] = y[0];
		}

		while (!Take[1].eof()) 
		{
			Fold[FileNum] << x[1] << " ";
			Take[1] >> y[1];

			if (x[1] > y[1]) 
			{
				FileNum = 1 - FileNum;
			}

			x[1] = y[1];
		}


		Take[0].close();
		Take[1].close();
		Fold[0].close();
		Fold[1].close();


		for (int i = 0; i < 2; i++) {
			Fold[i] = fstream(fileName + to_string(i + 3) + ".txt", ios::in);
		}


		if (Fold[1].peek() == EOF) 
		{ 
			file = fstream(fileName + ".txt", ios::out);
			Fold[0] >> x1;

			while (!Fold[0].eof()) 
			{
				file << x1 << " ";
				Fold[0] >> x1;
			}

			file.close();
			return true;
		}



		for (int i = 0; i < 2; i++) {
			Take[i] = fstream(fileName + to_string(i + 3) + ".txt", ios::in);
		}

		for (int i = 0; i < 2; i++) {
			Fold[i] = fstream(fileName + to_string(i + 1) + ".txt", ios::out);
		}


		Take[0] >> x[0];
		Take[1] >> x[1];

		FileNum = 0;
		ElementNum = 0;

		while ((!Take[0].eof()) && (!Take[1].eof())) 
		{
			if (x[ElementNum] > x[1 - ElementNum]) 
			{
				ElementNum = 1 - ElementNum;
			}

			Fold[FileNum] << x[ElementNum] << " ";
			Take[ElementNum] >> y[ElementNum];

			if ((Take[ElementNum].eof()) || (x[ElementNum] > y[ElementNum])) 
			{
				ElementNum = 1 - ElementNum;
				Fold[FileNum] << x[ElementNum] << " ";
				Take[ElementNum] >> y[ElementNum];

				while ((!Take[ElementNum].eof()) && (x[ElementNum] <= y[ElementNum])) 
				{
					x[ElementNum] = y[ElementNum];
					Fold[FileNum] << x[ElementNum] << " ";
					Take[ElementNum] >> y[ElementNum];
				}

				x[1 - ElementNum] = y[1 - ElementNum];
				FileNum = 1 - FileNum;
			}

			x[ElementNum] = y[ElementNum];

		}

		while (!Take[0].eof()) 
		{
			Fold[FileNum] << x[0] << " ";
			Take[0] >> y[0];

			if (x[0] > y[0]) 
			{
				FileNum = 1 - FileNum;
			}

			x[0] = y[0];
		}

		while (!Take[1].eof()) 
		{
			Fold[FileNum] << x[1] << " ";
			Take[1] >> y[1];

			if (x[1] > y[1]) 
			{
				FileNum = 1 - FileNum;
			}
			x[1] = y[1];
		}

		Take[0].close();
		Take[1].close();
		Fold[0].close();
		Fold[1].close();
	}

	

}
int createAndSortFile(const string& fileName, const int numbersCount, const int maxNumberValue)
{
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	sort(fileName);

	if (!isFileContainsSortedArray(fileName)) {
		return -2;
	}


	return 1;
}

int main()
{
	string FileName = "test";
	const int numbersCount = 1000000;
	const int maxNumberValue = 100000;

	for (int i = 0; i < 10; i++) {
		switch (createAndSortFile(FileName, numbersCount, maxNumberValue)) {
		case 1:
			cout << "Test passed." << endl;
			break;

		case -1:
			cout << "Test failed: can't create file." << endl;
			break;

		case -2:
			cout << "Test failed: file isn't sorted." << endl;
			break;
		}
	}
	return 0;
}