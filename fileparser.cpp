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
QVector<Street> FileParser::ParseStreet(const QString streetfilename)
{
    QVector<Street> vector;

    QFile file(streetfilename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed opening file with provided streetfilename.\n";
        return vector;
    }

    QTextStream text(&file);

    QString line;
    QStringList str_list;
    int x1, y1, x2, y2;
    bool ok = true;

    while (text.readLineInto(&line))
    {
        str_list = line.split(',', QString::SkipEmptyParts);
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

QMap<int, QVector<Route>> FileParser::ParseRoute(const QString stopfilename, const QString routefilename, const QString linefilename)
{
    QMap<int, QVector<Route>> lines;

    QFile stop_file(stopfilename);
    if (!stop_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed opening file with provided stopfilename.\n";
        return lines;
    }

    QFile route_file(routefilename);
    if (!route_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed opening file with provided routefilename.\n";
        return lines;
    }

    QFile line_file(linefilename);
    if (!line_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Failed opening file with provided linefilename.\n";
        return lines;
    }

    Stop tmp_stop;
    QString stop_line, route_line, line_line;
    QStringList stop_list, route_list, line_list;
    int line_number;
    bool ok = true;

    QStringList text_stream_line_list;
    QTextStream line_text(&line_file);
    while (true)
    {
        line_line = line_text.readLine();
        if (line_line == NULL)
            break;

        text_stream_line_list.append(line_line);
    }

    QStringList text_stream_route_list;
    QTextStream route_text(&route_file);
    while (true)
    {
        route_line = route_text.readLine();
        if (route_line == NULL)
            break;

        text_stream_route_list.append(route_line);
    }

    QStringList text_stream_stop_list;
    QTextStream stop_text(&stop_file);
    while (true)
    {
        stop_line = stop_text.readLine();
        if (stop_line == NULL)
            break;

        text_stream_stop_list.append(stop_line);
    }

    for (int l = 0; l < text_stream_line_list.length(); l++)
    {
        line_list = text_stream_line_list[l].split(',', QString::SkipEmptyParts);
        if (line_list.length() < 11)
        {
            std::cerr << "Incorrect amount of values, expected amount is 11 or more.\n";
            return lines;
        }

        line_number = line_list.at(0).toInt(&ok, 10);
        if (!ok)
        {
            std::cerr << "Incorrect value type of " << line_list.at(0).toStdString() << ", expected type is integer.\n";
            return lines;
        }

        QVector<Route> tmp_routes;
        for (int i = 1; i < line_list.length(); i++) //iteruje pres hodnoty autobusove linky, pres [Route]
        {
            for (int r = 0; r < text_stream_route_list.length(); r++)
            {
                route_list = text_stream_route_list[r].split(',', QString::SkipEmptyParts);
                if (route_list.length() < 5 || (route_list.length() % 2) == 0)
                {
                    std::cerr << "Incorrect amount of values, expected amount is even and 5 or more.\n";
                    return lines;
                }

                if (line_list.at(i) == route_list.at(0))
                {
                    QVector<QPair<Stop, int>> tmp_route;
                    for (int j = 1; j < route_list.length(); j += 2) //iteruje pres kazdou lichou hodnotu spoje, pres [QPair<Stop, int>]
                    {
                        for (int s = 0; s < text_stream_stop_list.length(); s++)
                        {
                            stop_list = text_stream_stop_list[s].split(',', QString::SkipEmptyParts);
                            if (stop_list.length() != 3)
                            {
                                std::cerr << "Incorrect amount of values, expected amount is even and 3.\n";
                                return lines;
                            }

                            if (route_list.at(j) == stop_list.at(0))
                            {
                                tmp_stop = Stop(stop_list.at(1), stop_list.at(2).toInt(&ok, 10));
                                if (!ok)
                                {
                                    std::cerr << "Incorrect value type of " << stop_list.at(2).toStdString() << ", expected type is integer.\n";
                                    return lines;
                                }

                                if (!ok)
                                {
                                    std::cerr << "Incorrect value type of " << route_list.at(j + 1).toStdString() << ", expected type is integer.\n";
                                    return lines;
                                }

                                tmp_route.append(QPair<Stop, int>(tmp_stop, route_list.at(j + 1).toInt(&ok, 10)));
                                break;
                            }
                        }
                    }

                    tmp_routes.append(Route(tmp_route));
                    break;
                }
            }
        }

        lines[line_number] = tmp_routes;
    }

    stop_file.close();
    route_file.close();
    line_file.close();
    return lines;
}
