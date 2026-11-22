#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int N = 5;
const int WIDTH = 2 * N + 1;
const int HEIGHT = N + 1;

int rods[3][N];
int top[3];
int step = 0;

void draw() {
    cout << "\nШаг " << step << ":\n";

    for (int row = 0; row < HEIGHT; row++) {
        for (int r = 0; r < 3; r++) {
            string cell(WIDTH, ' ');

            if (row == HEIGHT - 1) {
                cell = string(WIDTH, '=');
            } else {
                int ringIdx = (HEIGHT - 2) - row;

                if (ringIdx >= 0 && ringIdx < top[r]) {
                    int size = rods[r][ringIdx];
                    int stars = 2 * size - 1;
                    int left = (WIDTH - stars) / 2;
                    for (int i = 0; i < stars; i++) cell[left + i] = '*';
                } else {
                    cell[WIDTH / 2] = '|';
                }
            }
            cout << cell << "  ";
        }
        cout << "\n";
    }
    cout << string(WIDTH, '-') << "  "
         << string(WIDTH, '-') << "  "
         << string(WIDTH, '-') << "\n";
    cout << setw(WIDTH / 2 + 2) << "A"
         << setw(WIDTH / 2 + 2) << "B"
         << setw(WIDTH / 2 + 2) << "C" << "\n";
}

void moveDisk(int from, int to) {
    int disk = rods[from][top[from] - 1];
    top[from]--;
    rods[to][top[to]] = disk;
    top[to]++;
    step++;
    cout << "  --> Диск " << disk << " : "
         << (char)('A' + from) << " -> " << (char)('A' + to) << "\n";
    draw();
}

void hanoi(int n, int from, int to, int via) {
    if (n == 0) return;
    hanoi(n - 1, from, via, to);
    moveDisk(from, to);
    hanoi(n - 1, via, to, from);
}

int main() {
    for (int r = 0; r < 3; r++) top[r] = 0;
    for (int i = N; i >= 1; i--) {
        rods[0][top[0]] = i;
        top[0]++;
    }

    cout << "Ханойская башня: " << N << " колец, 3 стержня\n";
    draw();
    hanoi(N, 0, 2, 1);
    cout << "\nГотово! Всего шагов: " << step << "\n";
    return 0;
}