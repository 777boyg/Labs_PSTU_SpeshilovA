#include <iostream>
using namespace std;

int main() {
    float a1 = 1000, b1 = 0.0001;
    float s1 = a1 + b1;     // a+b
    float s2 = s1 * s1;     // (a+b)^2
    float s3 = a1 * a1;     // a^2
    float s4 = 2 * a1 * b1; // 2ab
    float s5 = s3 + s4;     // (a^2 + 2ab)
    float s6 = s2 - s5;     // (a+b)^2 - (a^2 + 2ab)
    float s7 = b1 * b1;     // b^2
    volatile float ans1 = s6 / s7;    // ((a+b)^2 - (a^2 + 2ab))/b^2
    cout << "float: " << ans1 << "\n";

    double a2 = 1000, b2 = 0.0001;
    double f1 = a2 + b2;     // a+b
    double f2 = f1 * f1;     // (a+b)^2
    double f3 = a2 * a2;     // a^2
    double f4 = 2 * a2 * b2; // 2ab
    double f5 = f3 + f4;     // (a^2 + 2ab)
    double f6 = f2 - f5;     // (a+b)^2 - (a^2 + 2ab)
    double f7 = b2 * b2;     // b^2
    volatile double ans2 = f6 / f7;   // ((a+b)^2 - (a^2 + 2ab))/b^2
    cout << "double: " << ans2 << "\n";
    return 0;
}