/**
 * @file vehicle.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Bus header file. This class contains bus interface.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include "street.h"
#include "busline.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtDebug>
#include <QtMath>

/**
 * @brief Class describing buses. Buses are created when a time matches a spawn time and they are destroyed when they reach their final stop.
 * 
 */
class Vehicle : public QGraphicsItem
{
public:
    /**
     * @brief Construct a new Vehicle object
     * 
     * @param r Schedule
     * @param index index
     */
    Vehicle(BusLine const &r, size_t index);

    /**
     * @brief Get the Current Street the bus drives
     * 
     * @return const Street* Returns a pointer to the street
     */
    const Street *getCurrentStreet() const;

    /**
     * @brief Get the previous Stop the bus stopped at
     * 
     * @return const Stop* Returns a pointer to the previous Stop
     */
    const Stop *getPrevStop() const;

    /**
     * @brief Get the next Stop the bus will stop at
     * 
     * @return const Stop* Returns a pointer to the next Stop
     */
    const Stop *getNextStop() const;

    /**
     * @brief Get the previous Stop time the bus stopped at
     *
     * @return const QTime Returns a time of the previous Stop
     */
    const QTime getPrevStopTime();

    /**
     * @brief Get the next Stop time the bus will stop at
     *
     * @return const QTime Returns a time of the next Stop
     */
    const QTime getNextStopTime();

    /**
     * @brief Get the Schedule of a bus
     * 
     * @return const BusLine& Returns the schedule
     */
    const BusLine &getRoute() const;

    /**
     * @brief Get the time when vehicle started
     * 
     * @return const QTime Time to be returned
     */
    const QTime getStartedAt();

    /**
     * @brief Set the time when vehicle started
     * 
     * @param time Time to be set
     */
    void setStartedAt(QTime time);

    /**
     * @brief Width of the bus sprite
     * 
     */
    constexpr static qreal WIDTH = 16.0;

    /**
     * @brief Height of the bus sprite
     * 
     */
    constexpr static qreal HEIGHT = 16.0;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

protected:
    /**
     * @brief This is called on a timer tick, this method move the bus
     * 
     * @param phase phase
     */
    virtual void advance(int phase) override;

private:
    const Street *currentStreet;
    const Stop *prevStop;
    const Stop *nextStop;
    QTime prevStopTime;
    QTime nextStopTime;

    BusLine const &schedule;
    QVector<QPair<const Stop *const, QTime>> route;
    QVector<QPointF> points;

    QPointF *destination;
    int nextPointIndex;
    int nextStopIndex;

    qreal angle;
    qreal speed;

    QTime started_at;

    int getTimeDiff(const QTime first, const QTime second) const;
    qreal calculateDistance() const;
};

#endif // VEHICLE_H
