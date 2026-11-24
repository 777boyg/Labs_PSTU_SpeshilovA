#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура узла однонаправленного списка
struct Node {
    int key;        
    Node* next;     
};

// 1. Создание пустого списка
Node* createList() {
    return nullptr;  // пустой список - это нулевой указатель
}

// 2. Добавление элемента в конец списка
void append(Node*& head, int value) {
    Node* newNode = new Node{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr)
        cur = cur->next;
    cur->next = newNode;
}

// Добавление элемента ПЕРЕД элементом с заданным ключом
bool insertBefore(Node*& head, int targetKey, int newValue) {
    if (head == nullptr) return false;

    // Если целевой элемент - первый
    if (head->key == targetKey) {
        Node* newNode = new Node{newValue, head};
        head = newNode;
        return true;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->key != targetKey)
        cur = cur->next;

    if (cur->next == nullptr) return false;  // ключ не найден

    Node* newNode = new Node{newValue, cur->next};
    cur->next = newNode;
    return true;
}

// 3. Удаление элемента с заданным ключом (первого найденного)
bool removeByKey(Node*& head, int key) {
    if (head == nullptr) return false;

    if (head->key == key) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->key != key)
        cur = cur->next;

    if (cur->next == nullptr) return false;  // не найден

    Node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
    return true;
}

// 4. Печать списка
void printList(const Node* head) {
    if (head == nullptr) {
        cout << "Список пустой" << endl;
        return;
    }
    cout << "Список: ";
    const Node* cur = head;
    while (cur != nullptr) {
        cout << cur->key;
        if (cur->next != nullptr) cout << ", ";
        cur = cur->next;
    }
    cout << endl;
}

// 5. Запись списка в файл
bool saveToFile(const Node* head, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Ошибка открытия файла для записи: " << filename << endl;
        return false;
    }
    const Node* cur = head;
    while (cur != nullptr) {
        fout << cur->key << "\n";
        cur = cur->next;
    }
    fout.close();
    return true;
}

// 6. Уничтожение списка
void destroyList(Node*& head) {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
}

// 7. Восстановление списка из файла
bool loadFromFile(Node*& head, const string& filename) {
    destroyList(head);  // на всякий случай

    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Ошибка открытия файла для чтения: " << filename << endl;
        return false;
    }
    int value;
    while (fin >> value) {
        append(head, value);
    }
    fin.close();
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* list = createList();

    cout << " Создание списка " << endl;
    append(list, 10);
    append(list, 20);
    append(list, 30);
    append(list, 40);
    append(list, 50);
    printList(list);
    cout << endl;

    cout << " Удаление элемента с ключом 30 " << endl;
    if (removeByKey(list, 30))
        cout << "Элемент 30 удалён." << endl;
    else
        cout << "Элемент 30 не найден." << endl;
    printList(list);
    cout << endl;

    cout << " Добавление элемента 25 перед ключом 40 " << endl;
    if (insertBefore(list, 40, 25))
        cout << "Элемент 25 добавлен перед 40." << endl;
    else
        cout << "Элемент 40 не найден." << endl;
    printList(list);
    cout << endl;

    cout << " Добавление элемента 5 перед ключом 10 " << endl;
    insertBefore(list, 10, 5);
    printList(list);
    cout << endl;

    cout << " Удаление элемента с ключом 999 " << endl;
    if (!removeByKey(list, 999))
        cout << "Элемент 999 не найден." << endl;
    printList(list);
    cout << endl;

    const string filename = "list.txt";
    cout << " Запись списка в файл " << filename << " " << endl;
    if (saveToFile(list, filename))
        cout << "Список успешно записан." << endl;
    cout << endl;

    cout << " Уничтожение списка " << endl;
    destroyList(list);
    printList(list);   // должно вывести "Список пустой"
    cout << endl;

    cout << " Восстановление списка из файла " << endl;
    if (loadFromFile(list, filename)) {
        cout << "Список успешно восстановлен." << endl;
        printList(list);
    }
    cout << endl;

    cout << " Финальное уничтожение списка " << endl;
    destroyList(list);
    printList(list);

    return 0;
}