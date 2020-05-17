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
    Vehicle(BusLine const& r, size_t index);

    const Street* getCurrentStreet() const;
    const Stop* getPrevStop() const;
    const Stop* getNextStop() const;
    const BusLine& getRoute() const;
    const QTime getStartedAt();

    void setStartedAt(QTime time);

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
    QVector<QPointF> points;

    QPointF* destination;
    int nextPointIndex;
    int nextStopIndex;

    qreal angle;
    qreal speed;

    QTime started_at;

    int getTimeDiff(const QTime first, const QTime second) const;
    qreal calculateDistance() const;
};

#endif // VEHICLE_H
