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
    QVector<Street> ParseStreet(const QString streetfilename);
    QMap<int, QVector<Route>> ParseRoute(const QString stopfilename, const QString routefilename, const QString linefilename);
};

#endif // FILEPARSER_H
