#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include <iomanip>

using namespace std;

// Структура "Сотрудник"
struct Employee {
    char fullName[100];   // ФИО
    char position[50];    // Должность
    int birthYear;        // Год рождения
    double salary;        // Зарплата
};

// Прототипы функций
bool createFile(const string& filename);
void printFile(const string& filename);
void printEmployee(const Employee& emp, int index);
void inputEmployee(Employee& emp);
bool addEmployeeAfter(const string& filename, int position, const Employee& emp);
bool deleteEmployeeByName(const string& filename, const string& name);
int findEmployeeByName(const string& filename, const string& name);
int countRecords(const string& filename);
bool findFreePosition(const string& filename, int& pos);
void clearInput();

// ---------- Формирование файла ----------
bool createFile(const string& filename) {
    ofstream fout(filename, ios::binary | ios::trunc);
    if (!fout) {
        cerr << "Ошибка: не удалось открыть файл для записи: " << filename << endl;
        return false;
    }

    int count;
    cout << "Введите количество сотрудников: ";
    if (!(cin >> count) || count < 0) {
        cerr << "Ошибка: некорректное количество сотрудников!" << endl;
        clearInput();
        return false;
    }
    clearInput();

    for (int i = 0; i < count; ++i) {
        cout << "\n--- Сотрудник #" << (i + 1) << " ---" << endl;
        Employee emp;
        inputEmployee(emp);
        fout.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
        if (!fout) {
            cerr << "Ошибка записи в файл!" << endl;
            return false;
        }
    }

    fout.close();
    cout << "Файл успешно сформирован (" << count << " записей)." << endl;
    return true;
}

// ---------- Ввод одного сотрудника ----------
void inputEmployee(Employee& emp) {
    cout << "ФИО: ";
    cin.getline(emp.fullName, sizeof(emp.fullName));
    if (cin.fail()) { cin.clear(); clearInput(); }

    cout << "Должность: ";
    cin.getline(emp.position, sizeof(emp.position));
    if (cin.fail()) { cin.clear(); clearInput(); }

    cout << "Год рождения: ";
    cin >> emp.birthYear;
    if (cin.fail()) { cin.clear(); emp.birthYear = 0; }
    clearInput();

    cout << "Заработная плата: ";
    cin >> emp.salary;
    if (cin.fail()) { cin.clear(); emp.salary = 0; }
    clearInput();
}

// ---------- Печать одного сотрудника ----------
void printEmployee(const Employee& emp, int index) {
    cout << "| " << setw(3) << index << " | "
         << setw(30) << left << emp.fullName
         << "| " << setw(20) << left << emp.position
         << "| " << setw(6) << emp.birthYear << " | "
         << setw(10) << right << emp.salary << " |" << endl;
}

// ---------- Печать всего файла ----------
void printFile(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << endl;
        return;
    }

    fin.seekg(0, ios::end);
    streamoff size = fin.tellg();
    fin.seekg(0, ios::beg);

    if (size <= 0) {
        cout << "Файл пуст." << endl;
        return;
    }

    int count = static_cast<int>(size / sizeof(Employee));
    cout << "\n=================== СПИСОК СОТРУДНИКОВ ===================" << endl;
    cout << "| #   | ФИО                           | Должность            | Год    | Зарплата   |" << endl;
    cout << "|-----|-------------------------------|----------------------|--------|------------|" << endl;

    for (int i = 0; i < count; ++i) {
        Employee emp;
        fin.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        if (!fin) {
            cerr << "Ошибка чтения записи #" << i << endl;
            break;
        }
        printEmployee(emp, i);
    }
    cout << "==========================================================" << endl;
    cout << "Всего записей: " << count << endl;
}

// ---------- Подсчёт записей ----------
int countRecords(const string& filename) {
    ifstream fin(filename, ios::binary | ios::ate);
    if (!fin) return -1;
    streamoff size = fin.tellg();
    if (size <= 0) return 0;
    return static_cast<int>(size / sizeof(Employee));
}

