#include <iostream>
using namespace std;
/*
int main() { // ЗАДАНИЕ 1
    float a1 = 1000, b1 = 0.0001;
    float s1 = a1 + b1;     // a+b
    float s2 = s1 * s1;     // (a+b)^2
    float s3 = a1 * a1;     // a^2
    float s4 = 2 * a1 * b1; // 2ab
    float s5 = s3 + s4;     // (a^2 + 2ab)
    float s6 = s2 - s5;     // (a+b)^2 - (a^2 + 2ab)
    float s7 = b1 * b1;     // b^2
    float ans1 = s6 / s7;    // ((a+b)^2 - (a^2 + 2ab))/b^2
    cout << "float: " << ans1 << "\n";

    double a2 = 1000, b2 = 0.0001;
    double f1 = a2 + b2;     // a+b
    double f2 = f1 * f1;     // (a+b)^2
    double f3 = a2 * a2;     // a^2
    double f4 = 2 * a2 * b2; // 2ab
    double f5 = f3 + f4;     // (a^2 + 2ab)
    double f6 = f2 - f5;     // (a+b)^2 - (a^2 + 2ab)
    double f7 = b2 * b2;     // b^2
    double ans2 = f6 / f7;   // ((a+b)^2 - (a^2 + 2ab))/b^2
    cout << "double: " << ans2 << "\n";
    return 0;
}
*/

int main() { // ЗАДАНИЕ 2
    setlocale(LC_ALL, ".65001");

    int n1, m1, n2, m2, n3, m3;
    cin >> n1;
    cin >> m1;
    n2=n1; n3=n1;
    m2=m1; m3=m1;
    
    int ans1 = ++n1*++m1;
    cout << "результат 1: " << ans1 << ";  n и m после выполнения программы: n=" << n1 << " m=" << m1 << "\n";

    bool ans2 = m2++<n2; //1=True 0=False
    cout << "результат 2: " << ans2 << ";  n и m после выполнения программы: n=" << n2 << " m=" << m2 << "\n";

    bool ans3 = n3++>m3; //1=True 0=False
    cout << "результат 3: " << ans3 << ";  n и m после выполнения программы: n=" << n3 << " m=" << m3 << "\n";
    return 0;
}
