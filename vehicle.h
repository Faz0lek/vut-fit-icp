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

    constexpr static qreal WIDTH = 16.0;
    constexpr static qreal HEIGHT = 16.0;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

protected:
    virtual void advance(int phase) override;

private:
    const Street* currentStreet;
    const Stop* prevStop;
    const Stop* nextStop;

    BusLine const& schedule;

    QVector<QPair<const Stop* const, QTime>> route;

    qreal angle;
    qreal speed;

    void setAngle();
    void setSpeed();

    constexpr static qreal ANGLE_UP = 0.0;
    constexpr static qreal ANGLE_RIGHT = 90.0;
    constexpr static qreal ANGLE_DOWN = 180.0;
    constexpr static qreal ANGLE_LEFT = 270.0;
};

#endif // VEHICLE_H
