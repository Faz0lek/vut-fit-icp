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

    this->nextPointIndex = 1;
    this->nextStopIndex = 1;

    // set stops
    this->prevStop = route[0].first;
    this->nextStop = route[1].first;

    // set street
    this->currentStreet = route[0].first->getStreet();

    // set destination
    this->destination = &points[1];

    // set start position
    setPos(points.first().x() + 8, points.first().y() + 8);
    qDebug() << points.first() << this->pos();

    this->setTransformOriginPoint(8, 8);

    // set rotation
    this->angle = qRadiansToDegrees(atan2(points[1].y() - points[0].y(), points[1].x() - points[0].x())) + 90;
    setRotation(angle);

    this->setTransformOriginPoint(0, 0);

    // set speed
    //this->speed = QLineF(points[0], points[1]).length() / getTimeDiff(route[0].second, route[1].second);
    this->speed = calculateDistance() / getTimeDiff(route[0].second, route[1].second);
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
    QRectF dRect = QRectF(destination->x() - 20, destination->y() - 20, 40, 40);

    if (dRect.contains(this->pos()))
    {
        if (*destination == points.last())
        {
            //destroy autobus
            qDebug() << "DESTROYING BUS BRRRRRR";
            this->hide();
            delete this;
            return;
        }

        if (*destination == nextStop->getCoordinates())
        {
            qDebug() << "NEXT STOP REACHED";
            nextStopIndex++;

            prevStop = nextStop;
            nextStop = route[nextStopIndex].first;
            //this->speed = QLineF(points[nextPointIndex - 1], points[nextPointIndex]).length() / getTimeDiff(route[nextStopIndex].second, route[nextStopIndex + 1].second);
            this->speed = calculateDistance() / getTimeDiff(route[nextStopIndex - 1].second, route[nextStopIndex].second);
        }

        currentStreet = nextStop->getStreet();

        nextPointIndex++;

        destination = &points[nextPointIndex];

        this->angle = qRadiansToDegrees(atan2(points[nextPointIndex].y() - points[nextPointIndex - 1].y(), points[nextPointIndex].x() - points[nextPointIndex - 1].x())) + 90;
        setTransformOriginPoint(8, 8);
        setRotation(angle);
        setTransformOriginPoint(0, 0);

        setPos(points[nextPointIndex - 1].x() + 8, points[nextPointIndex - 1].y() + 8);
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

qreal Vehicle::calculateDistance() const
{
    qreal d = 0.0;
    bool isStop = false;

    d = QLineF(points[nextPointIndex - 1], points[nextPointIndex]).length();

    for (const auto& p : route)
    {
        if (*destination == p.first->getCoordinates())
        {
            isStop = true;
            break;
        }
    }

    if (isStop)
    {
        return d;
    }
    else
    {
        return d + QLineF(points[nextPointIndex], points[nextPointIndex + 1]).length();
    }
}
