#pragma once
#include <iostream>

class Shop
{
public:
    friend std::ostream& operator<<(std::ostream& os, Shop& item);
    friend std::istream& operator>>(std::istream& is, Shop& item); 

    Shop() :
        m_piceFood(0),
        m_piceFuel(0),
        m_piceProtection(0)
    {};
    ~Shop() = default;

    int getPriceFood() const { return m_piceFood; }
    int getPriceFuel() const { return m_piceFuel; }
    int getPriceProtection() const { return m_piceProtection; }

private:
    int m_piceFood;
    int m_piceFuel;
    int m_piceProtection;
};