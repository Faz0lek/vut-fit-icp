#ifndef STOP_H
#define STOP_H

#include "street.h"

#include <QString>

class Stop
{
public:
    Stop(const Street * const street, const int distance);
    Stop();

    const Street* getStreet() const;
    int getDistance() const;

private:
    const Street * const street;
    const int distance;
};

#endif // STOP_H
