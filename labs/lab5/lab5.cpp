#include <iostream>
#include <iomanip>

using namespace std;

const int l = 3;
const int h = 3;

void swapl(int a[l][h], int r1, int r2) 
{
    for (int j = 0; j < h; j++) 
    {
        int temp = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = temp;
    }
}

int main() 
{

    setlocale(LC_ALL, ".65001");

    int a[l][h] = {
        {5, 2, 9},
        {8, 4, 3},
        {1, 6, 2},};

    for (int i = 0; i < l - 1; i++) 
        for (int j = 0; j < l - i - 1; j++) 
            if (a[j][2] > a[j + 1][2]) 
                swapl(a, j, j + 1);

    cout << "Массив, отсортированный по 3-му столбцу:" << endl;

    for (int i = 0; i < l; i++) 
    {
        for (int j = 0; j < h; j++) 
            cout << setw(3) << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
