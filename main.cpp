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
    auto *horizontalLayout = new QHBoxLayout(&mainWidget);
    horizontalLayout->setMargin(0);
    auto widget = new MainFrame(&mainWidget, 10);
    horizontalLayout->addWidget(widget);
    /*for(auto label : widget->points){
        horizontalLayout->addWidget(label);
    }*/
    mainWidget.setWindowTitle(QObject::tr("Test"));
    mainWidget.setFixedSize(480, 320);
    mainWidget.move(0,0);
    mainWidget.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QPixmap bg_pixmap(R"(../images/bg.png)");
    bg_pixmap = bg_pixmap.scaled(mainWidget.size());
    QPalette palette;
    palette.setBrush(QPalette::Background, bg_pixmap);
    mainWidget.setPalette(palette);

    mainWidget.show();
    //o.show();
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    return app.exec();
}
