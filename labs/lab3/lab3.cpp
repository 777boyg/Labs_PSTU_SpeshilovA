#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

int main() {
    setlocale (LC_ALL, ".65001");
    const double P = 3.14; 
    double a=P/5, b=9*P/5, s=(b-a)/10;
    int n=40;
    double e=0.0001;

    for (double x=a; x<=b+0.001; x+=s) {
        double n2 = 0, e2 = 0, t;
        int j = 1;
        for (int i = 1; i <= n; i++) 
            n2 += cos(i*x)/i;
        do {
            t = cos(j*x)/j;
            e2 += t;
            j++;
        } while (abs(t) >= e);

        cout <<"f(x): "<<-log(abs(2*sin(x/2)))<<";   для заданного n: "<<n2<< ";   для заданной точности 0.0001: " <<e2<<endl;
    }
    return 0;
}