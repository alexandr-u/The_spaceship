#pragma once
#include <iostream>
#include "SpaceItem.h"

class Enemy : public SpaceItem
{
public:
    friend std::ostream& operator<<(std::ostream& os, Enemy& item);

    Enemy() : SpaceItem::SpaceItem(0, 0, 0) {};
    Enemy(int resourcesValue, int fuelValue, int protectionValue) :
        SpaceItem::SpaceItem(resourcesValue, fuelValue, protectionValue) {};
    ~Enemy() = default;

    Enemy(const Enemy& over) = default;
    void operator () (int resourcesValue, int fuelValue, int protectionValue); //вносить данные через скобочки
    
};