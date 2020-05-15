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

private:
    QVector<QPair<const Stop* const, QVector<QTime>>> routes;
};

#endif // BUSLINE_H
