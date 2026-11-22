#include <iostream>
#include <cstdlib>
using namespace std;

const int N = 8;
int queens[N];        // queens[i] = столбец ферзя в строке i
int solutionsCount = 0;

// Проверка: можно ли поставить ферзя в столбец col в строке row
bool isSafe(int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (queens[i] == col || abs(queens[i] - col) == row - i)
            return false;
    }
    return true;
}

void solve(int row) {
    if (row == N) {
        ++solutionsCount;
        cout << "Решение #" << solutionsCount << ":\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                cout << (queens[i] == j ? " Q" : " .");
            cout << "\n";
        }
        cout << "\n";
        return;
    }
    for (int col = 0; col < N; ++col) {
        if (isSafe(row, col)) {
            queens[row] = col;
            solve(row + 1);
        }
    }
}

int main() {
    solve(0);
    cout << "Всего найдено решений: " << solutionsCount << "\n";
    return 0;
}