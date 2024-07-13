#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Spaceship
{
public:
    Spaceship()
    {
        location = 0;
        resources = 100;
        food = 100;
        oil = 100;
        safety = 100;
    }
    //resources. food. oil. location. safety.
    static int location;
    int resources;
    int food;
    int oil;
    int safety;
};

class Enemy
{
public:
    //resources. oil. safety.
    int resources;
    int oil;
    int safety;
};

class Shop
{
public:
    // цена еды топлива и безопасности
    int p_food;
    int p_oil;
    int p_safety;
};

class Planet
{
public:
    Planet() = default;
    Planet(const Planet& over) = default;
    ~Planet() = default;
    //resources. location.
    std::string label;
    int location;
    int resources;
    Shop shop;

    friend std::istream& operator>>(std::istream& is, Planet& item) //перегрузка метода ввода для планеты
    {
        is >> item.label >> item.location >> item.resources;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Planet& item) //перегрузка метода вывода для планеты
    {
        os << "\n\nThe name of the planet:\t" << item.label << "\nDistance to the planet:\t" << abs(Spaceship::location - item.location) << "\nNumber of available resources:\t" << item.resources;
        return os;
    }

};

class Play
{
public:
    // запуск игры 
    void start()
    {
        // созрание корабля игрока
        Spaceship mainSpaceship;
        // создание планет по данным из файла
        std::vector<Planet> allPlanets;
        std::fstream inF;
        inF.open("planet.txt");
        while (!inF.eof())
        {
            Planet temp;
            inF >> temp;
            allPlanets.push_back(temp);
        }
        outputAllPlanet(allPlanets);
    }
    // проигрыш (когда защита при бое с врагом меньше на 1)
    // вывод планет
    void outputAllPlanet(std::vector<Planet> vec)
    {
        for (auto& el : vec) {
            std::cout << "\nThe output of data about the planet." << el;
        }
    }
    // полет на планету + возможность врагов
    // обмен ресурсов в магазине на планете
    // бой с врагами (бул)
    // бой с врагами логика
    // поиск ресурсов на планете + возможность врагов
    // прилет на землю с пополнением всех полей до минимума (100)
};

int Spaceship::location = 0;

int main()
{
    srand(time(0)); //rand()
    Play main;
    main.start();

    return 0;
}