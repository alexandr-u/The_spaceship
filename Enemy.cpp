#include "Enemy.h"

extern int zeroIfNegative(int& value);

std::ostream& operator<<(std::ostream& os, Enemy& item)
{
    os << "\nInformation about the enemy:"
        << "\nfuel\t\t" << item.m_fuel
        << "\nprotection\t" << item.m_protection
        << "\nresources\t" << item.m_resources;
    return os;
}
void Enemy::operator () (int resourcesValue, int fuelValue, int protectionValue) 
{
    m_resources = resourcesValue;
    m_fuel = fuelValue;
    m_protection = protectionValue;
}