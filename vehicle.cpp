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

    // set rotation
    setAngle();
    setRotation(angle);

    // set start position
    const QPointF p = route[0].first->getCoordinates();
    setPos(p.x() - 1.0, p.y() - 1.0);

    // set speed
    setSpeed();
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

    qDebug() << "MOVE IT MOVE IT";

    QPointF location = this->pos();
    (void)location;
    setPos(mapToParent(0, -(speed)));
}

void Vehicle::setAngle()
{
    if (this->nextStop == Q_NULLPTR) return;

    const qreal dx = this->currentStreet->getBeginning().x() - this->currentStreet->getEnd().x();
    const qreal dy = this->currentStreet->getBeginning().y() - this->currentStreet->getEnd().y();

    if (dx == 0.0) // vertical street
    {

        if (dy > 0.0) // street is bottom-up
        {
            if (nextStop->getStreet()->getBeginning() == prevStop->getStreet()->getEnd() || nextStop->getStreet()->getEnd() == prevStop->getStreet()->getEnd())
            {
                angle = ANGLE_UP;
            }
            else
            {
                angle = ANGLE_DOWN;
            }
        }
        else // street is top-down
        {
            if (nextStop->getStreet()->getBeginning() == prevStop->getStreet()->getBeginning() || nextStop->getStreet()->getEnd() == prevStop->getStreet()->getBeginning())
            {
                angle = ANGLE_UP;
            }
            else
            {
                angle = ANGLE_DOWN;
            }
        }
    }
    else if (dy == 0.0) // horizontal street
    {
        if (dx > 0.0) // street is right-left
        {
            if (nextStop->getStreet()->getBeginning() == prevStop->getStreet()->getEnd() || nextStop->getStreet()->getEnd() == prevStop->getStreet()->getEnd())
            {
                angle = ANGLE_LEFT;
            }
            else
            {
                angle = ANGLE_RIGHT;
            }
        }
        else // street is left-right
        {
            if (nextStop->getStreet()->getBeginning() == prevStop->getStreet()->getBeginning() || nextStop->getStreet()->getEnd() == prevStop->getStreet()->getBeginning())
            {
                angle = ANGLE_LEFT;
            }
            else
            {
                angle = ANGLE_RIGHT;
            }
        }
    }
    else // diagonal street
    {
        this->angle = qAtan(qAbs(dy) / qAbs(dx)) - 90.0;
    }
}

void Vehicle::setSpeed()
{
    if (this->nextStop == Q_NULLPTR) return;

    const qreal dx = this->currentStreet->getBeginning().x() - this->currentStreet->getEnd().x();
    const qreal dy = this->currentStreet->getBeginning().y() - this->currentStreet->getEnd().y();

    QPoint endingPoint;
    qreal distance = 0.0;

    int dt = 0;
    int i = 0;
    for (const auto& s : this->route)
    {
        if (s.first == this->prevStop)
        {
            if (route[i + 1].second.hour() == s.second.hour())
            {
                dt = route[i + 1].second.minute() - s.second.minute();
            }
            else
            {
                dt = (route[i + 1].second.hour() - s.second.hour()) * 60 - s.second.minute() + 60;
            }
            break;
        }
        i++;
    }

    // next stop is on the same street
    if (this->currentStreet == nextStop->getStreet())
    {
        distance = qSqrt(qPow(qAbs(this->x() - nextStop->getCoordinates().x()), 2.0) + qPow(qAbs(this->y() - nextStop->getCoordinates().y()), 2.0));

        speed = distance / dt;
        qDebug() << distance << dt;
        return;
    }

    // find end of current street
    if (dx == 0.0) // vertical street
    {
        if (dy > 0.0) // street is bottom-up
        {
            if (angle == ANGLE_UP)
            {
                endingPoint = prevStop->getStreet()->getEnd();
            }
            else if (angle == ANGLE_DOWN)
            {
                endingPoint = prevStop->getStreet()->getBeginning();
            }
        }
        else // street is top-down
        {
            if (angle == ANGLE_UP)
            {
                endingPoint = prevStop->getStreet()->getBeginning();
            }
            else if (angle == ANGLE_DOWN)
            {
                endingPoint = prevStop->getStreet()->getEnd();
            }
        }
    }
    else if (dy == 0.0) // horizontal street
    {
        if (dx > 0.0) // street is right-left
        {
            if (angle == ANGLE_RIGHT)
            {
                endingPoint = prevStop->getStreet()->getBeginning();
            }
            else if (angle == ANGLE_LEFT)
            {
                endingPoint = prevStop->getStreet()->getEnd();
            }
        }
        else // street is left-right
        {
            if (angle == ANGLE_RIGHT)
            {
                endingPoint = prevStop->getStreet()->getEnd();
            }
            else if (angle == ANGLE_LEFT)
            {
                endingPoint = prevStop->getStreet()->getBeginning();
            }
        }
    }
    else // diagonal street
    {
        if (dx > 0.0)
        {
            if (dy > 0.0) //++
            {
                if (angle > ANGLE_RIGHT && angle < ANGLE_DOWN)
                {
                    endingPoint = prevStop->getStreet()->getBeginning();
                }
                else if (angle > ANGLE_LEFT)
                {
                    endingPoint = prevStop->getStreet()->getEnd();
                }
            }
            else //+-
            {
                if (angle > ANGLE_UP && angle < ANGLE_RIGHT)
                {
                    endingPoint = prevStop->getStreet()->getBeginning();
                }
                else if (angle > ANGLE_DOWN && angle < ANGLE_LEFT)
                {
                    endingPoint = prevStop->getStreet()->getEnd();
                }
            }
        }
        else // dx < 0.0
        {
            if (dy > 0.0) //-+
            {
                if (angle > ANGLE_UP && angle < ANGLE_RIGHT)
                {
                    endingPoint = prevStop->getStreet()->getEnd();
                }
                else if (angle > ANGLE_DOWN && angle < ANGLE_LEFT)
                {
                    endingPoint = prevStop->getStreet()->getBeginning();
                }
            }
            else //--
            {
                if (angle > ANGLE_RIGHT && angle < ANGLE_DOWN)
                {
                    endingPoint = prevStop->getStreet()->getEnd();
                }
                else if (angle > ANGLE_LEFT)
                {
                    endingPoint = prevStop->getStreet()->getBeginning();
                }
            }
        }
    }

    distance = qSqrt(qPow(qAbs(this->x() - endingPoint.x()), 2) + qPow(qAbs(this->y() - endingPoint.y()), 2)) + qSqrt(qPow(qAbs(endingPoint.x() - nextStop->getCoordinates().x()), 2) + qPow(qAbs(endingPoint.y() - nextStop->getCoordinates().y()), 2));
    speed = distance / dt;
    qDebug() << distance << dt;
}

