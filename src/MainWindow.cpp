
#include <QPushButton>
#include <QDebug>
#include <QMenuBar>
#include "MainWindow.h"
#include "MainFrame.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {







}

void MainWindow::handle1(){
    //slot - osetreni signalu
    qDebug() << "tlacitko stisknuto";

    auto t = (QPushButton*)sender();
    qDebug() << t->text();

}

void MainWindow::handle2() {
    qDebug() << "paste";
    status->showMessage("paste");
}
