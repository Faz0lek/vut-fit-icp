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

const QString MAP_FILENAME = R"(D:\Projects\ICP\vut-fit-icp\streetsfile.csv)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(75, 75, 75);");

    this->initScene();
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
    ui->graphicsView->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->openMapButton->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void MainWindow::drawMap(const QVector<Street>& map)
{
    for (auto s : map)
    {
        auto line = ui->graphicsView->scene()->addLine(s.getBeginning().x(), s.getBeginning().y(), s.getEnd().x(), s.getEnd().y());
        line->setPen(QPen({Qt::blue}, 5));
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
