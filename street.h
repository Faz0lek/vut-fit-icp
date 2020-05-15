#ifndef STREET_H
#define STREET_H

#include <QPoint>
#include <QString>
#include <QPair>


class Street
{
public:
    Street(const QString street_name, const int x1, const int y1, const int x2, const int y2);
    Street();

    QPoint getBeginning() const;
    QPoint getEnd() const;
    QString getName() const;

private:
    const QString street_name;
    const QPair<const QPoint, const QPoint> coordinates;
};

#endif // STREET_H
