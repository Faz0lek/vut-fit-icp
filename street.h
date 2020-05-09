#ifndef STREET_H
#define STREET_H

#include <utility>
#include <QPoint>


class Street
{
public:
    Street();

private:
    std::pair<QPoint, QPoint> coordinates;
};

#endif // STREET_H
