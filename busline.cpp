#include "busline.h"

BusLine::BusLine(QVector<QPair<const Stop* const, QVector<QTime>>> routes)
    : routes(routes)
{}

BusLine::BusLine()
{}
