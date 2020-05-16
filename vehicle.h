#ifndef VEHICLE_H
#define VEHICLE_H

#include "street.h"
#include "busline.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Vehicle : public QGraphicsItem
{
public:
    Vehicle(BusLine const& r, size_t index, qreal a = 0.0, qreal s = 0.0);

    const Street* getCurrentStreet() const;
    const Stop* getPrevStop() const;
    const Stop* getNextStop() const;
    const BusLine& getRoute() const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    constexpr static qreal WIDTH = 16.0;
    constexpr static qreal HEIGHT = 16.0;

protected:
    void move(int phase);

private:
    const Street* currentStreet;
    const Stop* prevStop;
    const Stop* nextStop;

    BusLine const& schedule;

    QVector<QPair<const Stop* const, QTime>> route;

    qreal angle;
    qreal speed;
};

#endif // VEHICLE_H
