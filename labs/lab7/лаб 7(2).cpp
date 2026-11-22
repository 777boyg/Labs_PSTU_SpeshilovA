#include <iostream>
#include <cstdarg>

using namespace std;

float mult(int count, ...)
{
    va_list args;
    va_start(args, count);

    float result = 1;
    for (int i = 0; i < count; ++i)
    {   float value = va_arg(args, double);
        result *= value;
    }

    va_end(args);
    return result;
}

int main()
{
    // 3 параметра
    float r1 = mult(3, 1.5, 2.0, 4.0);
    cout << "mult(3, 1.5, 2.0, 4.0) = " << r1 << endl;

    // 7 параметров
    float r2 = mult(7, 1.1, 2.2, 0.5, 3.0, 1.0, 2.0, 4.0);
    cout << "mult(7, ...) = " << r2 << endl;

    // 11 параметров
    float r3 = mult(11, 1.2, 2.0, 0.5, 1.5, 2.0, 1.0, 0.25, 4.0, 1.5, 2.0, 1.0);
    cout << "mult(11, ...) = " << r3 << endl;

    return 0;
}