#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include "street.h"
#include <QVector>

class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainScene(QObject *parent = nullptr);

signals:
};

#endif // MAINSCENE_H
