#ifndef ROUTE_H
#define ROUTE_H

#include <QVector>
#include <QString>

class Route
{
public:
    Route();

private:
    QVector<QString> streets;
};

#endif // ROUTE_H
