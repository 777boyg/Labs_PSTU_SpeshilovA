#include <iostream>
#include <clocale>
#include <complex> 

using namespace std;

double sum(double a, double b) {
    return a + b;
}

complex<double> sum(complex<double> a, complex<double> b) {
    return a + b;
}

int main() {
    setlocale(LC_ALL, ".65001");
    double num1 = 2.5;
    double num2 = 3.7;
    
    cout << "Сложение вещественных чисел:" << endl;
    cout << num1 << " + " << num2 << " = " << sum(num1, num2) << endl;
    cout << endl;

    complex<double> c1(2.0, 3.0);
    complex<double> c2(1.5, 2.5);

    cout << "Сложение комплексных чисел:" << endl;
    cout << "Первое число: " << c1 << endl;
    cout << "Второе число: " << c2 << endl;
    cout << "Сумма: " << sum(c1, c2) << endl;

    return 0;
}
