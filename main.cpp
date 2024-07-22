#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "windows.h"

class Spaceship
{
public:
    Spaceship() //начальные ресурсы игрока
    {
        location = 0;
        m_resources = 100;
        m_food = 100;
        m_fuel = 100;
        m_protection = 100;
    }
    ~Spaceship() = default;
    //resources. food. fuel. location. protection.
    static int location;
    int m_resources;
    int m_food;
    int m_fuel;
    int m_protection;
    friend std::ostream& operator<<(std::ostream& os, Spaceship& item)  //перегрузка метода вывода для планеты
    {
        os << "\nNow you have: \nfuel\t\t" << item.m_fuel << "\nfood\t\t" << item.m_food << "\nprotection\t" << item.m_protection << "\nresources\t" << item.m_resources;
        return os;
    }
};

class Enemy
{
public:
    //resources. fuel. protection.
    int m_resources;
    int m_fuel;
    int m_protection;
    Enemy() = default;
    Enemy(int resourcesValue, int fuelValue, int protectionValue) : m_resources(resourcesValue), m_fuel(fuelValue), m_protection(protectionValue) {};
    Enemy(const Enemy& over) = default;
    void operator () (int resourcesValue, int fuelValue, int protectionValue) //вносить данные через скобочки
    {
        m_resources = resourcesValue;
        m_fuel = fuelValue;
        m_protection = protectionValue;
    }
    ~Enemy() = default;
    friend std::ostream& operator<<(std::ostream& os, Enemy& item) //перегрузка метода вывода для врага
    {
        os << "\nInformation about the enemy:\nfuel\t\t" << item.m_fuel << "\nprotection\t" << item.m_protection << "\nresources\t" << item.m_resources;
        return os;
    }
};

class Shop
{
public:
    // цена еды топлива и безопасности
    int m_piceFood;
    int m_piceFuel;
    int m_piceProtection;
    Shop() = default;
    ~Shop() = default;
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
        is >> item.label >> item.location >> item.resources >> item.shop.m_piceFood>> item.shop.m_piceFuel>> item.shop.m_piceProtection;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Planet& item) //перегрузка метода вывода для планеты
    {
        os << "\n " << item.label << "\t" << item.resources << "\t\t" << abs(Spaceship::location - item.location);
        return os;
    }

};

class Game
{
public:
    Spaceship m_mainSpaceship;
    std::vector<Planet> m_allPlanets;
    Enemy m_enemy;

