#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <random>
#include <map>
#include "windows.h"

#include "SpaceItem.h"
#include "Enemy.h"
#include "Spaceship.h"
#include "Planet.h"

bool inputInt(int& temp);
int zeroIfNegative(int& value);


class Game
{
public:
    Game() = default;
    ~Game() = default;

    //запуск игры
    void run();

    // старт игры 
    void start();

    // конец игры
    bool is_ended() const;
    void ended();

    //cписок доступных действий
    void showMenu() const;

    // вывод планет
    void outputAllPlanet();

    //полет из меню
    void fly();

    // проверка на правильный номер планеты
    int choosingPlanet();

    // проверка на топливо и расстояние до планеты
    int possibilityOfFlight(int num);

    // возможность что враг попался на пути к планете
    bool enemyOnWay(int col);

    // бой с врагами (сложение/вычитание ресурсов при победе/поражении)
    bool battle();

    // бой с врагами логика
    bool attack();

    //вопрос к пользователю о необходимости перевода ресурсов во время боя
    void resourcesDuringTheBattle();

    //обмен ресурсов во время боя
    void exchangeOfResourcesDuringTheBattle();

    // поиск ресурсов на планете
    void searchForResources();

    // обмен ресурсов в магазине
    void shopping();

    Spaceship m_mainSpaceship;
    std::map<int, Planet> m_mapLocation_Planet;
    Enemy m_enemy;
};