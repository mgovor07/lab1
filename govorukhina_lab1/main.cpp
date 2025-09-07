//
//  main.cpp
//  govorukhina_lab1
//
//  Created by Мария Говорухина on 07.09.2025.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Pipe {
    string name;
    double length;
    int diameter;
    bool underRepair;
};

struct CompressorStation {
    string name;
    int totalWorkshops;
    int activeWorkshops;
    int stationClass;
};

vector<Pipe>pipes;
vector<CompressorStation> stations; //используем векторы для хранения данных

void addPipe() {
    Pipe p;
    cout << "Ведите название трубы: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Введите длину трубы (км): ";
    cin >> p.length;
    cout << "Введите диаметр трубы (мм): ";
    cin >> p.diameter;
    p.underRepair = false;
    pipes.push_back(p);
    cout << "Труба добавлена!\n";
}

void addStation() {
    CompressorStation cs;
    cout << "Ведите название КС: ";
    cin.ignore();
    getline(cin, cs.name);
    cout << "Введите количество цехов: ";
    cin >> cs.totalWorkshops;
    cout << "Введите количество работающих цехов: ";
    cin >> cs.activeWorkshops;
    cout << "Введите класс станции: ";
    cin >> cs.stationClass;
    stations.push_back(cs);
    cout << "КС добавлена!\n";
}

void viewAll() {
    cout << "\n Трубы \n";
    for (const auto& p : pipes) {
        cout << "Название: " << p.name
        << ", Длина: " << p.length
        << "км, Диаметр: " << p.diameter
        << "мм, В ремонте: " << (p.underRepair ? "Да" : "Нет") << endl;
    }
    
    cout << "\n Компрессионные станции \n";
    for (const auto& s : stations) {
        cout << "Название: " << s.name
        << ", Цехов: " << s.totalWorkshops
        << ", Работает: " << s.activeWorkshops
        << ", Класс: " << s.stationClass << endl;
    }
}

void editPipe() {
    if (pipes.empty()) {
        cout << "Нет доступных труб\n";
        return;
    }
    
    cout << "Выберите трубу для редактирования (0-" << pipes.size()-1 << "):\n";
    for (size_t i = 0; i < pipes.size(); ++i) {
        cout << i << ". " << pipes[i].name << endl;
    }
    
    size_t index;
    cin >> index;
    if (index < pipes.size()) {
        pipes[index].underRepair = !pipes[index].underRepair;
        cout << "Статус ремонта изменен на: " << (pipes[index].underRepair ? "В ремонте" : "Работает") << endl;
    } else {
        cout << "\n";
    }
};

void editStation() {
    if (stations.empty()) {
        cout << "Нет доступных КС!\n";
        return;
    }
    
    cout << "Выберите КС для редактирования (0-" << stations.size()-1 << "):\n";
    for (size_t i = 0; i < stations.size(); ++i) {
        cout << i << ". " << stations[i].name << endl;
    }
    
    size_t index;
    cin >> index;
    if (index < stations.size()) {
        cout << "1. Запустить цех\n2. Остановить цех\n";
        int choice;
        cin >> choice;
        if (choice == 1 && stations[index].activeWorkshops < stations[index].totalWorkshops) {
            stations[index].activeWorkshops++;
            cout << "Цех запущен!\n";
        } else if (choice == 2 && stations[index].activeWorkshops > 0) {
            stations[index].activeWorkshops--;
            cout << "Цех остановлен!\n";
        } else {
            cout << "Невозможно выполнить операцию!\n";
        }
    } else {
        cout << "Неверный индекс!\n";
    }
}

void saveData() {
    ofstream fout("data.txt");
    fout << pipes.size() << endl;
    for (const auto& p : pipes) {
        fout << p.name << endl << p.length << endl << p.diameter << endl << p.underRepair << endl;
    }
    
    fout << stations.size() << endl;
    for (const auto& s : stations) {
        fout << s.name << endl << s.totalWorkshops << endl << s.activeWorkshops << endl << s.stationClass << endl;
    }
    fout.close();
    cout << "Данные сохранены!\n";
}

void loadData() {
    ifstream fin("data.txt");
    if (!fin.is_open()) {
        cout << "Файл данных не найден!\n";
        return;
    }
    
    pipes.clear();
    stations.clear();
    
    size_t pipeCount, stationCount;
    fin >> pipeCount;
    fin.ignore();
    for (size_t i = 0; i < pipeCount; ++i) {
        Pipe p;
        getline(fin, p.name);
        fin >> p.length >> p.diameter >> p.underRepair;
        fin.ignore();
        pipes.push_back(p);
    }
    
    fin >> stationCount;
    fin.ignore();
    for (size_t i = 0; i < stationCount; ++i) {
        CompressorStation cs;
        getline(fin, cs.name);
        fin >> cs.totalWorkshops >> cs.activeWorkshops >> cs.stationClass;
        fin.ignore();
        stations.push_back(cs);
    }
    fin.close();
    cout << "Данные загружены!\n";
}

int main() {
    while (true) {
        cout << "\nМеню:\n"
             << "1. Добавить трубу\n"
             << "2. Добавить КС\n"
             << "3. Просмотр всех объектов\n"
             << "4. Редактировать трубу\n"
             << "5. Редактировать КС\n"
             << "6. Сохранить\n"
             << "7. Загрузить\n"
             << "0. Выход\n"
             << "Выберите действие: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: addPipe(); break;
            case 2: addStation(); break;
            case 3: viewAll(); break;
            case 4: editPipe(); break;
            case 5: editStation(); break;
            case 6: saveData(); break;
            case 7: loadData(); break;
            case 0: return 0;
            default: cout << "Неверный выбор!\n";
        }
    }
}
