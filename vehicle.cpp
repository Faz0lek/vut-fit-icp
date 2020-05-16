#include "vehicle.h"
#include <QtDebug>
#include <QtMath>

Vehicle::Vehicle(BusLine const& r, size_t index) :
      currentStreet(nullptr),
      schedule(r)
{
    // fill route
    for (const auto& s : r.getRoutes())
    {
        route.append(QPair<const Stop* const, QTime>(s.first, s.second[index]));
    }

    this->points = schedule.getPoints();

    // set stops
    this->prevStop = route[0].first;
    this->nextStop = route[1].first;

    // set street
    this->currentStreet = route[0].first->getStreet();

    // set destination
    this->destination = &points[1];

    // set rotation
    this->angle = qRadiansToDegrees(atan2(points[1].y() - points[0].y(), points[1].x() - points[0].x())) + 90;
    setRotation(angle);

    // set start position
    setPos(points.first().x(), points.first().y());

    // set speed
    this->speed = QLineF(points[0], points[1]).length() / getTimeDiff(route[0].second, route[1].second);

    this->pointIndex = 1;
    this->stopIndex = 0;
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
    (void)option;
    (void)widget;

    QRectF r = this->boundingRect();
    QBrush b(Qt::blue);

    painter->fillRect(r, b);
    painter->drawRect(r);
}

void Vehicle::advance(int phase)
{
    if (!phase) return;

    setPos(mapToParent(0, -(speed)));

    qreal tmp = speed * 0.5;
    QRectF dRect = QRectF(destination->x() - tmp, destination->y() - tmp, speed + 1, speed + 1);

    if (dRect.contains(this->pos()))
    {
        if (*destination == points.last())
        {
            //destroy autobus
            qDebug() << "DESTROYING BUS BRRRRRR";
            return;
        }

        if (*destination == nextStop->getCoordinates())
        {
            qDebug() << "NEXT STOP REACHED";
            prevStop = nextStop;
            nextStop = route[stopIndex + 1].first;
            this->speed = QLineF(points[pointIndex - 1], points[pointIndex]).length() / getTimeDiff(route[stopIndex].second, route[stopIndex + 1].second);
            stopIndex++;
        }

        currentStreet = nextStop->getStreet();

        pointIndex++;
        destination = &points[pointIndex];

        this->angle = qRadiansToDegrees(atan2(points[pointIndex].y() - points[pointIndex - 1].y(), points[pointIndex].x() - points[pointIndex - 1].x())) + 90;
        setRotation(angle);
        setPos(points[pointIndex - 1].x(), points[pointIndex - 1].y());
    }
}

int Vehicle::getTimeDiff(const QTime first, const QTime second) const
{
    if (first.hour() == second.hour())
    {
        return second.minute() - first.minute();
    }
    else
    {
        if (first.hour() > second.hour())
        {
            return 60 * (24 - first.hour() + second.hour()) - first.minute() + second.minute();
        }
        else
        {
            return 60 * (second.hour() - first.hour()) - first.minute() + second.minute();
        }
    }
}
