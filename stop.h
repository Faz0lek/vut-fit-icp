/**
 * @file stop.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Stop header file. This class contains Stop interface.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef STOP_H
#define STOP_H

#include "street.h"

#include <QString>

/**
 * @brief Class desribing stops. Stops are used in the map and buses use them as anchor points.
 * 
 */
class Stop
{
public:
    /**
     * @brief Construct a new Stop object
     * 
     * @param street Street on which the stop lies
     * @param distance Distance as percentage from Street beginning
     */
    Stop(const Street * const street, const int distance);

    /**
     * @brief Default constructor
     * 
     */
    Stop();

    /**
     * @brief Get the Street object the stop lies on
     * 
     * @return const Street* Returns the street the stop lies on
     */
    const Street* getStreet() const;

    /**
     * @brief Get the Distance object
     * 
     * @return int Returns the distance
     */
    int getDistance() const;

    /**
     * @brief This method calculates the actual coordinates of Stop
     * 
     * @return QPointF Returns coordinates of stop
     */
    QPointF getCoordinates() const;

    /**
     * @brief Width of stop sprite
     * 
     */
    constexpr static qreal WIDTH = 14.0;

    /**
     * @brief Height of stop sprite
     * 
     */
    constexpr static qreal HEIGHT = 14.0;

private:
    const Street * const street;
    const int distance;
};

#endif // STOP_H
