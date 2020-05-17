/**
 * @file main.cpp
 * @author Martin Kostelník (xkoste12), Adam Gajda (xgajda07)
 * @brief Main file
 * @version 1.0
 * @date 2020-05-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
