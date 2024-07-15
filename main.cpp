#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

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
    friend std::ostream& operator<<(std::ostream& os, Spaceship& item) //перегрузка метода вывода для планеты
    {
        os << "\nNow you have: \noil\t\t"<< item.oil<<"\nfood\t\t"<<item.food<<"\nsafety\t\t"<< item.safety << "\nresources\t"<<item.resources;
        return os;
    }
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
        // приветственная запись
        std::cout << "Hi! You are the captain of a spaceship.  We are on the Ground now. \nLet's fly to some planet? (The flight is wasting oil.)"<< mainSpaceship;
        // создание планет по данным из файла
        std::vector<Planet> allPlanets;
        std::fstream inF;
        inF.open("planet.txt");
        if (!inF.eof())
        {
            while (!inF.eof())
            {
                Planet temp;
                inF >> temp;
                allPlanets.push_back(temp);
            }
            //вывод планет
            auto a = allPlanets.begin();
            outputAllPlanet(allPlanets.begin(), allPlanets.end());
            //полет
            fly(allPlanets.begin(), allPlanets.end());
        }
        else { std::cout << "\nThe planet file was not found"; }

    }
    // проигрыш (когда защита при бое с врагом меньше на 1)
    // вывод планет
    void outputAllPlanet(std::vector<Planet>::iterator beginVec, std::vector<Planet>::iterator endVec)
    {
        std::cout << "\nThe output of data about the planet.";
        while (beginVec != endVec)
        {
            std::cout << *beginVec++;
        }
    }
    // полет на планету + возможность врагов
    void fly(std::vector<Planet>::iterator beginVec, std::vector<Planet>::iterator endVec)
    {
        std::cout << "\nEnter the name of the planet you want to fly to or the quit to exit";
        std::string namePlanet;
        std::cin >> namePlanet;
        if (namePlanet != "quit" && namePlanet != "Quit")
        {
            bool flag = 0; // проверка что нашлось такое имя
            while (beginVec != endVec && !flag)
            {
                if (namePlanet == beginVec->label) { flag = 1; }
                else { ++beginVec; }
            }
            if (flag)
            {
                //перелет на планету со сменой координат и вычетом топлива
            }
            else
            {
                std::cout << "\nA planet with that name has not been found. Please try again";
                fly(beginVec, endVec);
            }
        }
        // else приводит к выбору доступных действий
    }
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
