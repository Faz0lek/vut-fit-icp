#ifndef LINE_H
#define LINE_H

#include <QVector>
#include "route.h"

class Line
{
public:
//    Line();
    Line();
private:
    int line_number;
    QVector<Route> routes;
};

#endif // LINE_H
