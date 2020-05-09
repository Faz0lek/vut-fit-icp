/**
 * @file fileparser.cpp
 * @author Adam Gajda (xgajda07@stud.fit.vutbr.cz)
 * @brief Implementation of parser which parses files into desired data structures.
 * @version 0.1
 * @date 2020-05-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "fileparser.h"

FileParser::FileParser()
{


}

/**
 * @brief Method for parsing CVS files containing streets and their coordinates.
 * 
 * @param filename Name of file to be parsed.
 * @return QVector<Street> Vector of streets.
 */
QVector<Street> ParseStreet(const QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly))
    {
        std::cerr << "Failed opening file with provided filename." << endl;
        return;
    }

    QTextStream text(&file);
    QVector<Street> vector;
    QString line;
    QStringList str_list;
    int x1, y1, x2, y2;
    bool ok = true;

    while (text.readLineInto(&line)) {
        str_list = line.split(',', QString::KeepEmptyParts);

        if (str_list.length() != 5)
        {
            std::cerr << "Incorrect ammount of values, expected ammount is 5." << endl;
            return;
        }


        x1 = str_list.at(1).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(1).toStdString() << ", expected type is integer." << endl;
            return;
        }
        y1 = str_list.at(2).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(2).toStdString() << ", expected type is integer." << endl;
            return;
        }
        x2 = str_list.at(3).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(3).toStdString() << ", expected type is integer." << endl;
            return;
        }
        y2 = str_list.at(4).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(4).toStdString() << ", expected type is integer." << endl;
            return;
        }

        Street tmp_street = Street(str_list.at(0), x1, y1, x2, y2);
        vector.append(tmp_street);
    }

    file.close();
}
