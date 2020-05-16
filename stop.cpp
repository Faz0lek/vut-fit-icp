#include "stop.h"
#include <QtMath>

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

QPointF Stop::getCoordinates() const
{
    qreal a = 0.0,
          dx = 0.0,
          dy = 0.0,
          x = 0.0,
          y = 0.0;

    dx = qAbs(this->street->getBeginning().x() - this->street->getEnd().x());
    dy = qAbs(this->street->getBeginning().y() - this->street->getEnd().y());

    x = this->street->getBeginning().x() - (WIDTH * 0.5);
    y = this->street->getBeginning().y() - (HEIGHT * 0.5);

    if (dx == 0) // vertical street
    {
        if (this->street->getBeginning().y() > this->street->getEnd().y())
            y -= this->distance;
        else
            y += this->distance;
    }
    else if (dy == 0) // horizontal street
    {
        if (this->street->getBeginning().x() > this->street->getEnd().x())
            x -= this->distance;
        else
            x += this->distance;
    }
    else // diagonal street
    {
        a = qAtan(dy / dx);
        x += qCos(a);
        y += qSin(a);
    }

    return QPointF(x, y);
}
