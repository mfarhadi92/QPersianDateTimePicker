#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setFormat("dddd dd MMM yy hh:mm a");
    ui->widget->setPDateTime(QPersianDateTime::currentDateTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}
