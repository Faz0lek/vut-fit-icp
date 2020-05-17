#include "mainscene.h"



MainScene::MainScene(QObject *parent)
    : QGraphicsScene(parent)
{}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for (auto* item : items(event->scenePos()))
    {
        auto* vehicle = dynamic_cast<Vehicle*>(item);
        if (vehicle != nullptr)
        { //item is a vehicle
            QString schedule_text = "";
            QPair<const Stop * const, QVector<QTime>> pair = vehicle->getRoute().getRoutes()[0];

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

                for (auto* item2 : items(pair_stop_times.first->getCoordinates()))
                {
                    auto* ellipse = dynamic_cast<QGraphicsEllipseItem*>(item2);
                    if (ellipse != nullptr)
                    { //item2 is an ellipse (stop)
                        if (i == 1)
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



                schedule_text += "Stop " + QString::number(i) + " on " + pair_stop_times.first->getStreet()->getName() + ":";
//                for (auto time : pair_stop_times.second)
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

            QMessageBox schedule_box;
            schedule_box.setTextFormat(Qt::RichText);
            schedule_box.setText(schedule_text);
            schedule_box.exec();

            //reverse state
            for (auto pair_stop_times : vehicle->getRoute().getRoutes()) //iterate over all pairs of stop&times
            {
                for (auto* item2 : items(pair_stop_times.first->getCoordinates()))
                {
                    auto* ellipse = dynamic_cast<QGraphicsEllipseItem*>(item2);
                    if (ellipse != nullptr)
                    { //item2 is an ellipse (stop)
                        ellipse->setBrush(QBrush(Qt::red));

                        break;
                    }
                }
            }

            break;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
