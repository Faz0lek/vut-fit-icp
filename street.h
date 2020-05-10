#ifndef STREET_H
#define STREET_H

#include <QPoint>
#include <QString>
#include <QPair>


class Street
{
public:
    Street(QString street_name, int x1, int y1, int x2, int y2);
    Street();
private:
    QString street_name;
    QPair<QPoint, QPoint> coordinates;
};

#endif // STREET_H
