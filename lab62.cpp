#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
const int UPPER_INPUT = 100;
int inputCheck(char* value, int LIMIT)
{
	int i = 0, sign = 1, number = 0, m = 0;
	if (value[0] == '-') {
		sign = -1;
		i = 1;
	}
	else if (value[0] == '+') {
		i = 1;
	}
	for (; value[i] != '\0'; i++)
	{
		if (value[i] < '0' || value[i] > '9') {
			printf("Error: Invalid characters have been entered.\n");
			return INT_MAX;
		}
		int digit = value[i] - '0';
		if (sign == 1 && (number > (LIMIT - digit) / 10)) {
			printf("Error: int type overflow.\n");
			return INT_MAX;
		}
		else if (sign == -1 && (number > (LIMIT - digit) / 10)) {
			printf("Error: int type overflow.\n");
			return INT_MAX;
		}
		number = number * 10 + digit;
	}
	number *= sign;
	return number;
}
int input(int LIMIT)
{
	char* value;
	int isCorrect = 0, q = 0;
	while (isCorrect == 0)
	{
		value = (char*)malloc(sizeof(char) * 11);
		scanf_s("%11s", value, 12);
		if (getchar() != '\n')
		{
			printf("Error: there are too many elements in the row, or there are spaces\n");
			while (getchar() != '\n');
			value = NULL;
		}
		else if (inputCheck(value, LIMIT) != INT_MAX)
		{
			isCorrect = 1;
		}
		else
		{
			value = NULL;
		}
	}
	return inputCheck(value, LIMIT);
}
#include <stdio.h>
#include <stdlib.h>
void mergeSort(int* arr, int* arr2, int** matrix, int n, int l) {
	int* tempArray = (int*)malloc(n * sizeof(int));
	int rbegin, rend;
	int i, j, m;

	for (int k = 1; k < n; k *= 2) {
		for (int left = 0; left + k < n; left += k * 2) {
			rbegin = left + k;
			rend = rbegin + k;
			if (rend > n)
				rend = n;
			m = left;
			i = left;
			j = rbegin;

			while (i < rbegin && j < rend) {
				if (arr[i] <= arr[j]) {
					tempArray[m] = arr[i];
					i++;
				}
				else {
					tempArray[m] = arr[j];
					j++;
				}
				m++;
			}

			while (i < rbegin) {
				tempArray[m] = arr[i];
				i++;
				m++;
			}

			while (j < rend) {
				tempArray[m] = arr[j];
				j++;
				m++;
			}

			for (m = left; m < rend; m++) {
				arr[m] = tempArray[m];
			}
		}
	}
	printf("\nYour sort matrix is:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i] == arr2[j])
			{
				for (int q = 0; q < l; q++)
				{
					printf("%d ", matrix[j][q]);
				}
				arr2[j] = INT_MAX;
				break;
			}
		}
		printf("\n");
	}
	free(tempArray);
}
void sort1(int numberOfElements, int* arrayOfNumbers)
{
	int number = 0, i, j, jj = -1, temp = 0;
	for (i = 1; i < numberOfElements; i++, i++)
	{
		number = arrayOfNumbers[i];
		for (j = i; j < numberOfElements; j++, j++)
		{
			if (number > arrayOfNumbers[j])
			{
				number = arrayOfNumbers[j];
				jj = j;
			}
		}
		temp = arrayOfNumbers[i];
		arrayOfNumbers[i] = number;
		if (jj >= 0)
			arrayOfNumbers[jj] = temp;
	}
	printf_s("Your array is \n");
	for (i = 0; i < numberOfElements; i++)
	{
		printf_s("%d ", arrayOfNumbers[i]);
	}
}
void sort2(int** matrix, int numberOfColumns, int numberOfRows)
{
	int* sumOfMatrix;
	int* sumOfMatrix2;
	int i = 0, j = 0;
	sumOfMatrix = (int*)calloc(numberOfRows, sizeof(int*));
	sumOfMatrix2 = (int*)calloc(numberOfRows, sizeof(int*));
	for (i = 0; i < numberOfRows; i++)
	{
		for (j = 1; j < numberOfColumns; j++, j++)
		{
			sumOfMatrix[i] += matrix[i][j];
			sumOfMatrix2[i] += matrix[i][j];
		}

	}
	mergeSort(sumOfMatrix, sumOfMatrix2, matrix, numberOfRows, numberOfColumns);
}
void task1()
{
	int numberOfElements = 0, i = 0, n = 0, random = 0, number = 0;
	int* arrayOfNumbers;
	srand(time(NULL));
	while (numberOfElements < 1)
	{
		printf_s("Enter the number of elements(it is possible with the leading zeros and the + sign)\n");
		numberOfElements = input(UPPER_INPUT);
		if (numberOfElements < 1)
		{
			printf_s("Please, again\n");
		}
	}
	arrayOfNumbers = (int*)calloc(numberOfElements, sizeof(int));
	printf_s("If you want to use random to fill the array - enter 1\n");
	printf_s("Otherwise - enter 2\n");
	while (random < 1 || random>2)
	{
		random = input(3);
		if (random < 1 || random>2)
		{
			printf_s("Please, again\n");
		}
	}
	if (random == 2)
	{
		for (i = 0; i < numberOfElements; i++)
		{
			printf_s("Please enter the value of the array element under the number %d\n", i + 1);
			arrayOfNumbers[i] = input(INT_MAX);
		}
	}
	else
	{
		for (i = 0; i < numberOfElements; i++)
		{
			arrayOfNumbers[i] = rand() % 200 - 99;
		}
	}
	printf_s("Your array is \n");
	for (i = 0; i < numberOfElements; i++)
	{
		printf_s("%d ", arrayOfNumbers[i]);
	}
	printf_s("\n");
	sort1(numberOfElements, arrayOfNumbers);
}
void task2()
{
	int numberOfRows = 0, numberOfColumns = 0, i, j, a = 1, n = 0, random = 0;
	int** matrix = NULL;
	srand(time(NULL));
	while (numberOfRows < 1)
	{
		printf_s("Enter the number of rows (it is possible with the leading zeros and the + sign)\n");
		printf_s("Write using enter\n");
		numberOfRows = input(UPPER_INPUT);
		if (numberOfRows < 1)
		{
			printf_s("Please, again\n");
		}
	}
	while (numberOfColumns < 1)
	{
		printf_s("Enter the number of columns (it is possible with the leading zeros and the + sign)\n");
		printf_s("Write using enter\n");
		numberOfColumns = input(UPPER_INPUT);
		if (numberOfColumns < 1)
		{
			printf_s("Please, again\n");
		}
	}
	matrix = (int**)calloc(numberOfRows, sizeof(int*));
	for (i = 0; i < numberOfRows; i++) {
		matrix[i] = (int*)malloc(numberOfColumns * sizeof(int));
	}
	printf_s("If you want to use random to fill the matrix - enter 1\n");
	printf_s("Otherwise - enter 2\n");
	while (random < 1 || random>2)
	{
		random = input(UPPER_INPUT);
		if (random < 1 || random>2)
		{
			printf_s("Please, again\n");
		}
	}
	if (random == 2)
	{
		printf_s("Enter the matrix:\n");
		for (i = 0; i < numberOfRows; i++)
		{
			for (j = 0; j < numberOfColumns; j++)
			{
				matrix[i][j] = input(INT_MAX);
			}
			printf("\n");
		}
	}
	else
	{
		for (i = 0; i < numberOfRows; i++)
		{
			for (j = 0; j < numberOfColumns; j++)
			{
				matrix[i][j] = rand() % 200 - 100 + 1;
			}
		}
	}
	printf_s("Your matrix is \n");
	for (i = 0; i < numberOfRows; i++)
	{
		for (j = 0; j < numberOfColumns; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	sort2(matrix, numberOfColumns, numberOfRows);

}
void main()
{
	printf_s("Hello, this is Laba6\nPlease enter the number of task(1,2)\n");
	int numberOfTask = 0, userWork = 1;
	while (userWork) {
		while (numberOfTask < 1 || numberOfTask>2)
		{
			numberOfTask = input(4);
			if (numberOfTask < 1 || numberOfTask>2)
			{
				printf_s("Please, again\n");
			}
		}
		if (numberOfTask == 1)
		{
			task1();
		}
		else
		{
			task2();
		}
		numberOfTask = 0;
		printf_s("If you want to repeat press space,\nelse press any key\n");
		if (_getch() == ' ')
		{
			printf_s("Please enter the number of task(1, 2)\n");
		}
		else
		{
			printf_s("GoodBye");
			userWork = 0;
		}
	}
}