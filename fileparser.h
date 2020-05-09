#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream>
#include <QFile>
#include <QTextStream>
#include "street.h"
#include "route.h"
#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>


class FileParser
{
public:
    FileParser();
    QVector<Street> ParseStreet(const QString filename);
//    QMap<> ParseRoute(const QString filename);
};

#endif // FILEPARSER_H
