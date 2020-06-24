/**
 * @file mainscene.cpp
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief MainScene source file. This file contains implementation of custom scene.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "mainscene.h"


MainScene::MainScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->dialog_shown == true)
    {
        for (auto *item : MainScene::items())
        {
            auto *ellipse = dynamic_cast<QGraphicsEllipseItem *>(item);
            if (ellipse != nullptr)
            {
                ellipse->setBrush(QBrush(Qt::red));
            }
        }

        this->dialog_shown = false;
    }

    for (auto *item : items(event->scenePos())) //iterate through all items on a position where a vehicle could be located
    {
        auto *vehicle = dynamic_cast<Vehicle *>(item);
        if (vehicle != nullptr)
        { //item is a vehicle
            QString schedule_text = "";
            QPair<const Stop *const, QVector<QTime>> pair = vehicle->getRoute().getRoutes()[0];

            //schedule_text += "Previous stop: " + vehicle->getPrevStopTime().toString("hh:mm, ") + "Next stop: " + vehicle->getNextStopTime().toString("hh:mm<br>");

            bool time_index_found = false;
            int time_index;
            int i = 1;
            for (auto pair_stop_times : vehicle->getRoute().getRoutes()) //iterate over all pairs of stop&times
            {
                if (time_index_found == false) //find index of time to be highlighted
                {
                    time_index = 0;
                    for (auto time : pair_stop_times.second)
                    {
                        if (time == vehicle->getStartedAt())
                        {
                            time_index_found = true;
                            break;
                        }

                        time_index++;
                    }
                }

                for (auto *item2 : items(pair_stop_times.first->getCoordinates())) //iterate through all items on a position where a stop should be located
                {
                    auto *ellipse = dynamic_cast<QGraphicsEllipseItem *>(item2);
                    if (ellipse != nullptr)
                    {               //item2 is an ellipse (stop)
                        if (i == 1) //first stop has diff. color
                        {
                            ellipse->setBrush(QBrush(Qt::darkBlue));
                        }
                        else
                        {
                            ellipse->setBrush(QBrush(Qt::darkRed));
                        }

                        break;
                    }
                }

                this->dialog_shown = true;

                schedule_text += "Stop " + QString::number(i) + " on " + pair_stop_times.first->getStreet()->getName() + ":"; //make text for schedule_box
                for (int j = 0; j < pair_stop_times.second.length(); j++)
                {
                    if (j != time_index)
                        schedule_text += pair_stop_times.second[j].toString(" hh:mm,");
                    else
                        schedule_text += pair_stop_times.second[j].toString(" <b>hh:mm</b>,");
                }
                schedule_text += "<br>";
                i++;
            }

            QDialog* r = new QDialog();
            r->setAttribute(Qt::WA_DeleteOnClose);
            r->setWindowTitle(QString("Schedule"));
            QLabel* l = new QLabel(schedule_text);
            QHBoxLayout* layout = new QHBoxLayout();
            layout->addWidget(l);
            r->setLayout(layout);
            r->setModal(true);
            r->setWindowTitle("Schedule");
            r->show();

            break;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
