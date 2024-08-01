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