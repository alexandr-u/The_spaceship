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