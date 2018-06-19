//
// Created by radyop on 10.5.18.
//


#include <QApplication>
#include <QHBoxLayout>
#include <QtGui/QPainter>
#include "MainFrame.h"
#include "NetworkChecker.h"


int main(int argc, char *argv[]) {

    //nova QT aplikace
    QApplication app(argc, argv);

    //MainWindow o;
    QWidget mainWidget;

    // layout
    auto *horizontalLayout = new QHBoxLayout(&mainWidget);
    horizontalLayout->setMargin(0);
    auto mainFrame = new MainFrame(&mainWidget, 12);
    horizontalLayout->addWidget(mainFrame);

    mainWidget.setWindowTitle(QObject::tr("Led controller"));
    mainWidget.setFixedSize(480, 320);
    mainWidget.move(0,0);
    mainWidget.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QPixmap bg_pixmap(R"(../images/bg.png)");
    bg_pixmap = bg_pixmap.scaled(mainWidget.size());
    QPalette palette;
    palette.setBrush(QPalette::Background, bg_pixmap);
    mainWidget.setPalette(palette);



    mainWidget.show();
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    return QApplication::exec();
}
