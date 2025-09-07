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