    Game() = default;
    ~Game() = default;
    // запуск игры 
    void start()
    {
        // приветственная запись
        std::cout << "Hi! You are the captain of a spaceship.  We are on the Ground now. \nLet's fly to some planet? (The flight is wasting fuel.)" << m_mainSpaceship;
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
            //полет
            fly();
        }
        else { std::cout << "\nThe planet file was not found"; }

    }
    // проигрыш (когда защита при бое с врагом меньше на 1)
    void endOfGame() const
    {
        std::cout << "\nThe end of the game! See you next time!";
    }
    // вывод планет
    void outputAllPlanet()
    {
        std::cout << "\nThe output of data about the planet.";
        std::cout << "\n Label   \tResourses\tDistanse";
        auto beginVec = m_allPlanets.begin();
        while (beginVec != m_allPlanets.end())
        {
            std::cout << *beginVec++;
        }
    }
    // полет на планету + возможность врагов
    void fly()
    {
        //вывод планет
        outputAllPlanet();
        std::cout << "\nEnter the name of the planet you want to fly to or the quit to exit: ";
        std::string namePlanet;
        std::cin >> namePlanet;
        if (namePlanet != "quit" && namePlanet != "Quit")
        {
            auto beginVec = m_allPlanets.begin();
            bool flag = 0; // проверка что нашлось такое имя
            if (namePlanet != "Earth" && namePlanet != "Earth(Home)") 
            {
                while (beginVec != m_allPlanets.end() && !flag)
                {
                    if (namePlanet == beginVec->label) { flag = 1; }
                    else { ++beginVec; }
                }
            }
            else { flag = 1; }
            if (flag)
            {
                if (abs(m_mainSpaceship.location - beginVec->location) != 0) //проверка что не та же планета, что и сейчас
                {
                    //проверка, что топлива хватает
                    if ((m_mainSpaceship.m_fuel - abs(m_mainSpaceship.location - beginVec->location)) >= 0)
                    {
                        if (rand() % 3 < 2) //случайное решение выпадение врага при 0 1 
                        {
                            if (namePlanet != "Earth" && namePlanet != "Earth(Home)") { flyToPlanet(beginVec); }
                            else { flyToEarth(); }
                        }
                        else //выпадение врага при 2
                        {
                            //Oh no. You've been attacked!
                            //генерация значений полей врага и его отправление на бой
                            int temp = rand() % 70 + 50;//protection
                            m_enemy(((double)temp / 100 * (rand() % 40 + 30)), ((double)temp / 100 * (rand() % 70 + 30)), temp);
                            if (attack()) //победа
                            {
                                if (namePlanet != "Earth" && namePlanet != "Earth(Home)") { flyToPlanet(beginVec); }
                                else { flyToEarth(); }
                            }
                            else { menu(); }
                        }
                    }
                    else
                    {
                        std::cout << "\nThere is not enough fuel for the flight, choose another planet";
                        fly();
                    }
                }
                else
                {
                    std::cout << "\nYou are already on this planet, choose another planet";
                    fly();
                }
            }
            else
            {
                std::cout << "\nA planet with that name has not been found. Please try again";
                fly();
            }
        }
    }
    //выбор доступных действий
    void menu()
    {
        int choose;
        std::cout << "\nAvailable to you: \n\t1.Flight to another planet\n\t2.Resource search\n\t3.Information about the ship\n\t4.Exchange of resources in the store\n\t0.Exit the game\nEnter your choose ";
        std::cin >> choose;
        switch (choose)
        {
        case 1:
            fly();
            break;
        case 2:
            std::cout << "\nSorry, the feature is in development";
            menu();
            break;
        case 3:
            std::cout << m_mainSpaceship;
            menu();
            break;
        case 4:
            std::cout << "\nSorry, the feature is in development";
            menu();
            break;
        case 0:
            endOfGame();
            break;
        deflaut:
            std::cout << "\nEnter a different value";
            menu();
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
        //приводит к выбору доступных действий
        menu();
    }
    // прилет на планету
    void flyToPlanet(std::vector<Planet>::iterator vecPlanet)
    {
        //перелет на планету со сменой координат и вычетом топлива
        m_mainSpaceship.m_fuel -= abs(m_mainSpaceship.location - vecPlanet->location);
        m_mainSpaceship.location = vecPlanet->location;
        std::cout << "\n\nYou have arrived on the planet. (8-8)" << *vecPlanet;
        //приводит к выбору доступных действий
        menu();
    }
    // бой с врагами (бул)
    bool battle()
    {
        Sleep(1000);
        if (m_mainSpaceship.m_protection >= m_enemy.m_protection)
        {
            m_mainSpaceship.m_fuel += m_enemy.m_fuel;
            m_mainSpaceship.m_resources += m_enemy.m_resources;
            m_mainSpaceship.m_protection += (m_enemy.m_resources / 2) - 5;
            std::cout << "\n\nCongratulations! You've won!" << m_mainSpaceship;
            return true;
        }
        else
        {
            m_mainSpaceship.m_protection -= 10;
            m_enemy.m_protection -= 10;
            std::cout << "\n\nNo luck! You've been defeated\nYour protection = " << m_mainSpaceship.m_protection << "\nEnemy`s protection = " << m_enemy.m_protection;
            return false;
        }
    }
    // бой с врагами логика
    bool attack()
    {
        std::cout << "\nOh no. You've been attacked! (:\\/)" << m_enemy;
        if (battle())
        {
            return true;
        }
        else
        {
            //здесь вожзможность перевести ресурсы в защиту
            std::string value;
            std::cout << "\nYou can transfer resources to protection points. Enter yes or no: ";
            std::cin>>value;
            while (value[0] == 'Y' || value[0] == 'y')
            {
                std::cout << "\nYou can get one point of protection for three resource points.";
                std::cout << "\nYous resource points: "<<m_mainSpaceship.m_resources;
                std::cout << "\nEnter the number of protection to share. ";
                int valueInt;// очки ресурсов для обмена
                std::cin >> valueInt;
                while (valueInt > (m_mainSpaceship.m_resources/3)) {
                    std::cout << "\nYou don't have that many resources. Enter the number of protection to share. ";
                    std::cin >> valueInt;
                }
                m_mainSpaceship.m_resources -= valueInt*3;
                m_mainSpaceship.m_protection += valueInt;
                std::cout << "\n\nSuccessful exchange\nYour protection = " << m_mainSpaceship.m_protection << "\nEnemy`s protection = " << m_enemy.m_protection;
                std::cout << "\nYou can transfer resources to protection points. Enter yes or no: ";
                std::cin >> value;
            }            
            if (battle()) { return true; }
            else
            {
                std::cout << "\nGame over! You've lost!";
                return false;
            }
        }

    }
    // поиск ресурсов на планете + возможность врагов
    // обмен ресурсов в магазине
};

int Spaceship::location = 0;

int main()
{
    srand(time(0)); //rand()
    Game main;
    main.start();

    return 0;
}