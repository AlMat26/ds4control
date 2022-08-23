#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::string str = "Red: " + std::to_string( ds4leds.getRed() );
    ui->label_red->setText( QString::fromStdString (str) );
    ui->dial_red->setValue( ds4leds.getRed() );

    str = "Green: " + std::to_string( ds4leds.getRed() );
    ui->label_green->setText( QString::fromStdString (str) );
    ui->dial_green->setValue( ds4leds.getGreen() );

    str = "Blue: " + std::to_string( ds4leds.getRed() );
    ui->label_blue->setText( QString::fromStdString (str) );
    ui->dial_blue->setValue( ds4leds.getBlue() );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dial_red_valueChanged(int value)
{
    std::string str = "Red: " + std::to_string(value);
    ui->label_red->setText( QString::fromStdString (str) );
    ds4leds.setRed( value );
}

void MainWindow::on_dial_green_valueChanged(int value)
{
    std::string str = "Green: " + std::to_string(value);
    ui->label_green->setText( QString::fromStdString (str) );
    ds4leds.setGreen( value );
}


void MainWindow::on_dial_blue_valueChanged(int value)
{
    std::string str = "Blue: " + std::to_string(value);
    ui->label_blue->setText( QString::fromStdString (str) );
    ds4leds.setBlue( value );
}


void MainWindow::on_checkBox_automaticRGB_toggled(bool checked)
{
    automaticRGB = checked;
    if ( checked ) {
        autoRGBthr = new std::thread([this]{automaticRGBCycle();});
    }
}

void MainWindow::automaticRGBCycle ()
{
    unsigned int red, green, blue;
    int currentColor = SS_RED;

    red = 255;
    green = 0;
    blue = 0;

    ds4leds.setRed ( red );
    ds4leds.setGreen ( green );
    ds4leds.setBlue ( blue );

    while (automaticRGB) {
        if ( currentColor == SS_RED && blue == 0 && green != 255 ) {
            green++;
            ds4leds.setGreen (green);

        } else if ( currentColor == SS_RED && green == 255 ) {

            currentColor = SS_GREEN;

        } else if ( currentColor == SS_GREEN && red != 0 && blue == 0 ) {

            red--;
            ds4leds.setRed ( red );

        } else if ( currentColor == SS_GREEN && red == 0 && blue != 255 ) {

            blue++;
            ds4leds.setBlue ( blue );

        } else if ( currentColor == SS_GREEN && blue == 255 ) {

            currentColor = SS_BLUE;

        } else if ( currentColor == SS_BLUE && green != 0 && red == 0 ) {

            green--;
            ds4leds.setGreen ( green );

        } else if ( currentColor == SS_BLUE && green == 0 && red != 255 ) {

            red++;
            ds4leds.setRed ( red );

        } else if ( currentColor == SS_BLUE && red == 255 ) {

            currentColor = SS_RED;

        } else if ( currentColor == SS_RED && blue != 0 && green == 0 ) {

            blue--;
            ds4leds.setBlue ( blue );
        }

        ds4leds.wait(100000);
    }
}

