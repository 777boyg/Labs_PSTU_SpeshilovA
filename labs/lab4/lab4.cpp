#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, ".65001");

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int c = n*2;
    int* a = new int[c];
    int s = n;

    for (int i = 0; i < n; i++) 
        a[i] = rand() % 41 - 20; 
    

    cout << "\n исходный массив:" << endl;
    for (int i = 0; i < s; i++) 
        cout << a[i] << " ";
    

    int zi = -1;
    for (int i = 0; i < s; i++) 
        if (a[i] == 0) {
            zi = i;
            break;
        }
    
    if (zi!=-1) {
        for (int i = zi; i < s - 1; i++) 
            a[i] = a[i + 1];
        
        s--;
        cout << "\n Удалён первый нулевой элемент (индекс " << zi << ")." << endl;
    } else 
        cout << "\n Нулевых элементов не найдено — удаление не выполнено." << endl;
    

    for (int i = s - 1; i >= 0; i--) {
        if (a[i] % 2 == 0) {
            int v = a[i] + 2;         
            for (int j = s; j > i + 1; j--) {
                a[j] = a[j - 1];
            }
            a[i + 1] = v;
            s++;
        }
    }

    cout << "\n Итоговый массив:" << endl;
    for (int i = 0; i < s; i++) {
        cout << a[i] <<" ";
    }

    delete[] a;
    return 0;
}