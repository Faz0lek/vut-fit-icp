#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "street.h"
#include <QVector>
#include <QTimer>
#include <QTime>

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
    void on_openMapButton_clicked();
    void on_zoomSlider_valueChanged(int value);
    void onClockTick();

private:
    Ui::MainWindow *ui;
    QVector<Street> map;
    QTimer* clock;
    QTime time;

    void initScene();
    void drawMap(const QVector<Street>& map);
};
#endif // MAINWINDOW_H
