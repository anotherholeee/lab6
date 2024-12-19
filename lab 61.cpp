#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <locale.h>

int safeInputInt()
{
    int value;
    while (scanf_s("%d", &value) != 1)
    {
        printf("Неверный ввод. Пожалуйста, введите целое число: ");
        while (getchar() != '\n');
    }
    return value;
}

void fillArr(int** arr, int* size, int* choice)
{
    printf("Введите размер массива:\n");
    *size = safeInputInt();
    *arr = (int*)malloc(*size * sizeof(int));

    if (*arr == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        exit(1);
    }

    if (*choice == 1)
    {
        srand(time(NULL));
        for (int i = 0; i < *size; i++)
        {
            (*arr)[i] = rand() % 100;
        }
    }
    else if (*choice == 2)
    {
        printf("Введите элементы массива:\n");
        for (int i = 0; i < *size; i++)
        {
            (*arr)[i] = safeInputInt();
        }
    }
}

void printArray(int** arr, int* size)
{
    printf("Массив: \n");
    for (int i = 0; i < *size; i++)
    {
        printf("%d ", (*arr)[i]);
    }
    printf("\n");
}

void findMinOddElement(int** arr, int* size)
{
    // Инициализация переменных для хранения первого и второго минимальных элементов и их индексов
    int firstMinElement = INT_MAX, secondMinElement = INT_MAX, firstMinIndex = 0, secondMinIndex = 0;
    int index, currentNumber;

    // Поиск первого минимального элемента и его индекса
    for (int i = 0; i < *size; i++)
    {
        if ((*arr)[i] < firstMinElement)
        {
            firstMinElement = (*arr)[i];
            firstMinIndex = i;
        }
    }

    // Поиск второго минимального элемента и его индекса, игнорируя первый минимальный элемент
    for (int j = 0; j < *size; j++)
    {
        if ((*arr)[j] <= secondMinElement && j != firstMinIndex)
        {
            secondMinElement = (*arr)[j];
            secondMinIndex = j;
        }
    }

    // Обмен индексов, если первый минимальный элемент находится после второго
    if (firstMinIndex > secondMinIndex)
    {
        int temp;
        temp = firstMinIndex;
        firstMinIndex = secondMinIndex;
        secondMinIndex = temp;
    }

    // Вычисление количества элементов между первым и вторым минимальными элементами
    int arraySize = secondMinIndex - firstMinIndex - 1;
    if (arraySize == 0)
    {
        printf("\nНет элементов для сортировки в этом диапазоне\n");
        return;
    }

    // Выделение памяти для нового массива, который будет содержать нечетные элементы
    int* array = (int*)malloc(arraySize * sizeof(int));
    if (array == NULL)
    {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    // Копирование нечетных элементов в новый массив и замена их в исходном массиве на INT_MAX
    int newSize = 0;
    for (int i = firstMinIndex + 1; i < secondMinIndex; i++)
    {
        if ((*arr)[i] % 2 != 0)
        {
            array[newSize] = (*arr)[i];
           
            newSize++;
        }
    }

    // Проверка, есть ли нечетные элементы для сортировки
    if (newSize == 0)
    {
        printf("Нет нечетных элементов для сортировки в этом диапазоне\n");
        free(array);
        return;
    }

    // Сортировка нечетных элементов методом вставки
    for (int i = 1; i < newSize; i++)
    {
        index = i;
        currentNumber = array[i];
        while (index > 0 && currentNumber < array[index - 1])
        {
            array[index] = array[index - 1];
            index--;
        }
        array[index] = currentNumber;
    }

    // Возвращение отсортированных нечетных элементов на их исходные позиции в массиве
    int counter = 0;
    for (int i = firstMinIndex + 1; i < secondMinIndex; i++)
    {
        if ((*arr)[i] == INT_MAX)
        {
            (*arr)[i] = array[counter];
            counter++;
        }
    }
    free(array);
}

int main()
{
    setlocale(LC_ALL, "");
    int endChoice;
    do
    {
        int* arr = NULL;
        int size = 0, choice = 0;

        printf("Нажмите 1, чтобы заполнить массив случайными числами, или нажмите 2, чтобы заполнить его вручную: ");
        choice = safeInputInt();

        if (choice != 1 && choice != 2)
        {
            printf("Неверный выбор. Пожалуйста, введите 1 или 2.\n");
        }
        else
        {
            fillArr(&arr, &size, &choice);
            if (size <= 1 || arr == NULL)
            {
                printf("Размер массива %d, сортировка не требуется.\n", size);
            }
            else
            {
                printArray(&arr, &size);
                findMinOddElement(&arr, &size);
                printArray(&arr, &size);
            }
            if (arr != NULL)
            {
                free(arr);
            }
        }

        printf("Нажмите 1, чтобы запустить программу снова, или нажмите 2, чтобы выйти: ");
        endChoice = safeInputInt();
        if (endChoice != 1 && endChoice != 2)
        {
            printf("Неверный выбор. Пожалуйста, введите 1 или 2.\n");
        }
    } while (endChoice != 2);
    return 0;
}
