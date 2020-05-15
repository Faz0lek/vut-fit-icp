#include "vehicle.h"

Vehicle::Vehicle()
    : currentStreet(nullptr)
    , route(nullptr)
{}

Vehicle::Vehicle(BusLine* const r)
    : currentStreet(nullptr)
    , route(r)
{}

Vehicle::Vehicle(Street* const s, BusLine* const r)
    : currentStreet(s)
    , route(r)
{}
