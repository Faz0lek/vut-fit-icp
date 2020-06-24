/**
 * @file vehicle.cpp
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Vehicle source file. This file implements all bus behaviour.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "vehicle.h"
#include <QDebug>

Vehicle::Vehicle(BusLine const &r, size_t index) : currentStreet(nullptr),
                                                   schedule(r)
{
    // fill route
    for (const auto &s : r.getRoutes())
    {
        route.append(QPair<const Stop *const, QTime>(s.first, s.second[index]));
    }

    this->points = schedule.getPoints();

    this->nextPointIndex = 1;
    this->nextStopIndex = 1;

    // set stops
    this->prevStop = route[0].first;
    this->nextStop = route[1].first;

    this->prevStopTime = route[0].second;
    this->nextStopTime = route[1].second;

    // set street
    this->currentStreet = route[0].first->getStreet();

    // set destination
    this->destination = &points[1];

    // calculate angle
    this->angle = qRadiansToDegrees(atan2(points[1].y() - points[0].y(), points[1].x() - points[0].x()));

    // set start position relative to the rotation
    const qreal LEN = qSqrt(512) / 2;
    setPos(points.first().x() - (LEN * qCos(qDegreesToRadians(angle + 45))), points.first().y() - (LEN * qSin(qDegreesToRadians(angle + 45))));

    //set rotation
    setRotation(angle);

    // set speed
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

const Stop *Vehicle::getNextStop() const
{
    return this->nextStop;
}

const QTime Vehicle::getPrevStopTime()
{
    return this->prevStopTime;
}

const QTime Vehicle::getNextStopTime()
{
    return this->nextStopTime;
}

const BusLine &Vehicle::getRoute() const
{
    return this->schedule;
}

void Vehicle::setStartedAt(QTime time)
{
    this->started_at = time;
}

const QTime Vehicle::getStartedAt()
{
    return this->started_at;
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
    if (!phase)
        return;

    setPos(mapToParent(speed, 0.0));

    const qreal LEN = qSqrt(512) / 2;
    QRectF dRect = QRectF(destination->x() - 20, destination->y() - 20, 40, 40);
    if (dRect.contains(this->pos()))
    {
        if (*destination == points.last())
        {
            //destroy autobus
            this->hide();
            delete this;
            return;
        }

        if (*destination == nextStop->getCoordinates())
        {
            nextStopIndex++;

            prevStop = nextStop;
            nextStop = route[nextStopIndex].first;
            prevStopTime = nextStopTime;
            nextStopTime = route[nextStopIndex].second;
            this->speed = calculateDistance() / getTimeDiff(route[nextStopIndex - 1].second, route[nextStopIndex].second);
        }

        currentStreet = nextStop->getStreet();

        nextPointIndex++;

        destination = &points[nextPointIndex];
        this->angle = qRadiansToDegrees(atan2(points[nextPointIndex].y() - points[nextPointIndex - 1].y(), points[nextPointIndex].x() - points[nextPointIndex - 1].x()));

        // set start position relative to the rotation
        setPos(points[nextPointIndex - 1].x() - (LEN * qCos(qDegreesToRadians(angle + 45))), points[nextPointIndex - 1].y() - (LEN * qSin(qDegreesToRadians(angle + 45))));

        setRotation(angle);
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

    for (const auto &p : route)
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
