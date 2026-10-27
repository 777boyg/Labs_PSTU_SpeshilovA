#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL,".65001");
    int sm=0;
    for (int i=2; i<100; i+=2)
        sm+=i;
    cout <<"Сумма целых положительных четных чисел, меньших 100 = "<<sm;
    return 0;
}