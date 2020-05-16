#include "vehicle.h"
#include <QtDebug>
#include <QtMath>


Vehicle::Vehicle(BusLine const& r, size_t index, qreal a, qreal s) :
      currentStreet(nullptr),
      schedule(r),
      angle(a),
      speed(s)
{
    // fill route
    for (const auto& s : r.getRoutes())
    {
        route.append(QPair<const Stop* const, QTime>(s.first, s.second[index]));
    }

    // set stops
    this->prevStop = route[0].first;
    this->nextStop = route[1].first;

    // set street
    this->currentStreet = route[0].first->getStreet();

    // set rotation TODO: calculate correct angle for next stop (ORIENTATION MATTERS)
    const qreal dx = qAbs(this->currentStreet->getBeginning().x() - this->currentStreet->getEnd().x());
    const qreal dy = qAbs(this->currentStreet->getBeginning().y() - this->currentStreet->getEnd().y());

    if (dx == 0) // vertical street
    {

    }
    else if (dy == 0) // horizontal street
    {

    }
    else // diagonal street
    {
        this->angle = qAtan(dy / dx);
    }
    setRotation(angle);

    // set start position
    const QPointF p = route[0].first->getCoordinates();
    setPos(p.x() + (WIDTH * 0.5) + 7.0, p.y() - 1.0);

    // set speed
    speed = 5;
}

const Street *Vehicle::getCurrentStreet() const
{
    return this->currentStreet;
}

const Stop *Vehicle::getPrevStop() const
{
    return this->prevStop;
}

const Stop* Vehicle::getNextStop() const
{
    return this->nextStop;
}

const BusLine& Vehicle::getRoute() const
{
    return this->schedule;
}

QRectF Vehicle::boundingRect() const
{
    return QRectF(0.0, 0.0, 16.0, 16.0);
}

void Vehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF r = this->boundingRect();
    QBrush b(Qt::blue);

    painter->fillRect(r, b);
    painter->drawRect(r);
}

void Vehicle::move(int phase)
{
    if (!phase) return;

    QPointF location = this->pos();
    setPos(mapToParent(0, -(speed)));
}

