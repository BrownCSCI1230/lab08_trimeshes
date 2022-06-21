#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>

#include "glwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    GLWidget *glWidget;

    QSlider *p1Slider;
    QSlider *p2Slider;
    QSpinBox *p1Box;
    QSpinBox *p2Box;

    void connectParam1();
    void disconnectParam1();

    void connectParam2();
    void disconnectParam2();

private slots:
    void onValChangeP1(int newValue);
    void onValChangeP2(int newValue);
};
#endif // MAINWINDOW_H
