#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainscene.h"
#include <QGraphicsView>
#include "street.h"
#include "route.h"
#include "fileparser.h"
#include <QVector>
#include <QString>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>

const QString MAP_FILENAME = R"(D:\Projects\ICP\vut-fit-icp\streetsfile.csv)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: rgb(75, 75, 75);");

    clock = new QTimer(this);
    connect(clock, &QTimer::timeout, this, &MainWindow::onClockTick);

    time = "6:00";

    this->initScene();

    clock->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScene()
{
    auto* scene = new MainScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setStyleSheet("background-color: rgb(255, 255, 255);");
    //ui->openMapButton->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void MainWindow::drawMap(const QVector<Street>& map)
{
    for (auto s : map)
    {
        auto line = ui->graphicsView->scene()->addLine(s.getBeginning().x(), s.getBeginning().y(), s.getEnd().x(), s.getEnd().y());
        line->setPen(QPen({Qt::darkGray}, 7));
        line->setFlag(QGraphicsItem::ItemIsSelectable);
    }
}

void MainWindow::on_openMapButton_clicked()
{
    FileParser p;

    QString fileName = QFileDialog::getOpenFileName(this, "Open map file", QDir::homePath());

    if (fileName.isNull())
    {
        return;
    }

    this->map = p.ParseStreet(fileName);
    this->drawMap(this->map);
}

void MainWindow::on_zoomSlider_valueChanged(int value)
{
    auto origin = ui->graphicsView->transform();

    qreal scale = value / 10.0;

    ui->graphicsView->setTransform(QTransform(scale, origin.m12(), origin.m21(), scale, origin.dx(), origin.dy()));
}


void MainWindow::onClockTick()
{
    auto t = time.split(":");
    int minutes = t[1].toInt() + 1;
    int hours = t[0].toInt();

    if (minutes == 60)
    {
        minutes = 0;
        hours++;
    }

    if (hours == 24)
    {
        hours = 0;
    }

    time = (hours < 10 ? "0" + QString::number(hours) : QString::number(hours)) + ":" + (minutes < 10 ? "0" + QString::number(minutes) : QString::number(minutes));
    ui->timeLabel->setText(time);
}
