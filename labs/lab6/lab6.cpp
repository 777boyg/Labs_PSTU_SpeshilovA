#include <iostream>
#include <cstdio> 
#include <cstring>
#include <clocale> 

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    char s[256];
    cout << "Введите строку (заканчивается точкой): " << endl;
    gets(s); 

    char dl[256] = "";
    char kr[256] = "";
    
    int mx = 0, mn = 256; 

    int i = 0, len = strlen(s);

    while (i < len && s[i] != '.') 
    {
        while (i < len && s[i] == ' ') i++;

        if (i < len && s[i] != '.') 
        {
            int start = i;
            while (i < len && s[i] != ' ' && s[i] != '.') i++;
            int wLen = i - start;

            if (wLen > mx) 
            {
                mx = wLen;
                for (int j = 0; j < wLen; j++) 
                    dl[j] = s[start + j];
                dl[wLen] = '\0';
            }

            if (wLen < mn) 
            {
                mn = wLen;
                for (int j = 0; j < wLen; j++) 
                    kr[j] = s[start + j];
                kr[wLen] = '\0';
            }
        }
    }
    
    cout << "\nСамое длинное слово: " << dl << " (длина: " << mx << ")" << endl;
    cout << "Самое короткое слово: " << kr << " (длина: " << mn << ")" << endl;

    return 0;
}
