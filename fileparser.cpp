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
 * @param streetfilename Name of file to be parsed.
 * @return QVector<Street> Vector of streets.
 */
QVector<Street> FileParser::ParseStreet(const QString street_filename)
{
    QVector<Street> vector;

    QFile file(street_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed opening file with provided street filename.\n";
        return vector;
    }

    QTextStream text(&file);

    QString tmp_line;
    QStringList str_list;
    int x1, y1, x2, y2;
    bool ok = true;

    while (text.readLineInto(&tmp_line))
    {
        str_list = tmp_line.split(',', QString::SkipEmptyParts);
        if (str_list.length() != 5)
        {
            std::cerr << "Incorrect amount of values, expected amount is 5.\n";
            return vector;
        }

        x1 = str_list.at(1).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(1).toStdString() << ", expected type is integer.\n";
            return vector;
        }
        y1 = str_list.at(2).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(2).toStdString() << ", expected type is integer.\n";
            return vector;
        }
        x2 = str_list.at(3).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(3).toStdString() << ", expected type is integer.\n";
            return vector;
        }
        y2 = str_list.at(4).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << str_list.at(4).toStdString() << ", expected type is integer.\n";
            return vector;
        }

        Street tmp_street = Street(str_list.at(0), x1, y1, x2, y2);
        vector.append(tmp_street);
    }

    file.close();
    return vector;
}

QMap<int, Route> FileParser::ParseLine(const QString line_filename)
{
    QMap<int, Route> bus_lines;

    QFile file(line_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed opening file with provided line filename.\n";
        return bus_lines;
    }

    QString tmp_line;
    QStringList line_list, str_list;
    QVector<QTime> tmp_times;
    QVector<QPair<Stop, QVector<QTime>>> routes;
    bool ok = true;

    QTextStream text(&file);
    while (text.readLineInto(&tmp_line))
    {
        line_list = tmp_line.split(",,", QString::SkipEmptyParts);
        if (line_list.length() < 3)
        {
            std::cerr << "Incorrect amount of values, expected amount is 3 or more.\n";
            return bus_lines;
        }

        for (int i = 1; i < line_list.length(); i++)
        {
            str_list = line_list.at(i).split(",", QString::SkipEmptyParts);
            if (str_list.length() < 12)
            {
                std::cerr << "Incorrect amount of values, expected amount is 12 or more.\n";
                return bus_lines;
            }

            for (int j = 2; j < str_list.length(); j++)
            {
                tmp_times.append(QTime::fromString(str_list.at(j), "hh:mm"));
                if (tmp_times.last().toString("hh:mm") != str_list.at(j))
                {
                    std::cerr << "Incorrect value format of " << str_list.at(j).toStdString() << ", expected format is hh:mm (e.g. 09:06).\n";
                    return bus_lines;
                }
            }

            routes.append(QPair<Stop, QVector<QTime>>(Stop(str_list.at(0), str_list.at(1).toInt(&ok, 10)), tmp_times));
            if (!ok)
            {
                std::cerr << "Incorrect value type of " << str_list.at(1).toStdString() << ", expected type is integer.\n";
                return bus_lines;
            }
            tmp_times.clear();
        }

        bus_lines[line_list.at(0).toInt(&ok, 10)] = Route(routes);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << line_list.at(0).toStdString() << ", expected type is integer.\n";
            return bus_lines;
        }
        routes.clear();
    }

    file.close();
    return bus_lines;
}
