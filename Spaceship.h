#pragma once
#include <iostream>
#include "SpaceItem.h"

class Spaceship : public SpaceItem
{
public:
    friend std::ostream& operator<<(std::ostream& os, Spaceship& item);

    static int location;

    //начальные ресурсы игрока
    Spaceship() :
        SpaceItem::SpaceItem(100, 100, 100),
        m_food(100) {};
    ~Spaceship() = default;

    int getFood() const;

    void setFood(int velueFood);
    void setProtectionEnded();

    void addFood(int velueFood);

private:
    int m_food;
};