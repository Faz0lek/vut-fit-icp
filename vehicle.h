#ifndef VEHICLE_H
#define VEHICLE_H

#include "street.h"
#include "busline.h"

class Vehicle
{
public:
    Vehicle();
    Vehicle(BusLine* const r);
    Vehicle(Street* const s, BusLine* const r);

private:
    Street* currentStreet;
    BusLine* route;
};

#endif // VEHICLE_H
