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

class FileParser
{
public:
    ~FileParser();
    FileParser();
    QVector<Street> ParseStreet(const QString street_filename);
    QMap<int, BusLine> ParseLine(const QString line_filename, QVector<Street> *streets);

    QVector<Stop> getStops() const;

private:
    QVector<Stop*> stops;
};

#endif // FILEPARSER_H
