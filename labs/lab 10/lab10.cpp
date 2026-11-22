#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int* removeElement(int* arr, int& size, int key) {
    int pos = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "Элемент с ключом " << key << " не найден. Удаление не выполнено.\n";
        int* result = new int[size];
        for (int i = 0; i < size; i++) result[i] = arr[i];
        return result;
    }

    int newSize = size - 1;
    int* result = new int[newSize > 0 ? newSize : 1];

    for (int i = 0, j = 0; i < size; i++) {
        if (i != pos) {
            result[j++] = arr[i];
        }
    }

    size = newSize;
    cout << "Удалён элемент с ключом " << key << " (позиция " << pos << ").\n";
    return result;
}

int* addElement(int* arr, int& size, int key) {
    int newSize = size + 1;
    int* result = new int[newSize];

    for (int i = 0; i < size; i++) {
        result[i] = arr[i];
    }
    result[size] = key;
    size = newSize;

    cout << "Добавлен элемент с ключом " << key << " в конец массива.\n";
    return result;
}

void printArray(const int* arr, int size, const string& title) {
    cout << title << " (размер " << size << "): ";
    if (size == 0) {
        cout << "[пусто]";
    } else {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr)));

    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) {
        cout << "Некорректный размер массива.\n";
        return 1;
    }

    int* arr = new int[size];
    cout << "Исходный массив (случайные числа 0..20):\n";
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 21;
    }
    printArray(arr, size, "Исходный массив");

    int keyToRemove;
    cout << "\nВведите ключ (значение) для удаления: ";
    cin >> keyToRemove;

    int* afterRemove = removeElement(arr, size, keyToRemove);
    delete[] arr;
    arr = afterRemove;

    printArray(arr, size, "Массив после удаления");

    int keyToAdd;
    cout << "\nВведите ключ (значение) для добавления: ";
    cin >> keyToAdd;

    int* afterAdd = addElement(arr, size, keyToAdd);
    delete[] arr;
    arr = afterAdd;

    printArray(arr, size, "Массив после добавления");

    delete[] arr;

    return 0;
}