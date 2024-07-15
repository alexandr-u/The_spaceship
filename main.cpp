#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "windows.h"

class Spaceship
{
public:
    Spaceship() //начальные ресурсы игрока
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
    Enemy() = default;
    Enemy(int resourcesValue, int oilValue, int safetyValue) : resources(resourcesValue), oil(oilValue), safety(safetyValue) {};
    Enemy(const Enemy& over) = default;
    void operator () (int resourcesValue, int oilValue, int safetyValue) //вносить данные через скобочки
    {
        resources = resourcesValue;
        oil = oilValue;
        safety = safetyValue;
    }
    ~Enemy() = default;
    friend std::ostream& operator<<(std::ostream& os, Enemy& item) //перегрузка метода вывода для врага
    {
        os <<"\nInformation about the enemy.\nresources\t"<< item.resources <<"\noil\t\t" << item.oil << "\nsafety\t\t" << item.safety;
        return os;
    }
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
    Enemy m_enemy;

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
    void endOfGame()
    {
        std::cout << "\nThe end of the game! See you next time!";
    }
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
                //проверка, что топлива хватает
                if ((m_mainSpaceship.oil - abs(m_mainSpaceship.location - beginVec->location))>=0)
                {
                    if (rand()%3<2) //случайное решение выпадение врага при 0 1 
                    {
                        if (namePlanet != "Earth") { flyToPlanet(beginVec); }
                        else { flyToEarth(); }
                    }
                    else //выпадение врага при 2
                    {
                        //Oh no. You've been attacked!
                        //генерация значений полей врага и его отправление на бой
                        int temp = rand() % 70 + 50;//safety
                        m_enemy(((double)temp/100*(rand()%40+30)), ((double)temp/100*(rand()%70+30)), temp);
                        if (attack()) //победа
                        {
                            if (namePlanet != "Earth") { flyToPlanet(beginVec); }
                            else { flyToEarth(); }
                        }
                        else { endOfGame(); }
                    }
                }
                else
                {
                    std::cout << "\nThere is not enough oil for the flight, choose another planet";
                    fly();
                }
            }
            else
            {
                std::cout << "\nA planet with that name has not been found. Please try again";
                fly();
            }
        }
        // else приводит к выбору доступных действий
    }
    // прилет на планету Земля и повышение ресурсов до минимума (100)
    void flyToEarth()
    {
        std::cout << "\nYou have arrived on Earth";
        m_mainSpaceship.location = 0;        
        if (m_mainSpaceship.resources < 100) { m_mainSpaceship.resources = 100; }
        if (m_mainSpaceship.food < 100) { m_mainSpaceship.food = 100; }
        if (m_mainSpaceship.oil < 100) { m_mainSpaceship.oil = 100; }
        if (m_mainSpaceship.safety < 100) { m_mainSpaceship.safety = 100; }
        //приводит к выбору доступных действий
     }
    // прилет на планету
    void flyToPlanet(std::vector<Planet>::iterator vecPlanet)
    {
        //перелет на планету со сменой координат и вычетом топлива
        m_mainSpaceship.oil -= abs(m_mainSpaceship.location - vecPlanet->location);
        m_mainSpaceship.location = vecPlanet->location;
        std::cout << "\nYou have arrived on the planet." << *vecPlanet;
        //приводит к выбору доступных действий
    }
    // обмен ресурсов в магазине на планете
    // бой с врагами (бул)
    bool battle()
    {
        Sleep(1000);
        if (m_mainSpaceship.safety >= m_enemy.safety)
        {
            m_mainSpaceship.oil += m_enemy.oil;
            m_mainSpaceship.resources += m_enemy.resources;
            m_mainSpaceship.safety += (m_enemy.resources / 2)-5;
            std::cout << "\n\nCongratulations! You've won!"<< m_mainSpaceship;
            return true;
        }
        else
        {
            m_mainSpaceship.safety -= 10;
            m_enemy.safety -= 10;
            std::cout << "\n\nNo luck! You've been defeated\nYour safety = "<< m_mainSpaceship.safety<<"\nEnemy`s safety = "<< m_enemy.safety;
            return false;
        }
    }
    // бой с врагами логика
    bool attack()
    {
        std::cout << "\nOh no. You've been attacked!" << m_enemy;
        if (battle()) 
        {
            
            return true;
        }
        else
        {
            //здесь вожзможность перевести ресурсы в защиту
            std::cout << "\nYou can transfer resources to safety";
            if (battle()) { return true; }
            else 
            { 
                std::cout << "\nComplete defeat. You've lost!";
                return false; 
            }
        }

    }
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
