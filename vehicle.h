#ifndef VEHICLE_H
#define VEHICLE_H

#include "street.h"
#include "route.h"

class Vehicle
{
public:
    Vehicle();
    Vehicle(Route* const r);
    Vehicle(Street* const s, Route* const r);

private:
    Street* currentStreet;
    Route* route;
};

#endif // VEHICLE_H
