#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include "ds4ledcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dial_red_valueChanged(int value);

    void on_dial_green_valueChanged(int value);

    void on_dial_blue_valueChanged(int value);

    void on_checkBox_automaticRGB_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    ds4ledControl ds4leds;
    bool automaticRGB = false;

    void automaticRGBCycle ();
    std::thread *autoRGBthr;
};
#endif // MAINWINDOW_H
