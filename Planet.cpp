
#include "Planet.h"


std::istream& operator>>(std::istream& is, Planet& item) //перегрузка метода ввода для планеты
{
    is >> item.number >> item.label >> item.location >> item.resources >> item.shop;
    return is;
};

std::ostream& operator<<(std::ostream& os, Planet& item) //перегрузка метода вывода для планеты
{
    os << "\n " << item.number
        << "\t" << item.label
        << "\t" << item.resources
        << "\t\t" << abs(Spaceship::location - item.location);
    return os;
};

Planet::Planet() :
    number(0),
    location(0),
    resources(0)
{};

void Planet::removeResources(int value)
{
    if (value > resources) { value = resources; }
    resources -= value;
}