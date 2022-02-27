#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <ctime>
using namespace std;


bool createFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumberValue)
{
	srand(time(NULL));
	fstream File("D:\\test\\" + fileName + ".txt", ios::out);

	if (!File.is_open()) 
	{
		cout << "Can't create 'test.txt'!" << endl;
		return false;
	}

	for (int i = 0; i < numbersCount; i++) {
		File << rand() % (maxNumberValue + 1) << " ";
	}

	File.close();

	File.open("D:\\test\\" + fileName + ".txt");

	if (!File.is_open()) 
	{
		cout << "Can't open 'test.txt'!" << endl;
		return false;
	}


	if (sizeof File == 0) 
	{
		cout << "File is an empty" << endl;
		return false;
	}
	else 
	{
		cout << " File was created" << endl;
		return true;
	}
}

bool isFileContainsSortedArray(const string& fileName) 
{

	fstream File("D:\\test\\" + fileName + ".txt");
	if (!File.is_open()) 
	{
		cout << "Can't create 'test.txt'!" << endl;
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
	fstream file1("D:\\test\\" + fileName + "1.txt", ios::out);
	if (!file1.is_open()) {
		cout << "Can't create 'test1.txt'!" << endl;
	}

	fstream file2("D:\\test\\" + fileName + "2.txt", ios::out);
	if (!file2.is_open()) {
		cout << "Can't create 'test2.txt'!" << endl;
	}

	fstream file3("D:\\test\\" + fileName + "3.txt", ios::out);
	if (!file3.is_open()) {
		cout << "Can't create 'test3.txt'!" << endl;
	}

	fstream file4("D:\\test\\" + fileName + "4.txt", ios::out);
	if (!file4.is_open()) {
		cout << "Can't create 'test4.txt'!" << endl;
	}

	fstream file = fstream("D:\\test\\" + fileName + ".txt");
	if (!file.is_open()) {
		cout << "Can't open 'test.txt'!" << endl;
	}

	fstream Fold[2];
	for (int i = 0; i < 2; i++) {
		Fold[i] = fstream("D:\\test\\" + fileName + to_string(i + 1) + ".txt");
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
			Fold[i] = fstream("D:\\test\\" + fileName + to_string(i + 1) + ".txt");
		}


		if (Fold[1].peek() == EOF) // Проверили на отсортированность 
		{
			file = fstream("D:\\test\\" + fileName + ".txt", ios::out);
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
			Take[i] = fstream("D:\\test\\" + fileName + to_string(i + 1) + ".txt");
		}

		for (int i = 0; i < 2; i++) {
			Fold[i] = fstream("D:\\test\\" + fileName + to_string(i + 3) + ".txt", ios::out);
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
			Fold[i] = fstream("D:\\test\\" + fileName + to_string(i + 3) + ".txt");
		}


		if (Fold[1].peek() == EOF) 
		{ 
			file = fstream("D:\\test\\" + fileName + ".txt", ios::out);
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
			Take[i] = fstream("D:\\test\\" + fileName + to_string(i + 3) + ".txt");
		}

		for (int i = 0; i < 2; i++) {
			Fold[i] = fstream("D:\\test\\" + fileName + to_string(i + 1) + ".txt", ios::out);
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
		cout << " File wasn't created" << endl;
		return -1;
	}

	sort(fileName);

	if (!isFileContainsSortedArray(fileName)) {
		cout << " File wasn't sorted correctly" << endl;
		return -2;
	}


	cout << " File was sorted correctly" << endl;
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