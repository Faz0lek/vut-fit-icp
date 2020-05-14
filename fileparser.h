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
#include "route.h"

class FileParser
{
public:
    FileParser();
    QVector<Street> ParseStreet(const QString street_filename);
    QMap<int, Route> ParseLine(const QString line_filename);
};

#endif // FILEPARSER_H
