#ifndef STREET_H
#define STREET_H

#include <QPoint>
#include <QString>
#include <QPair>


class Street
{
public:
    Street(QString street_name, int x1, int y1, int x2, int y2);

private:
    QPair<QPoint, QPoint> coordinates;
    QString street_name;
};

#endif // STREET_H