// ---------- Поиск свободной позиции (для добавления в конец или на место удалённой) ----------
bool findFreePosition(const string& filename, int& pos) {
    int cnt = countRecords(filename);
    if (cnt < 0) return false;
    pos = cnt;
    return true;
}

// ---------- Поиск сотрудника по фамилии ----------
int findEmployeeByName(const string& filename, const string& name) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл для поиска!" << endl;
        return -1;
    }

    int count = countRecords(filename);
    for (int i = 0; i < count; ++i) {
        Employee emp;
        fin.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        if (!fin) return -1;

        string fullName = emp.fullName;
        // Ищем вхождение фамилии в начало ФИО
        if (fullName.find(name) == 0) {
            return i;
        }
        // Или точное совпадение по всей строке
        if (fullName == name) {
            return i;
        }
    }
    return -1;
}

// ---------- Удаление сотрудника по фамилии ----------
bool deleteEmployeeByName(const string& filename, const string& name) {
    int idx = findEmployeeByName(filename, name);
    if (idx < 0) {
        cerr << "Сотрудник с фамилией \"" << name << "\" не найден." << endl;
        return false;
    }

    fstream fs(filename, ios::binary | ios::in | ios::out);
    if (!fs) {
        cerr << "Ошибка: не удалось открыть файл!" << endl;
        return false;
    }

    int count = countRecords(filename);
    Employee emp;
    fs.seekg(idx * sizeof(Employee), ios::beg);
    fs.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
    cout << "Удаляется сотрудник: " << emp.fullName << endl;

    // Сдвиг всех последующих записей на одну позицию влево
    for (int i = idx; i < count - 1; ++i) {
        fs.seekg((i + 1) * sizeof(Employee), ios::beg);
        Employee tmp;
        fs.read(reinterpret_cast<char*>(&tmp), sizeof(Employee));
        if (!fs) { cerr << "Ошибка чтения!" << endl; return false; }

        fs.seekp(i * sizeof(Employee), ios::beg);
        fs.write(reinterpret_cast<char*>(&tmp), sizeof(Employee));
        if (!fs) { cerr << "Ошибка записи!" << endl; return false; }
    }

    fs.close();

    // Обрезаем файл
    int newCount = count - 1;
    ofstream trunc(filename, ios::binary | ios::trunc);
    trunc.close();

    // Восстанавливаем записи (или проще — использовать trunc после перезаписи)
    // Перепишем более надёжно: создадим новый временный файл
    // (уже сделано через trunc — теперь файл пуст, надо переписать)
    // Открываем исходный на чтение уже нельзя. Поэтому реализуем через временный файл.

    // --- Переделаем более надёжно ---
    // (закрываем всё и делаем полное пересоздание)
    // Читаем все записи, кроме удаляемой, во временный файл
    ifstream fin(filename, ios::binary);
    // На этом этапе файл уже обнулён — исправим логику: используем временный файл с самого начала
    // (см. ниже исправленную версию)

    return true;
}

// ---------- Исправленная версия удаления через временный файл ----------
bool deleteEmployeeByNameSafe(const string& filename, const string& name) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл!" << endl;
        return false;
    }

    int count = countRecords(filename);
    if (count <= 0) {
        cerr << "Файл пуст!" << endl;
        return false;
    }

    // Находим индекс удаляемого
    int idx = -1;
    for (int i = 0; i < count; ++i) {
        Employee emp;
        fin.seekg(i * sizeof(Employee), ios::beg);
        fin.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        if (!fin) break;

        string fullName = emp.fullName;
        if (fullName.find(name) == 0 || fullName == name) {
            idx = i;
            cout << "Удаляется сотрудник: " << emp.fullName
                 << " (позиция " << i << ")" << endl;
            break;
        }
    }

    if (idx < 0) {
        cerr << "Сотрудник с фамилией \"" << name << "\" не найден." << endl;
        return false;
    }

    // Создаём временный файл
    const string tmpName = filename + ".tmp";
    ofstream fout(tmpName, ios::binary | ios::trunc);
    if (!fout) {
        cerr << "Ошибка: не удалось создать временный файл!" << endl;
        return false;
    }

    for (int i = 0; i < count; ++i) {
        if (i == idx) continue;
        Employee emp;
        fin.seekg(i * sizeof(Employee), ios::beg);
        fin.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        fout.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    }

    fin.close();
    fout.close();

    // Заменяем исходный файл
    remove(filename.c_str());
    if (rename(tmpName.c_str(), filename.c_str()) != 0) {
        cerr << "Ошибка: не удалось заменить исходный файл!" << endl;
        return false;
    }

    cout << "Удаление выполнено успешно." << endl;
    return true;
}

