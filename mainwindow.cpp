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
    ui->zoomSlider->hide();

    clock = new QTimer(this);
    connect(clock, &QTimer::timeout, this, &MainWindow::onClockTick);

    time = QTime(6, 0);

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

    const QString fileName = QFileDialog::getOpenFileName(this, "Open map file", QDir::homePath());

    if (fileName.isNull())
    {
        return;
    }

    this->map = p.ParseStreet(fileName);
    this->drawMap(this->map);
    ui->zoomSlider->show();
}

void MainWindow::on_zoomSlider_valueChanged(int value)
{
    const auto origin = ui->graphicsView->transform();
    const qreal scale = value / 10.0;
    ui->graphicsView->setTransform(QTransform(scale, origin.m12(), origin.m21(), scale, origin.dx(), origin.dy()));
}


void MainWindow::onClockTick()
{
    this->time = this->time.addSecs(60);
    ui->timeLabel->setText(this->time.toString("HH:mm"));
}

void MainWindow::on_openLinesButton_clicked()
{
    FileParser p;
    const QString fileName = QFileDialog::getOpenFileName(this, "Open lines file", QDir::homePath());

    if (fileName.isNull())
    {
        return;
    }

    this->lines = p.ParseLine(fileName);
}
