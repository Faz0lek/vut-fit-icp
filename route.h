#ifndef ROUTE_H
#define ROUTE_H

#include <QVector>
#include <QPair>
#include <QString>
#include "stop.h"

class Route
{
public:
//    Route();
    Route();

private:
    QVector<QPair<Stop, int>> stops;
};

#endif // ROUTE_H
