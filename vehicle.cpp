#include "vehicle.h"

Vehicle::Vehicle(BusLine const& r)
    : currentStreet(nullptr)
    , route(r)
{}

const Street *Vehicle::getCurrentStreet() const
{
    return this->currentStreet;
}

const Stop *Vehicle::getPrevStop() const
{
    return this->prevStop;
}

const Stop* Vehicle::getNextStop() const
{
    return this->nextStop;
}

const BusLine& Vehicle::getRoute() const
{
    return this->route;
}

