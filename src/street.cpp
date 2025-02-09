/**
 * @file street.cpp
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Street source file. This file implements the Street behaviour.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "street.h"

Street::Street(const QString street_name, const int x1, const int y1, const int x2, const int y2)
    : street_name(street_name), coordinates(QPair<QPoint, QPoint>(QPoint(x1, y1), QPoint(x2, y2)))
{
}

Street::Street()
    : street_name(QString("")), coordinates(QPair<QPoint, QPoint>(QPoint(-1, -1), QPoint(-1, -1)))
{
}

QPoint Street::getBeginning() const
{
    return this->coordinates.first;
}

QPoint Street::getEnd() const
{
    return this->coordinates.second;
}

QString Street::getName() const
{
    return this->street_name;
}

qreal Street::getLength() const
{
    return qSqrt(qPow(qAbs(getBeginning().x() - getEnd().x()), 2) + qPow(qAbs(getBeginning().y() - getEnd().y()), 2));
}
