#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainscene.h"
#include <QGraphicsView>
#include "street.h"
#include "route.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initScene()
{
    auto* scene = new MainScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
}
