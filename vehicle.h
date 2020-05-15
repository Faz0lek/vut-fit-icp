#ifndef VEHICLE_H
#define VEHICLE_H

#include "street.h"
#include "busline.h"

class Vehicle
{
public:
    Vehicle(BusLine const& r);

    const Street* getCurrentStreet() const;
    const Stop* getPrevStop() const;
    const Stop* getNextStop() const;
    const BusLine& getRoute() const;

private:
    const Street* currentStreet;
    const Stop* prevStop;
    const Stop* nextStop;

    BusLine const& route;
};

#endif // VEHICLE_H
