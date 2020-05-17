#include "mainscene.h"

MainScene::MainScene(QObject *parent)
    : QGraphicsScene(parent)
{}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for (auto* item : items(event->scenePos()))
    {
        qDebug() << "item: " << item;
        auto* vehicle = dynamic_cast<Vehicle*>(item);
        if (vehicle != nullptr)
        { //item is a vehicle
            for (auto pair_stop_time : vehicle->getRoute().getRoutes())
            {
                qDebug() << "pair_stop_time: " << pair_stop_time << "coords: " << pair_stop_time.first->getCoordinates();
//                this->addRect(pair_stop_time.first->getCoordinates().x(),pair_stop_time.first->getCoordinates().y(),10,10);
                for (auto* item2 : items(pair_stop_time.first->getCoordinates()))
                {
                    break; //TODO:WIP
                }
            }

            break;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
