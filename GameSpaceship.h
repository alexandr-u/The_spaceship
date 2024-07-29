#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
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

    // проверка на правильный номер планеты
    int choosingPlanet();

    // проверка на топливо и расстояние до планеты
    int possibilityOfFlight(int num);

    // возможность что враг попался на пути к планете
    bool enemyOnWay();

    // прилет на планету Земля и повышение ресурсов до минимума (100)
    void flyToEarth();

    // прилет на планету
    void flyToPlanet(int num);

    // бой с врагами (сложение/вычитание ресурсов при победе/поражении)
    bool battle();

    // бой с врагами логика
    bool attack();

    //обмен ресурсов во время боя
    void exchangeOfResourcesDuringTheBattle();

    // поиск ресурсов на планете
    void searchForResources();

    //получение ресурсов и вычитание их из планеты
    void gettingResources(std::vector<Planet>::iterator iterPlanet);

    // обмен ресурсов в магазине
    void shopping();


    Spaceship m_mainSpaceship;
    std::vector<Planet> m_allPlanets;
    Enemy m_enemy;
};