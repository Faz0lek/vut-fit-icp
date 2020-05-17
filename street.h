/**
 * @file street.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Street header file. This class contains street interface.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef STREET_H
#define STREET_H

#include <QPoint>
#include <QString>
#include <QPair>

/**
 * @brief Class describing Streets. Streets are used in the map.
 * 
 */
class Street
{
public:
    /**
     * @brief Construct a new Street object
     * 
     * @param street_name Name of the street
     * @param x1 x1
     * @param y1 y1
     * @param x2 x2
     * @param y2 y2
     */
    Street(const QString street_name, const int x1, const int y1, const int x2, const int y2);

    /**
     * @brief Default constructor
     * 
     */
    Street();

    /**
     * @brief Get the Beginning of the street
     * 
     * @return QPoint Returns the beginning point of the street
     */
    QPoint getBeginning() const;

    /**
     * @brief Get the End of the street
     * 
     * @return QPoint Returns the end point of the street
     */
    QPoint getEnd() const;

    /**
     * @brief Get the name of the street
     * 
     * @return QString Returns the name of the street
     */
    QString getName() const;

    /**
     * @brief This method calculates the length of the street
     * 
     * @return qreal Returns the length of the street
     */
    qreal getLength() const;

private:
    const QString street_name;
    const QPair<const QPoint, const QPoint> coordinates;
};

#endif // STREET_H
