/**
 * @file fileparser.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Fileparser header file. This class creates fileparser interface.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>
#include "street.h"
#include "stop.h"
#include "busline.h"

/**
 * @brief Class describing FileParser. FileParser is used to read street and busline information from files.
 * 
 */
class FileParser
{
public:
    /**
     * @brief Destroy the File Parser object
     * 
     */
    ~FileParser();

    /**
     * @brief Construct a new File Parser object
     * 
     */
    FileParser();

    /**
     * @brief This method parses the file containing streets
     * 
     * @param street_filename Name of the file containing streets
     * @return QVector<Street> Returns parsed streets
     */
    QVector<Street> ParseStreet(const QString street_filename);

    /**
     * @brief This method parses the file containing stops and buslines
     * 
     * @param line_filename Name of the file containing the data
     * @param streets All the streets from previously parsed file
     * @return QMap<int, BusLine> Returns parsed data
     */
    QMap<int, BusLine> ParseLine(const QString line_filename, QVector<Street> *streets);

    /**
     * @brief Get the unique Stops object
     * 
     * @return QVector<Stop*> 
     */
    QVector<Stop*> getStops() const;

private:
    QVector<Stop*> stops;
    QVector<Stop*> unique_stops;
};

#endif // FILEPARSER_H