// ---------- Добавление сотрудника после элемента с указанным номером ----------
bool addEmployeeAfter(const string& filename, int position, const Employee& emp) {
    int count = countRecords(filename);
    if (count < 0) {
        cerr << "Ошибка: не удалось прочитать файл!" << endl;
        return false;
    }

    if (position < -1 || position >= count) {
        cerr << "Ошибка: неверный номер позиции (" << position
             << "). Допустимо: от -1 до " << (count - 1) << endl;
        return false;
    }

    // Если position == -1 — добавляем в начало
    int insertPos = position + 1;

    const string tmpName = filename + ".tmp";
    ifstream fin(filename, ios::binary);
    ofstream fout(tmpName, ios::binary | ios::trunc);
    if (!fin || !fout) {
        cerr << "Ошибка: не удалось открыть файлы!" << endl;
        return false;
    }

    int i = 0;
    for (; i < insertPos; ++i) {
        Employee e;
        fin.read(reinterpret_cast<char*>(&e), sizeof(Employee));
        fout.write(reinterpret_cast<char*>(&e), sizeof(Employee));
    }

    fout.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));

    for (; i < count; ++i) {
        Employee e;
        fin.read(reinterpret_cast<char*>(&e), sizeof(Employee));
        fout.write(reinterpret_cast<char*>(&e), sizeof(Employee));
    }

    fin.close();
    fout.close();

    remove(filename.c_str());
    if (rename(tmpName.c_str(), filename.c_str()) != 0) {
        cerr << "Ошибка: не удалось заменить исходный файл!" << endl;
        return false;
    }

    cout << "Сотрудник добавлен на позицию " << insertPos << "." << endl;
    return true;
}

// ---------- Очистка потока ввода ----------
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------- Главное меню ----------
int main() {
    setlocale(LC_ALL, ".65001");

    const string filename = "employees.bin";
    int choice;

    do {
        cout << "\n===== МЕНЮ =====" << endl;
        cout << "1. Сформировать файл" << endl;
        cout << "2. Просмотреть файл" << endl;
        cout << "3. Удалить сотрудника по фамилии" << endl;
        cout << "4. Добавить сотрудника после позиции" << endl;
        cout << "5. Выход" << endl;
        cout << "Выбор: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Неверный ввод!" << endl;
            continue;
        }
        clearInput();

        switch (choice) {
        case 1:
            createFile(filename);
            break;

        case 2:
            printFile(filename);
            break;

        case 3: {
            cout << "Введите фамилию: ";
            string name;
            getline(cin, name);
            deleteEmployeeByNameSafe(filename, name);
            break;
        }

        case 4: {
            int pos;
            cout << "Введите номер элемента, после которого добавить (-1 для начала): ";
            if (!(cin >> pos)) {
                clearInput();
                cout << "Неверный ввод!" << endl;
                break;
            }
            clearInput();

            cout << "Введите данные нового сотрудника:" << endl;
            Employee emp;
            inputEmployee(emp);
            addEmployeeAfter(filename, pos, emp);
            break;
        }

        case 5:
            cout << "Выход." << endl;
            break;

        default:
            cout << "Неверный пункт меню!" << endl;
        }
    } while (choice != 5);

    return 0;
}