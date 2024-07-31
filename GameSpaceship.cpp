
#include "GameSpaceship.h"

std::random_device r;
std::default_random_engine randInt(r());

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

int zeroIfNegative(int& value) { if (value < 0) { value = 0; } return value; }

void Game::run()
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
                                        m_mainSpaceship.flyToEarth();
                                        break;
                                    }
                                    m_mainSpaceship.flyToPlanet(m_allPlanets[usersChoice - 1].getLocation());
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
    system("pause");
}

void Game::start()
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
        ended();
        return;
    }

    // приветственная запись
    std::cout << "Hi! You are the captain of a spaceship. "
        << "We are on the Ground now."
        << "\nLet's fly to some planet? (The flight is wasting fuel.)"
        << m_mainSpaceship;
}
bool Game::is_ended() const
{
    if (m_mainSpaceship.getProtection() < 0)
    {
        std::cout << "\nThe end of the game! See you next time!\n";
        return true;
    }
    if (m_mainSpaceship.getFood() == 0) { return true; }
    else { return false; }
}
void Game::ended() //принудительное завершение игры
{
    m_mainSpaceship.setProtectionEnded();
}

//cписок доступных действий
void Game::showMenu() const
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
void Game::outputAllPlanet()
{
    std::cout << "\nThe output of data about the planet.";
    std::cout << "\nNum\t Label   \tResourses\tDistanse";

    for (auto&& planet : m_allPlanets) { std::cout << planet; }
}

// проверка на правильный номер планеты
int Game::choosingPlanet()//-1 - такой планеты нет, 0 - выход, иначе номер планеты для полета
{
    std::cout << "\nEnter the number of the planet you want to fly to or 0 to exit: ";
    int numberPlanet;
    if (inputInt(numberPlanet))
    {
        if (numberPlanet < 0 && numberPlanet >((*m_allPlanets.cend()).getNumber())) { return -1; }
        else { return numberPlanet; }
    }
    else
    {
        return -1;
    }
}

// проверка на топливо и расстояние до планеты
int Game::possibilityOfFlight(int num)
{
    // расстояние до планеты
    int temp = abs(m_mainSpaceship.location - m_allPlanets[num].getLocation());

    // проверка что не та же планета, что и сейчас, иначе -1
    if (temp == 0) { return -1; }
    // если топлива больше, чем расстояния, то 1, иначе 0
    else { return (m_mainSpaceship.getFuel() - temp >= 0); }
}

// возможность что враг попался на пути к планете
bool Game::enemyOnWay()
{
    if (randInt() % 3 < 2) // нет врага при 0 1
    {
        return false;
    }
    else //выпадение врага при 2
    {
        //генерация значений полей врага
        int temp = m_mainSpaceship.getProtection() * (double(randInt() % 4 + 8) / 10);//protection
        m_enemy(((double)temp / 100 * (randInt() % 30 + 10)), ((double)temp / 100 * (randInt() % 30 + 10)), temp);
        return true;
    }
}

// бой с врагами (сложение/вычитание ресурсов при победе/поражении)
bool Game::battle()
{
    m_mainSpaceship.setFood(m_mainSpaceship.getFood() - 5);
    Sleep(1000);
    if (m_mainSpaceship.getProtection() >= m_enemy.getProtection())
    {
        m_mainSpaceship.addFuel(m_enemy.getFuel());
        m_mainSpaceship.addResources(m_enemy.getResources());

        return true;
    }
    else
    { //проигрыш в бою
        m_mainSpaceship.setProtection(m_mainSpaceship.getProtection() - 10);
        m_enemy.setProtection(m_enemy.getProtection() - 10);

        return false;
    }
}

