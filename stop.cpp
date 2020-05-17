/**
 * @file stop.cpp
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Stop source file. This file implements Stop behaviour.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "stop.h"

Stop::Stop(const Street *const street, const int distance)
    : street(street), distance(distance)
{
}

Stop::Stop()
    : street(nullptr), distance(-1)
{
}

const Street *Stop::getStreet() const
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

    dx = this->street->getBeginning().x() - this->street->getEnd().x();
    dy = this->street->getBeginning().y() - this->street->getEnd().y();

    x = this->street->getBeginning().x();
    y = this->street->getBeginning().y();

    const qreal streetLen = this->street->getLength() * 0.01;

    if (dx == 0) // vertical street
    {
        if (this->street->getBeginning().y() > this->street->getEnd().y())
            y -= this->distance * streetLen;
        else
            y += this->distance * streetLen;
    }
    else if (dy == 0) // horizontal street
    {
        if (this->street->getBeginning().x() > this->street->getEnd().x())
            x -= this->distance * streetLen;
        else
            x += this->distance * streetLen;
    }
    else // diagonal street
    {
        a = qAtan(dy / dx);
        x += qCos(a) * this->distance * streetLen;
        y += qSin(a) * this->distance * streetLen;
    }

    return QPointF(x, y);
}
