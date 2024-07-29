#include "SpaceItem.h"

extern int zeroIfNegative(int& value);

int SpaceItem::getResources() const { return m_resources; }
int SpaceItem::getFuel() const { return m_fuel; }
int SpaceItem::getProtection() const { return m_protection; }

void SpaceItem::setResources(int velueResources) { m_resources = zeroIfNegative(velueResources); }
void SpaceItem::setFuel(int velueFuel) { m_fuel = zeroIfNegative(velueFuel); }
void SpaceItem::setProtection(int velueProtection) { m_protection = zeroIfNegative(velueProtection); }

void SpaceItem::addResources(int velueResources) { m_resources += zeroIfNegative(velueResources); }
void SpaceItem::addFuel(int velueFuel) { m_fuel += zeroIfNegative(velueFuel); }
void SpaceItem::addProtection(int velueProtection) { m_protection += zeroIfNegative(velueProtection); }