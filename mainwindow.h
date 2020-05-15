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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_zoomSlider_valueChanged(int value);
    void onClockTick();

    void on_setTimeButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Street> map;
    QVector<Stop> stops;
    QMap<int, BusLine> lines;

    QTimer* clock;
    QTime time;

    void initScene();
    void drawMap(const QVector<Street>& map);
    void initStops();
    void drawStops();
};
#endif // MAINWINDOW_H
