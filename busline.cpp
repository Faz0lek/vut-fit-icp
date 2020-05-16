#include "busline.h"

BusLine::BusLine(QVector<QPair<const Stop* const, QVector<QTime>>> routes)
    : routes(routes)
{
    calculatePoints();
}

BusLine::BusLine()
{}

QVector<QPair<const Stop * const, QVector<QTime> > > BusLine::getRoutes() const
{
    return this->routes;
}

QVector<QPointF> BusLine::getPoints() const
{
    return this->points;
}

void BusLine::calculatePoints()
{
    points.push_back(routes[0].first->getCoordinates());

    for (int i = 0; i < routes.length() - 1; i++)
    {
        if (routes[i].first->getStreet() == routes[i + 1].first->getStreet()) // stops on the same street
        {
            points.push_back(routes[i + 1].first->getCoordinates());
            continue;
        }
        else // middle point
        {
            if (routes[i].first->getStreet()->getBeginning() == routes[i + 1].first->getStreet()->getBeginning() || routes[i].first->getStreet()->getBeginning() == routes[i + 1].first->getStreet()->getEnd())
            {
                points.push_back(routes[i].first->getStreet()->getBeginning());
            }
            else if (routes[i].first->getStreet()->getEnd() == routes[i + 1].first->getStreet()->getBeginning() || routes[i].first->getStreet()->getEnd() == routes[i + 1].first->getStreet()->getEnd())
            {
                points.push_back(routes[i].first->getStreet()->getEnd());
            }

            points.push_back(routes[i + 1].first->getCoordinates());
        }
    }
}
