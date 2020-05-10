#include "vehicle.h"

Vehicle::Vehicle() : currentStreet(nullptr), route(nullptr)  {}

Vehicle::Vehicle(Street* const s, Route* const r) : currentStreet(s), route(r) {}
