#include <iostream>
#include <stdlib.h>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, ".65001");
    
    int c = 5*2;
    int a[5];
    int s = 5;

    for (int i = 0; i < s; i++) 
        a[i] = rand() % 41 - 20; 

    cout << "\n исходный массив:" << endl;
    for (int i = 0; i < s; i++) 
        cout << a[i] << " ";
    
    int zi = -1;
    int i = 0;
    for (; i < s && a[i] != 0; i++)
        ;   // пустое тело — идём до первого нуля

    if (i < s && a[i] == 0) {
        zi = i;
        for (int k = zi; k < s - 1; k++)
            a[k] = a[k + 1];
        s--;
        cout << "\n Удалён первый нулевой элемент (индекс " << zi << ")." << endl;
    } else {
        cout << "\n Нулевых элементов не найдено — удаление не выполнено." << endl;
    }

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

    return 0;
}
