
#include "Shop.h"

std::ostream& operator<<(std::ostream& os, Shop& item)
{
    os << "\nProduct price (resources): "
        << "\n1. Fuel\t\t" << item.m_piceFuel
        << "\n2. Food\t\t" << item.m_piceFood
        << "\n3. Protection\t" << item.m_piceProtection;
    return os;
};

std::istream& operator>>(std::istream& is, Shop& item)
{
    is >> item.m_piceFood >> item.m_piceFuel >> item.m_piceProtection;
    return is;
};