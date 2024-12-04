#include <iostream>
#include <iomanip> // Для std::setw
#include <Windows.h> // Для работы с Windows API
#include <thread> // Для использования std::this_thread::sleep_for
#include <random>
#include <chrono>

using namespace std;

const int MAX_SIZE = 10;

void subtractAndDisplay(int** matrix1, int** matrix2, int N) {
    cout << "Результат вычитания второй матрицы из первой:" << endl;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int result = matrix2[i][j] - matrix1[i][j];
            cout << setw(4) << result;
            cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        cout << endl;
    }
}

void fillMatrixRandom(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % (N * N) + 1;
        }
    }
}

void fillMatrixSequential(int** matrix, int N) {
    int value = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = value++;
        }
    }
}

void setCursorPosition(HANDLE hStdout, int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hStdout, coord);
}

void fillAndPrintMatrix(int* matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << *(matrix + i * N + j);
        }
        cout << endl;
    }
}

void fillAndPrintVerticalSnake(HANDLE hStdout, int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, N * N);
    int value = 1;
    int startRow = 1;
    setCursorPosition(hStdout, 0, startRow);
    cout << "Задание 1" << endl;

    for (int j = 0; j < N; ++j) {
        if (j % 2 == 0) { // Четные столбцы
            for (int i = 0; i < N; ++i) {
                setCursorPosition(hStdout, j * 5, startRow + i + 2); // Позиция для вывода с учётом отступа
                cout << setw(4) << dis(gen);
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(200));
            }
        }
        else { // Нечетные столбцы
            for (int i = N - 1; i >= 0; --i) {
                setCursorPosition(hStdout, j * 5, startRow + i + 2); // Позиция для вывода с учётом отступа
                cout << setw(4) << dis(gen);
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(200));
            }
        }
    }
}

void fillAndPrintSpiral(HANDLE hStdout, int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, N * N);
    int value = 1;
    int left = 0, right = N - 1, top = 0, bottom = N - 1;

    while (left <= right && top <= bottom) {
        // Заполняем верхнюю строку
        for (int i = left; i <= right; ++i) {
            setCursorPosition(hStdout, i * 5, top + N + 4); // Позиция для вывода с отступом вниз
            cout << setw(4) << dis(gen);
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        top++;

        // Заполняем правый столбец
        for (int i = top; i <= bottom; ++i) {
            setCursorPosition(hStdout, right * 5, i + N + 4); // Позиция для вывода с отступом вниз
            cout << setw(4) << dis(gen);
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        right--;

        // Заполняем нижнюю строку
        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                setCursorPosition(hStdout, i * 5, bottom + N + 4); // Позиция для вывода с отступом вниз
                cout << setw(4) << dis(gen);
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(200));
            }
            bottom--;
        }

        // Заполняем левый столбец
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                setCursorPosition(hStdout, left * 5, i + N + 4); // Позиция для вывода с отступом вниз
                cout << setw(4) << dis(gen);
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(200));
            }
            left++;
        }
    }
}

void printQuadrantsA(int* matrix, int N) {
    int halfN = N / 2;

    // Создаем массив для хранения квадрантов
    int* quadrants[4];

    // Выделяем память для каждого квадранта
    for (int i = 0; i < 4; ++i) {
        quadrants[i] = new int[halfN * halfN];
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            quadrants[0][i * halfN + j] = *(matrix + i * N + j);
            quadrants[1][i * halfN + j] = *(matrix + i * N + (j + halfN));
            quadrants[2][i * halfN + j] = *(matrix + (i + halfN) * N + j);
            quadrants[3][i * halfN + j] = *(matrix + (i + halfN) * N + (j + halfN));
        }
    }

    cout << "Матрица в порядке 4-1-2-3 (A):" << endl;
    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[2][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[0][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[3][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[1][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < 4; ++i) {
        delete[] quadrants[i];
    }
}

void printQuadrantsB(int* matrix, int N) {
    int halfN = N / 2;

    // Создаем массив для хранения квадрантов
    int* quadrants[4];

    // Выделяем память для каждого квадранта
    for (int i = 0; i < 4; ++i) {
        quadrants[i] = new int[halfN * halfN];
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            quadrants[0][i * halfN + j] = *(matrix + i * N + j);
            quadrants[1][i * halfN + j] = *(matrix + i * N + (j + halfN));
            quadrants[2][i * halfN + j] = *(matrix + (i + halfN) * N + j);
            quadrants[3][i * halfN + j] = *(matrix + (i + halfN) * N + (j + halfN));
        }
    }

    cout << "Матрица в порядке 3-4-1-2 (B):" << endl;
    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[3][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[2][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[1][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[0][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < 4; ++i) {
        delete[] quadrants[i];
    }
}

void printQuadrantsC(int* matrix, int N) {
    int halfN = N / 2;

    int* quadrants[4];

    // Выделяем память для каждого квадранта
    for (int i = 0; i < 4; ++i) {
        quadrants[i] = new int[halfN * halfN];
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            quadrants[0][i * halfN + j] = *(matrix + i * N + j);
            quadrants[1][i * halfN + j] = *(matrix + i * N + (j + halfN));
            quadrants[2][i * halfN + j] = *(matrix + (i + halfN) * N + j);
            quadrants[3][i * halfN + j] = *(matrix + (i + halfN) * N + (j + halfN));
        }
    }

    cout << "Матрица в порядке 4-3-2-1 (C):" << endl;
    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[2][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[3][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[0][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[1][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < 4; ++i) {
        delete[] quadrants[i];
    }
}

void printQuadrantsD(int* matrix, int N) {
    int halfN = N / 2;

    // Создаем массив для хранения квадрантов
    int* quadrants[4];

    // Выделяем память для каждого квадранта
    for (int i = 0; i < 4; ++i) {
        quadrants[i] = new int[halfN * halfN];
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            quadrants[0][i * halfN + j] = *(matrix + i * N + j);
            quadrants[1][i * halfN + j] = *(matrix + i * N + (j + halfN));
            quadrants[2][i * halfN + j] = *(matrix + (i + halfN) * N + j);
            quadrants[3][i * halfN + j] = *(matrix + (i + halfN) * N + (j + halfN));
        }
    }

    cout << "Матрица в порядке 2-1-4-3 (D):" << endl;
    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[1][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[0][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < halfN; ++i) {
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[3][i * halfN + j];
        }
        for (int j = 0; j < halfN; ++j) {
            cout << setw(4) << quadrants[2][i * halfN + j];
        }
        cout << endl;
    }

    for (int i = 0; i < 4; ++i) {
        delete[] quadrants[i];
    }
}

void shakerSort(int* array, int size) {
    bool swapped = true;
    int start = 0;
    int end = size - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (*(array + i) > *(array + i + 1)) {
                swap(*(array + i), *(array + i + 1));
                swapped = true;
            }
        }

        if (!swapped) break;

        --end;
        swapped = false;

        for (int i = end - 1; i >= start; --i) {
            if (*(array + i) > *(array + i + 1)) {
                swap(*(array + i), *(array + i + 1));
                swapped = true;
            }
        }

        ++start;
    }
}

void shakerSortMatrix(int* matrix, int N) {
    shakerSort(matrix, N * N);

    cout << "Отсортированная матрица:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << *(matrix + i * N + j);
        }
        cout << endl;
    }
}

void manipulateMatrix(int* matrix, int N, char operation, int number) {
    for (int i = 0; i < N * N; ++i) {
        switch (operation) {
        case '+':
            *(matrix + i) += number;
            break;
        case '-':
            *(matrix + i) -= number;
            break;
        case '*':
            *(matrix + i) *= number;
            break;
        case '/':
            if (number != 0)
                *(matrix + i) /= number;
            else
                cout << "Деление на ноль невозможно!" << endl;
            return;
        default:
            cout << "Неверная операция!" << endl;
            return;
        }
    }

    cout << "Измененная матрица:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << *(matrix + i * N + j);
        }
        cout << endl;
    }
}

