#pragma once
#include <iostream>
#include <string>
#include "Shop.h"
class Planet
{
public:
    friend std::istream& operator>>(std::istream& is, Planet& item); //перегрузка метода ввода для планеты
    friend std::ostream& operator<<(std::ostream& os, Planet& item); //перегрузка метода вывода для планеты

    Planet();
    Planet(const Planet& over) = default;
    ~Planet() = default;


    int getLocation() const { return location; }
    int getResources() const { return resources; }

    void removeResources(int value);

    Shop shop;
private:
    //название, положение, ресурсы, магазин
    std::string label;
    int location;
    int resources;
};
