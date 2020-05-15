#include "street.h"

Street::Street(const QString street_name, const int x1, const int y1, const int x2, const int y2)
    : street_name(street_name)
    , coordinates(QPair<QPoint, QPoint>(QPoint(x1, y1), QPoint(x2, y2)))
{}

Street::Street()
    : street_name(QString(""))
    , coordinates(QPair<QPoint, QPoint>(QPoint(-1, -1), QPoint(-1, -1)))
{}

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
