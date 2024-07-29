#pragma once

class SpaceItem
{
public:

    SpaceItem() = default;
    SpaceItem(int velueResources, int velueFuel, int velueProtection) :
        m_resources(velueResources),
        m_fuel(velueFuel),
        m_protection(velueProtection)
    {};
    virtual ~SpaceItem() = default;

    int getResources() const;
    int getFuel() const;
    int getProtection() const;

    void setResources(int velueResources);
    void setFuel(int velueFuel);
    void setProtection(int velueProtection);

    void addResources(int velueResources);
    void addFuel(int velueFuel);
    void addProtection(int velueProtection);

protected:
    int m_resources;
    int m_fuel;
    int m_protection;
};
