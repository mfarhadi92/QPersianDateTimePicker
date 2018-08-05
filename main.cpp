#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    qDebug() << QPersianDateTime::currentDateTime().toString();
//    QPersianDateTime p(1396,4,20,QPersianDateTime::PERSIAN);
//    p.setTime(QTime::currentTime());
//    qDebug() << p.toString() << p.getGDateTime().toString();

//    QPersianDateTime gd(2018,7,11,QPersianDateTime::GREGORIAN);
//    qDebug() << gd.toString("dddd dd MMM yy hh:mm a");
    MainWindow w;
    w.show();

    return a.exec();
}
