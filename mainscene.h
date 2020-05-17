#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include "street.h"
#include "vehicle.h"
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainScene(QObject *parent = nullptr);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
};

#endif // MAINSCENE_H
