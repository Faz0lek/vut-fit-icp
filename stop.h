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

    QPointF getCoordinates() const;

    constexpr static qreal WIDTH = 14.0;
    constexpr static qreal HEIGHT = 14.0;

private:
    const Street * const street;
    const int distance;
};

#endif // STOP_H
