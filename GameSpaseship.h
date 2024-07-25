#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "windows.h"

bool inputInt(int& temp)
{
    if (std::cin >> temp)
    {
        return true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
}

class Spaceship
{
public:
    //перегрузка метода вывода для планеты
    friend std::ostream& operator<<(std::ostream& os, Spaceship& item)
    {
        os << "\nNow you have: "
            << "\nfuel\t\t" << item.m_fuel
            << "\nfood\t\t" << item.m_food
            << "\nprotection\t" << item.m_protection
            << "\nresources\t" << item.m_resources;
        return os;
    }

    static int location;

    //начальные ресурсы игрока
    Spaceship() :
        m_resources(100),
        m_food(100),
        m_fuel(100),
        m_protection(100)
    {};
    ~Spaceship() = default;

    //переменные: ресурсы, пища, топливо, защита
    int m_resources;
    int m_food;
    int m_fuel;
    int m_protection;
};

class Enemy
{
public:
    friend std::ostream& operator<<(std::ostream& os, Enemy& item) //перегрузка метода вывода для врага
    {
        os << "\nInformation about the enemy:"
            << "\nfuel\t\t" << item.m_fuel
            << "\nprotection\t" << item.m_protection
            << "\nresources\t" << item.m_resources;
        return os;
    }

    Enemy() :
        m_resources(0),
        m_fuel(0),
        m_protection(0)
    {};
    Enemy(int resourcesValue, int fuelValue, int protectionValue) :
        m_resources(resourcesValue),
        m_fuel(fuelValue),
        m_protection(protectionValue)
    {};
    ~Enemy() = default;

    Enemy(const Enemy& over) = default;
    void operator () (int resourcesValue, int fuelValue, int protectionValue) //вносить данные через скобочки
    {
        m_resources = resourcesValue;
        m_fuel = fuelValue;
        m_protection = protectionValue;
    }

    //ресурсы, топливо, защита
    int m_resources;
    int m_fuel;
    int m_protection;
};

class Shop
{
public:
    friend std::ostream& operator<<(std::ostream& os, Shop& item)
    {
        os << "\nProduct price (resources): "
            << "\n1. Fuel\t\t" << item.m_piceFuel
            << "\n2. Food\t\t" << item.m_piceFood
            << "\n3. Protection\t" << item.m_piceProtection;
        return os;
    }

    Shop() :
        m_piceFood(0),
        m_piceFuel(0),
        m_piceProtection(0)
    {};
    ~Shop() = default;

    // цена еды топлива и безопасности
    int m_piceFood;
    int m_piceFuel;
    int m_piceProtection;
};

class Planet
{
public:
    friend std::istream& operator>>(std::istream& is, Planet& item) //перегрузка метода ввода для планеты
    {
        is >> item.number >> item.label >> item.location >> item.resources >> item.shop.m_piceFood >> item.shop.m_piceFuel >> item.shop.m_piceProtection;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Planet& item) //перегрузка метода вывода для планеты
    {
        os << "\n " << item.number
            << "\t" << item.label
            << "\t" << item.resources
            << "\t\t" << abs(Spaceship::location - item.location);
        return os;
    }

    Planet() :
        number(0),
        location(0),
        resources(0)
    {};
    Planet(const Planet& over) = default;
    ~Planet() = default;

    //название, положение, ресурсы, магазин
    int number;
    std::string label;
    int location;
    int resources;
    Shop shop;
};

class Game
{
public:
    Game() = default;
    ~Game() = default;

    //запуск игры
    void run()
    {
        start();
        while (!is_ended())
        {
            showMenu();
            int choose;
            if (inputInt(choose))
            {
                switch (choose)
                {
                case 1: //полет
                {
                    bool flag = 0; // 1 - неправильный ввод пользователя
                    do
                    {
                        flag = 0;
                        outputAllPlanet();
                        int usersChoice;
                        usersChoice = choosingPlanet();
                        if (usersChoice == -1) { std::cout << "\nThe input was incorrect, please try again."; flag = 1; }
                        else
                        {
                            if (usersChoice == 0) { break; }
                            else // подходящее значение планеты
                            {
                                int possibility = possibilityOfFlight(usersChoice - 1);
                                if (possibility == -1)
                                {
                                    std::cout << "\nYou are already on this planet.";
                                    flag = 1;
                                }
                                else
                                {
                                    if (possibility == 0)
                                    {
                                        std::cout << "\nNot enough fuel, please try again.";
                                        flag = 1;
                                    }
                                    // долететь можно
                                    else
                                    {
                                        if (enemyOnWay())//попался враг
                                        {
                                            if (!attack()) { ended(); break; }
                                        }
                                        if (usersChoice == 1)
                                        {
                                            flyToEarth();
                                            break;
                                        }
                                        flyToPlanet(usersChoice - 1);
                                    }

                                }
                            }
                        }
                    } while (flag);
                    break;
                }
                case 2: //поиск ресурсов
                {
                    searchForResources();
                    break;
                }
                case 3: //вывод информации о корабле
                {
                    std::cout << m_mainSpaceship;
                    break;
                }
                case 4: // обмен ресурсов в магазине
                {
                    shopping();
                    break;
                }
                case 0: // выход из игры
                {
                    ended();
                    break;
                }
            deflaut:
                {
                    std::cout << "\nEnter a different value";
                }
                }
            }
        }
    }

    // старт игры 
    void start()
    {
        // создание планет по данным из файла
        if (auto inF = std::fstream("planet.txt"))
        {
            while (inF && !inF.eof())
            {
                Planet temp;
                inF >> temp;
                m_allPlanets.push_back(temp);
            }
        }

        if (m_allPlanets.empty())
        {
            std::cout << "\nCannot load planets.";
            return;
        }

        // приветственная запись
        std::cout << "Hi! You are the captain of a spaceship. "
            << "We are on the Ground now."
            << "\nLet's fly to some planet? (The flight is wasting fuel.)"
            << m_mainSpaceship;
    }

    // конец игры
    bool is_ended() const
    {
        if (m_mainSpaceship.m_protection < 0)
        {
            std::cout << "\nThe end of the game! See you next time!";
            return true;
        }
        else { return false; }
    }
    void ended() //принудительное завершение игры
    {
        m_mainSpaceship.m_protection = -1;
    }

    //cписок доступных действий
    void showMenu()
    {
        std::cout << "\n\nAvailable to you: "
            << "\n\t1.Flight to another planet"
            << "\n\t2.Resource search"
            << "\n\t3.Information about the ship"
            << "\n\t4.Exchange of resources in the store"
            << "\n\t0.Exit the game"
            << "\nEnter your choose ";
    }

    // вывод планет
    void outputAllPlanet()
    {
        std::cout << "\nThe output of data about the planet.";
        std::cout << "\nNum\t Label   \tResourses\tDistanse";

        for (auto&& planet : m_allPlanets) { std::cout << planet; }
    }

    // проверка на правильный номер планеты
    int choosingPlanet()//-1 - такой планеты нет, 0 - выход, иначе номер планеты для полета
    {
        std::cout << "\nEnter the number of the planet you want to fly to or 0 to exit: ";
        int numberPlanet;
        if (inputInt(numberPlanet))
        {
            if (numberPlanet < 0 && numberPlanet >((*m_allPlanets.cend()).number)) { return -1; }
            else { return numberPlanet; }
        }
        else
        {
            return -1;
        }
    }

    // проверка на топливо и расстояние до планеты
    int possibilityOfFlight(int num)
    {
        // расстояние до планеты
        int temp = abs(m_mainSpaceship.location - m_allPlanets[num].location);

        // проверка что не та же планета, что и сейчас, иначе -1
        if (temp == 0) { return -1; }
        // если топлива больше, чем расстояния, то 1, иначе 0
        else { return (m_mainSpaceship.m_fuel - temp >= 0); }
    }

    // возможность что враг попался на пути к планете
    bool enemyOnWay()
    {
        if (rand() % 3 < 2) // нет врага при 0 1
        {
            return false;
        }
        else //выпадение врага при 2
        {
            //генерация значений полей врага
            int temp = rand() % 70 + 50;//protection
            m_enemy(((double)temp / 100 * (rand() % 40 + 30)), ((double)temp / 100 * (rand() % 70 + 30)), temp);
            return true;
        }
    }

    // прилет на планету Земля и повышение ресурсов до минимума (100)
    void flyToEarth()
    {
        std::cout << "\nYou have arrived on Earth";
        m_mainSpaceship.location = 0;
        if (m_mainSpaceship.m_resources < 100) { m_mainSpaceship.m_resources = 100; }
        if (m_mainSpaceship.m_food < 100) { m_mainSpaceship.m_food = 100; }
        if (m_mainSpaceship.m_fuel < 100) { m_mainSpaceship.m_fuel = 100; }
        if (m_mainSpaceship.m_protection < 100) { m_mainSpaceship.m_protection = 100; }
    }

    // прилет на планету
    void flyToPlanet(int num)
    {
        //перелет на планету со сменой координат и вычетом топлива
        m_mainSpaceship.m_fuel -= abs(m_mainSpaceship.location - m_allPlanets[num].location);
        m_mainSpaceship.location = m_allPlanets[num].location;
        std::cout << "\n\nYou have arrived on the planet. (8-8)" << m_allPlanets[num];
    }

    // бой с врагами (сложение/вычитание ресурсов при победе/поражении)
    bool battle()
    {
        Sleep(1000);
        if (m_mainSpaceship.m_protection >= m_enemy.m_protection)
        {
            m_mainSpaceship.m_fuel += m_enemy.m_fuel;
            m_mainSpaceship.m_resources += m_enemy.m_resources;
            m_mainSpaceship.m_protection += (m_enemy.m_resources / 2) - 5;

            return true;
        }
        else
        { //проигрыш в бою
            m_mainSpaceship.m_protection -= 10;
            m_enemy.m_protection -= 10;

            return false;
        }
    }

    // бой с врагами логика
    bool attack()
    {
        std::cout << "\nOh no. You've been attacked! (:\\/)" << m_enemy;
        if (battle()) // сразу победа
        {
            std::cout << "\n\nCongratulations! You've won!"
                << m_mainSpaceship;

            return true;
        }
        else
        {
            std::cout << "\n\nNo luck! You've been defeated"
                << "\nYour protection = " << m_mainSpaceship.m_protection
                << "\nEnemy`s protection = " << m_enemy.m_protection;

            // вторая попытка и вожзможность перевести ресурсы в защиту
            int value;
            std::cout << "\nYou can transfer resources to protection points. Enter yes(1) or no(0): ";
            while (!inputInt(value)) { std::cout << "\nEnter yes - 1 or no - 0: "; }

            while (value == 1)
            {
                resourcesInBattle();
                std::cout << "\nYou can transfer resources to protection points. Enter yes - 1 or no - 0: ";

                while (!inputInt(value)) { std::cout << "\nEnter yes - 1 or no - 0: "; }
            }
            if (battle())
            {
                std::cout << "\n\nCongratulations! You've won!"
                    << m_mainSpaceship;
                return true;
            }
            else
            {
                std::cout << "\nGame over! You've lost!";
                return false;
            }
        }
    }

    //обмен ресурсов во время боя
    void resourcesInBattle()
    {
        std::cout << "\nYou can get 1 point of protection for 3 resource points.";
        std::cout << "\nYous resource points: " << m_mainSpaceship.m_resources;
        std::cout << "\nEnter the number of protection to share: ";
        int valueInt;// очки ресурсов для обмена
        while (!inputInt(valueInt)) { std::cout << "\nEnter the number of protection to share: "; }

        while (valueInt > (m_mainSpaceship.m_resources / 3)) {
            std::cout << "\nYou don't have that many resources. Enter the number of protection to share: ";
            if (!inputInt(valueInt)) { valueInt = (m_mainSpaceship.m_resources / 3) + 1; }
        }
        m_mainSpaceship.m_resources -= valueInt * 3;
        m_mainSpaceship.m_protection += valueInt;
        std::cout << "\n\nSuccessful exchange"
            << "\nYour protection = " << m_mainSpaceship.m_protection
            << "\nEnemy`s protection = " << m_enemy.m_protection;
    }

    // поиск ресурсов на планете
    void searchForResources()
    {
        auto iter = m_allPlanets.begin();
        while ((*iter).location != m_mainSpaceship.location) { ++iter; }
        int i = 0;
        while ((*iter).resources > 0 && m_mainSpaceship.m_food > 0)
        {
            if (i == 5)
            {
                std::cout << "\nContinue searching for resources? (Yes - 1, No - 0): ";
                if (inputInt(i))
                {
                    if (i == 0) { break; }
                    else i = 0;
                }
                else
                {
                    i = 5;
                }
            }
            else
            {
                i++;
                std::cout << "\n\nYour resources: " << m_mainSpaceship.m_resources
                    << "\nYour food: " << m_mainSpaceship.m_food
                    << "\nPlanet`s resources: " << (*iter).resources;
                Sleep(500);
                gettingResources(iter);
            }
        }
        std::cout << std::endl;
        if ((*iter).resources <= 0) { std::cout << "\nThe planet's resources have run out."; }
        if (m_mainSpaceship.m_food <= 0) { std::cout << "\nWe can't continue the search without food."; }
    }

    //получение ресурсов и вычитание их из планеты
    void gettingResources(std::vector<Planet>::iterator iterPlanet)
    {
        if (m_mainSpaceship.m_food < 3) m_mainSpaceship.m_food = 0;
        else { m_mainSpaceship.m_food -= 3; }
        if ((*iterPlanet).resources < 3) (*iterPlanet).resources = 0;
        else { (*iterPlanet).resources -= 7; }
        m_mainSpaceship.m_resources += 7;
    }

    // обмен ресурсов в магазине

    void shopping()
    {
        auto iter = m_allPlanets.begin();
        while ((*iter).location != m_mainSpaceship.location) { ++iter; }

        //массив пар с указателем на значение продукта в корабле и на цену такого продукта в этом магазине
        std::pair<int*, int*> masValuePrice[] = { {&(m_mainSpaceship.m_fuel), &((*iter).shop.m_piceFuel)},
                                                  {&(m_mainSpaceship.m_food), &((*iter).shop.m_piceFood)},
                                                  {&(m_mainSpaceship.m_protection), &((*iter).shop.m_piceProtection)} };

        std::cout << (*iter).shop;
        std::cout << "\nYour resources:" << m_mainSpaceship.m_resources;

        int numProd;
        do
        {
            std::cout << "\nEnter the number of the product you want to buy: ";
            if (!inputInt(numProd)) { numProd = -1; }
        } while (numProd < 0 && numProd>3);
        if (numProd == 0) return;

        int quanProd = 0;
        do
        {
            std::cout << "\nEnter the quantity of the product you want to buy: ";
            if (inputInt(quanProd))
            {
                if (m_mainSpaceship.m_resources < (quanProd * *(masValuePrice[numProd - 1].second)))
                {
                    std::cout << "\nThere are not enough resources to purchase the product";
                }
            }
            else { quanProd = 1000000; }
        } while (m_mainSpaceship.m_resources < (quanProd * *(masValuePrice[numProd - 1].second)));
        if (quanProd == 0) return;

        *(masValuePrice[numProd - 1].first) += quanProd;
        m_mainSpaceship.m_resources -= (quanProd * *(masValuePrice[numProd - 1].second));
        std::cout << "\nThe purchase is successful! " << m_mainSpaceship;
    }


    Spaceship m_mainSpaceship;
    std::vector<Planet> m_allPlanets;
    Enemy m_enemy;
};
