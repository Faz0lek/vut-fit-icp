/**
 * @file busline.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Busline header file
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef BUSLINE_H
#define BUSLINE_H

#include <QVector>
#include <QPair>
#include <QString>
#include <QTime>
#include "stop.h"

/**
 * @brief Class describing buslines, their interface and behaviour. Busline is a schedule, a set of stops with respective times.
 * 
 */
class BusLine
{
public:

    /**
     * @brief Construct a new Bus Line object
     * 
     * @param routes Schedule, is always passed from fileparser.
     */
    BusLine(QVector<QPair<const Stop* const, QVector<QTime>>> routes);

    /**
     * @brief Default constructor
     * 
     */
    BusLine();

    /**
     * @brief Get the Routes object
     * 
     * @return QVector<QPair<const Stop* const, QVector<QTime>>> Schedule of the Busline
     */
    QVector<QPair<const Stop* const, QVector<QTime>>> getRoutes() const;

    /**
     * @brief Get the Points object
     * 
     * @return QVector<QPointF> All points in the route
     */
    QVector<QPointF> getPoints() const;

private:
    QVector<QPair<const Stop* const, QVector<QTime>>> routes;

    void calculatePoints();
    QVector<QPointF> points;
};

#endif // BUSLINE_H
