#include "stop.h"

Stop::Stop(const Street * const street, const int distance)
    : street(street)
    , distance(distance)
{}

Stop::Stop()
    : street(nullptr)
    , distance(-1)
{}

const Street* Stop::getStreet() const
{
    return this->street;
}

int Stop::getDistance() const
{
    return this->distance;
}
