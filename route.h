#ifndef ROUTE_H
#define ROUTE_H

#include <QVector>
#include <QPair>
#include <QString>
#include <QTime>
#include "stop.h"

class Route
{
public:
    Route(QVector<QPair<Stop, QVector<QTime>>> routes);
    Route();

private:
    QVector<QPair<Stop, QVector<QTime>>> routes;
};

#endif // ROUTE_H
