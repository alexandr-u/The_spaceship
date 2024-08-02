#pragma once
#include <iostream>
#include "SpaceItem.h"
#include "Planet.h"

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

    // прилет на планету Земля и повышение ресурсов до минимума (100)
    void flyToEarth();
        
    // прилет на планету
    void flyToPlanet(int loc);

    //получение ресурсов и вычитание их из планеты
    void gettingResources(Planet& planet);


private:
    int m_food;
};