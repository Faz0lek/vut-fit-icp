/**
 * @file mainwindow.cpp
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Mainwindow source file. This file implements the behaviour of main window.
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

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
#include <QInputDialog>
#include <QMessageBox>
#include "vehicle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->zoomSlider->hide();

    this->draw_complete = false;
    this->timeout_multiplier = 1;

    clock = new QTimer(this);
    connect(clock, &QTimer::timeout, this, &MainWindow::onClockTick);

    time = QTime(6, 0);
    ui->timeLabel->setText(this->time.toString("hh:mm"));
    ui->speedLabel->setText((QString) "Speed: " + QString::number(this->timeout_multiplier, 'f', 2));
    this->initScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScene()
{
    auto *scene = new MainScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    connect(clock, SIGNAL(timeout()), scene, SLOT(advance()));
}

void MainWindow::drawMap(const QVector<Street> &map)
{
    ui->graphicsView->scene()->clear();

    for (auto s : map)
    {
        auto line = ui->graphicsView->scene()->addLine(s.getBeginning().x(), s.getBeginning().y(), s.getEnd().x(), s.getEnd().y());
        line->setPen(QPen({Qt::darkGray}, 7));
    }
}

void MainWindow::drawStops()
{
    for (const auto &stop : this->stops)
    {
        QPointF p = stop->getCoordinates();

        auto e = ui->graphicsView->scene()->addEllipse(p.x() - (Stop::WIDTH * 0.5), p.y() - (Stop::HEIGHT * 0.5), stop->WIDTH, stop->HEIGHT);
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

    this->clock->stop();

    this->lines = p.ParseLine(linesFileName, &this->map);
    this->stops = p.getStops();
    this->drawStops();

    this->draw_complete = true;

    bool ok;
    QMessageBox err_box;
    QMessageBox warning_box;
    err_box.setText("Invalid time format.");
    warning_box.setText("Time not set. Default value 6:00 will be used.");
    QString text_time;
    QTime qtime_time;
    while (true)
    {
        ok = false;
        text_time = QInputDialog::getText(this, tr("Set time of simulation"), tr("Time: "), QLineEdit::Normal, tr("(e.g. 17:45, 06:02, 11:00, ...)"), &ok);
        if (ok == true)
        {
            qtime_time = QTime::fromString(text_time, "hh:mm");
            if (qtime_time.toString("hh:mm") != text_time)
            {
                err_box.exec();
                continue;
            }

            this->time = qtime_time;
            ui->timeLabel->setText(this->time.toString("hh:mm"));

            if (this->timeout_multiplier != 0.0)
                this->clock->start(DEFAULT_SPEED / timeout_multiplier);

            break;
        }
        else
        {
            warning_box.exec();
            this->time = QTime(6, 0);
            ui->timeLabel->setText(this->time.toString("hh:mm"));

            if (this->timeout_multiplier != 0.0)
                this->clock->start(DEFAULT_SPEED / this->timeout_multiplier);

            break;
        }
    }
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

    for (const auto &line : this->lines)
    {
        size_t i = 0;
        for (const auto &t : line.getRoutes()[0].second)
        {
            if (t.hour() == this->time.hour() && t.minute() == this->time.minute())
            {
                Vehicle *v = new Vehicle(line, i);
                v->setStartedAt(this->time);

                this->buses.append(v);
                ui->graphicsView->scene()->addItem(v);
                break;
            }
            i++;
        }
    }
}

void MainWindow::on_setSpeedButton_clicked()
{
    bool ok;
    QMessageBox err_box;
    err_box.setText("Invalid speed format. Enter double in range <0,100>");
    QString text_speed;
    double double_speed;
    while (true)
    {
        ok = false;
        text_speed = QInputDialog::getText(this, tr("Set speed of simulation"), tr("Double in range <0,100>:"), QLineEdit::Normal, tr("(e.g. 0.5, 23, 96.66, ...)"), &ok);
        if (ok == true)
        {
            ok = false;
            double_speed = text_speed.toDouble(&ok);
            if (!ok || double_speed > 100 || double_speed < 0)
            {
                err_box.exec();
                continue;
            }

            this->timeout_multiplier = double_speed;
            ui->speedLabel->setText((QString) "Speed: " + QString::number(this->timeout_multiplier, 'f', 2));

            if (this->timeout_multiplier != 0.0)
            {
                if (this->draw_complete)
                    this->clock->start(DEFAULT_SPEED / this->timeout_multiplier);
            }
            else
            {
                this->clock->stop();
            }

            break;
        }
        else
        {
            break;
        }
    }
}
