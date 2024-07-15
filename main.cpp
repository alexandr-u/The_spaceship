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
    Spaceship m_mainSpaceship;
    std::vector<Planet> m_allPlanets;
    Play() = default;
    // запуск игры 
    void start()
    {
        // приветственная запись
        std::cout << "Hi! You are the captain of a spaceship.  We are on the Ground now. \nLet's fly to some planet? (The flight is wasting oil.)"<< m_mainSpaceship;
        // создание планет по данным из файла
        m_allPlanets;
        std::fstream inF;
        inF.open("planet.txt");
        if (!inF.eof())
        {
            while (!inF.eof())
            {
                Planet temp;
                inF >> temp;
                m_allPlanets.push_back(temp);
            }
            //вывод планет
            outputAllPlanet();
            //полет
            fly();
        }
        else { std::cout << "\nThe planet file was not found"; }

    }
    // проигрыш (когда защита при бое с врагом меньше на 1)
    // вывод планет
    void outputAllPlanet()
    {
        std::cout << "\nThe output of data about the planet.";
        auto beginVec = m_allPlanets.begin();
        while (beginVec != m_allPlanets.end())
        {
            std::cout << *beginVec++;
        }
    }
    // полет на планету + возможность врагов
    void fly()
    {
        std::cout << "\nEnter the name of the planet you want to fly to or the quit to exit: ";
        std::string namePlanet;
        std::cin >> namePlanet;
        if (namePlanet != "quit" && namePlanet != "Quit")
        {
            auto beginVec = m_allPlanets.begin();
            bool flag = 0; // проверка что нашлось такое имя
            while (beginVec != m_allPlanets.end() && !flag)
            {
                if (namePlanet == beginVec->label) { flag = 1; }
                else { ++beginVec; }
            }
            if (flag)
            {
                //перелет на планету со сменой координат и вычетом топлива
                m_mainSpaceship.oil -= abs(m_mainSpaceship.location - beginVec->location);
                m_mainSpaceship.location = beginVec->location;
                std::cout << "\nYou have arrived on the planet." << *beginVec;
                //приводит к выбору доступных действий
            }
            else
            {
                std::cout << "\nA planet with that name has not been found. Please try again";
                fly();
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
