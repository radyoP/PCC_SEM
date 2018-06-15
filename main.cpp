//
// Created by radyop on 10.5.18.
//


#include <QApplication>
#include <QHBoxLayout>
#include <QtCore/QResource>
#include "MainFrame.h"


int main(int argc, char *argv[]) {

    //nova QT aplikace
    QApplication app(argc, argv);

    //MainWindow o;
    QWidget mainWidget;

    // layout
    QHBoxLayout *horizontalLayout = new QHBoxLayout(&mainWidget);
    horizontalLayout->setMargin(0);
    auto widget = new MainFrame(&mainWidget);
    widget->setNumPoints(6);
    horizontalLayout->addWidget(widget);
    /*for(auto label : widget->points){
        horizontalLayout->addWidget(label);
    }*/
    mainWidget.setWindowTitle(QObject::tr("Test"));
    mainWidget.show();
    //o.show();

    return app.exec();
}
