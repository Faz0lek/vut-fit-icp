#ifndef ROUTE_H
#define ROUTE_H

#include <QVector>
#include <QPair>
#include <QString>
#include "stop.h"

class Route
{
public:
    Route(QVector<QPair<Stop, int>> route);
    Route();

private:
    QVector<QPair<Stop, int>> route;
};

#endif // ROUTE_H
