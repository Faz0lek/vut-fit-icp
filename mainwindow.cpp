#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainscene.h"
#include <QGraphicsView>
#include "street.h"
#include "busline.h"
#include "fileparser.h"
#include <QVector>
#include <QString>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QtMath>
#include "vehicle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->zoomSlider->hide();

    p = FileParser();

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
    auto* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    connect(clock, SIGNAL(timeout()), scene, SLOT(advance()));
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

void MainWindow::drawStops()
{
    for (const auto& stop : this->stops)
    {
        QPointF p = stop->getCoordinates();

        auto e = ui->graphicsView->scene()->addEllipse(p.x(), p.y(), stop->WIDTH, stop->HEIGHT);
        e->setBrush(QBrush(Qt::red));
    }
}

void MainWindow::on_loadButton_clicked()
{
    const QString mapFileName = QFileDialog::getOpenFileName(this, "Open map file", QDir::homePath());
    if (mapFileName.isNull())
    {
        return;
    }

    this->map = p.ParseStreet(mapFileName);
    this->drawMap(this->map);
    ui->zoomSlider->show();


    const QString linesFileName = QFileDialog::getOpenFileName(this, "Open lines file", QDir::homePath());
    if (linesFileName.isNull())
    {
        return;
    }

    this->lines = p.ParseLine(linesFileName, &this->map);
    this->stops = p.getStops();
    this->drawStops();
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

    for (const auto& line : this->lines)
    {
        size_t i = 0;
        for (const auto& t : line.getRoutes()[0].second)
        {
            if (t.hour() == this->time.hour() && t.minute() == this->time.minute())
            {
                Vehicle* v = new Vehicle(line, i);
                this->buses.append(v);
                ui->graphicsView->scene()->addItem(v);
                break;
            }
            i++;
        }
    }
}

void MainWindow::on_setTimeButton_clicked() {}
