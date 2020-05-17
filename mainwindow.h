/**
 * @file mainwindow.h
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Mainwindow header file.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "street.h"
#include <QVector>
#include <QTimer>
#include <QTime>
#include <QMap>
#include "busline.h"
#include "stop.h"
#include "vehicle.h"
#include "fileparser.h"
#include <QApplication>
#include "mainscene.h"
#include <QGraphicsView>
#include <QString>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QFileDialog>
#include <QtMath>
#include <QInputDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/*!
 * @brief Class describing MainWindow. Used to operate on main application window.
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * @brief Construct a new Main Window object
     * 
     * @param parent 
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * @brief Destroy the Main Window object
     * 
     */
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_zoomSlider_valueChanged(int value);
    void onClockTick();

    void on_setSpeedButton_clicked();

private:
    Ui::MainWindow *ui;

    FileParser p;

    QVector<Street> map;
    QVector<Stop *> stops;
    QMap<int, BusLine> lines;
    QList<Vehicle *> buses;

    QTimer *clock;
    QTime time;

    void initScene();
    void drawMap(const QVector<Street> &map);
    void initStops();
    void drawStops();

    bool draw_complete;

    constexpr static int DEFAULT_SPEED = 1000;
    qreal timeout_multiplier;
};
#endif // MAINWINDOW_H
