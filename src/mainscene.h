/**
 * @file mainscene.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief MainScene header file. This file contains interface of custom scene.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include "street.h"
#include "vehicle.h"
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMessageBox>

/*!
 * @brief Class describing MainScene. Behaves like QGraphicsScene, except mousePressEvent was redifined.
 * 
 */
class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /*!
     * @brief Construct a new Main Scene object.
     * 
     * @param parent 
     */
    explicit MainScene(QObject *parent = nullptr);

protected:
    /*!
     * @brief Captures mouse press event.
     * 
     * @param event 
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
};

#endif // MAINSCENE_H
