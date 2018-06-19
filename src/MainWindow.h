//
// Created by radyop on 10.5.18.
//
#ifndef CV11_OKNO_H
#define CV11_OKNO_H


#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QStatusBar>

class MainWindow : public QMainWindow {
    // makro vyvola MOC - meta object compiler
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void handle1();
    void handle2();

private:
    QStatusBar *status;


};


#endif //CV11_OKNO_H