// бой с врагами логика
bool Game::attack()
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
            << "\nYour protection = " << m_mainSpaceship.getProtection()
            << "\nEnemy`s protection = " << m_enemy.getProtection();

        // вторая попытка и вожзможность перевести ресурсы в защиту
        int value;
        std::cout << "\nYou can transfer resources to protection points. Enter yes(1) or no(0): ";
        while (!inputInt(value)) { std::cout << "\nEnter yes - 1 or no - 0: "; }

        while (value == 1)
        {
            exchangeOfResourcesDuringTheBattle();
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
void Game::exchangeOfResourcesDuringTheBattle()
{
    std::cout << "\nYou can get 1 point of protection for 3 resource points.";
    std::cout << "\nYous resource points: " << m_mainSpaceship.getResources();
    std::cout << "\nEnter the number of protection to share: ";
    int valueInt;// очки ресурсов для обмена
    while (!inputInt(valueInt)) { std::cout << "\nEnter the number of protection to share: "; }

    while (valueInt > (m_mainSpaceship.getResources() / 3)) {
        std::cout << "\nYou don't have that many resources. Enter the number of protection to share: ";
        if (!inputInt(valueInt)) { valueInt = (m_mainSpaceship.getResources() / 3) + 1; }
    }
    m_mainSpaceship.setResources(m_mainSpaceship.getResources() - valueInt * 3);
    m_mainSpaceship.addProtection(valueInt);
    std::cout << "\n\nSuccessful exchange"
        << "\nYour protection = " << m_mainSpaceship.getProtection()
        << "\nEnemy`s protection = " << m_enemy.getProtection();
}

// поиск ресурсов на планете
void Game::searchForResources()
{
    auto iter = m_allPlanets.begin();
    while ((*iter).getLocation() != m_mainSpaceship.location) { ++iter; }
    int i = 0;
    while ((*iter).getResources() > 0 && m_mainSpaceship.getFood() > 0)
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
            std::cout << "\n\nYour resources: " << m_mainSpaceship.getResources()
                << "\nYour food: " << m_mainSpaceship.getFood()
                << "\nPlanet`s resources: " << (*iter).getResources();
            Sleep(500);
            gettingResources(iter);
        }
    }
    std::cout << std::endl;
    if ((*iter).getResources() <= 0) { std::cout << "\nThe planet's resources have run out."; }
    if (m_mainSpaceship.getFood() <= 0) { std::cout << "\nWe can't continue the search without food."; }
}

//получение ресурсов и вычитание их из планеты
void Game::gettingResources(std::vector<Planet>::iterator iterPlanet)
{
    if (m_mainSpaceship.getFood() < 3) m_mainSpaceship.setFood(0);
    else { m_mainSpaceship.setFood(m_mainSpaceship.getFood() - 3); }
    (*iterPlanet).removeResources(7);
    m_mainSpaceship.addResources(7);
}

// обмен ресурсов в магазине

void Game::shopping()
{
    auto iter = m_allPlanets.begin();
    while ((*iter).getLocation() != m_mainSpaceship.location) { ++iter; }

    //массив пар с указателем на значение продукта в корабле и на цену такого продукта в этом магазине
    std::pair<void (Spaceship::*)(int), int> masValuePrice[] = { {(&Spaceship::addFuel), ((*iter).shop.getPriceFuel())},
                                              {(&Spaceship::addFood), ((*iter).shop.getPriceFood())},
                                              {(&Spaceship::addProtection), ((*iter).shop.getPriceProtection())} };

    //void (Spaceship::* f)(int) = &Spaceship::setFuel;
    //(m_mainSpaceship.*f)(11);

    std::cout << (*iter).shop;
    std::cout << "\nYour resources:" << m_mainSpaceship.getResources();

    int numProd;
    do
    {
        std::cout << "\nEnter the number of the product you want to buy: ";
        if (!inputInt(numProd)) { numProd = -1; }
    } while (numProd < 0 || numProd>3);
    if (numProd == 0) return;

    int quanProd = 0;
    do
    {
        std::cout << "\nEnter the quantity of the product you want to buy: ";
        if (inputInt(quanProd))
        {
            if (m_mainSpaceship.getResources() < (quanProd * (masValuePrice[numProd - 1].second)))
            {
                std::cout << "\nThere are not enough resources to purchase the product";
            }
        }
        else { quanProd = 1000000; }
    } while (m_mainSpaceship.getResources() < (quanProd * (masValuePrice[numProd - 1].second)));
    if (quanProd == 0) return;

    (m_mainSpaceship.*(masValuePrice[numProd - 1].first))(quanProd);
    m_mainSpaceship.setResources(m_mainSpaceship.getResources() - (quanProd * (masValuePrice[numProd - 1].second)));
    std::cout << "\nThe purchase is successful! " << m_mainSpaceship;
}