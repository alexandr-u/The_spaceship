#include "Spaceship.h"


extern int zeroIfNegative(int& value);

std::ostream& operator<<(std::ostream& os, Spaceship& item)
{
    os << "\nNow you have: "
        << "\nfuel\t\t" << item.m_fuel
        << "\nfood\t\t" << item.m_food
        << "\nprotection\t" << item.m_protection
        << "\nresources\t" << item.m_resources;
    return os;
}
int Spaceship::getFood() const { return m_food; }

void Spaceship::setFood(int velueFood) { m_food = zeroIfNegative(velueFood); }
void Spaceship::setProtectionEnded() { m_protection = -1; }

void Spaceship::addFood(int velueFood) { m_food += zeroIfNegative(velueFood); }

void Spaceship::flyToEarth()
{
    std::cout << "\nYou have arrived on Earth";
    location = 0;
    if (m_resources < 100) { m_resources=100; }
    if (m_food < 100) { m_food = 100; }
    if (m_fuel < 100) { m_fuel = 100; }
    if (m_protection < 100) { m_protection = 100; }
}

// прилет на планету
void Spaceship::flyToPlanet(int loc)
{
    //перелет на планету со сменой координат и вычетом топлива
    m_fuel= (m_fuel - abs(location - loc));
    location = loc;
    std::cout << "\n\nYou have arrived on the planet. (8-8)";
}

//получение ресурсов и вычитание их из планеты
void Spaceship::gettingResources(Planet& planet)
{
    if (m_food < 3) m_food=0;
    else { m_food -= 3; }
    (planet).removeResources(7);
    m_resources += 7;
}