int main() {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "ru-RU");
    int N;

    cout << "Введите порядок матрицы (6, 8 или 10): ";
    cin >> N;

    if (N != 6 && N != 8 && N != 10) {
        cout << "Неверный порядок матрицы!" << endl;
        return 1;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, N * N);
    int value = 1;
    int* matrix = new int[N * N];
    // Заполнение матрицы по схеме змейки перед разделением на квадранты
    for (int j = 0; j < N; ++j) {
        if (j % 2 == 0) { // Четные столбцы
            for (int i = 0; i < N; ++i) {
                *(matrix + i * N + j) = dis(gen);
            }
        }
        else { // Нечетные столбцы
            for (int i = N - 1; i >= 0; --i) {
                *(matrix + i * N + j) = dis(gen);
            }
        }
    }

    fillAndPrintVerticalSnake(hStdout, N);

    cout << endl;

    fillAndPrintSpiral(hStdout, N);

    cout << endl << endl << endl << endl;

    int choice;
    do {
        cout << "\nЗадания 2 и 3:\n";
        cout << "1. Показать случайную матрицу\n";
        cout << "2. Квадранты 4-1-2-3 (A)\n";
        cout << "3. Квадранты 3-4-1-2 (B)\n";
        cout << "4. Квадранты 4-3-2-1 (C)\n";
        cout << "5. Квадранты 2-1-4-3 (D)\n";
        cout << "6. Сортировка всей матрицы (Shaker Sort)\n";
        cout << "0. 4 Задание\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Случайная матрица:\n";
            fillAndPrintMatrix(matrix, N);
            break;
        case 2:
            printQuadrantsA(matrix, N);
            break;
        case 3:
            printQuadrantsB(matrix, N);
            break;
        case 4:
            printQuadrantsC(matrix, N);
            break;
        case 5:
            printQuadrantsD(matrix, N);
            break;
        case 6:
            shakerSortMatrix(matrix, N);
            break;
        case 0:
            cout << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);

    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << *(matrix + i * N + j);
        }
        cout << endl;
    }
    char operation;
    int number;
    cout << "Выберите операцию (+, -, *, /): ";
    cin >> operation;
    cout << "Введите число для операции: ";
    cin >> number;

    manipulateMatrix(matrix, N, operation, number);

    srand(static_cast<unsigned>(time(0)));

    cout << "Введите размер матрицы N: ";
    cin >> N;

    int** matrix1 = new int* [N];
    int** matrix2 = new int* [N];
    for (int i = 0; i < N; ++i) {
        matrix1[i] = new int[N];
        matrix2[i] = new int[N];
    }

    fillMatrixSequential(matrix1, N);

    fillMatrixRandom(matrix2, N);

    cout << "Первая матрица (от 1 до N^2):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << matrix1[i][j];
        }
        cout << endl;
    }

    cout << "Вторая матрица (рандом от 1 до N^2):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << matrix2[i][j];
        }
        cout << endl;
    }

    subtractAndDisplay(matrix1, matrix2, N);

    for (int i = 0; i < N; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] matrix;
    return 0;
}