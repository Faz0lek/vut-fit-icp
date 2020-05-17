#ifndef BUSLINE_H
#define BUSLINE_H

#include <QVector>
#include <QPair>
#include <QString>
#include <QTime>
#include "stop.h"

class BusLine
{
public:
    BusLine(QVector<QPair<const Stop* const, QVector<QTime>>> routes);
    BusLine();

    QVector<QPair<const Stop* const, QVector<QTime>>> getRoutes() const;

    QVector<QPointF> getPoints() const;

private:
    QVector<QPair<const Stop* const, QVector<QTime>>> routes;

    void calculatePoints();
    QVector<QPointF> points;
};

#endif // BUSLINE_H
