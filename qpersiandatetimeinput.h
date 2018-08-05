#ifndef QPERSIANDATETIMEINPUT_H
#define QPERSIANDATETIMEINPUT_H
/****************************************************************************
** QPersianDateTimeInput
** Copyright (C) 2018 Mehdi Farhadi <mfarhadi.ece.iut.ac.ir>
** Contact: 09134223351
** created at 2018/08/05
**
** Licensed for distribution under the GPL version3
****************************************************************************/

#include <QWidget>
#include <QDialog>
#include <QDateTime>
#include "qpersiandatetime.h"

class QPersianDateTimeWidget;

namespace Ui {
class QPersianDateTimeInput;
}

class QPersianDateTimeInput : public QWidget
{
    Q_OBJECT

private:
    Ui::QPersianDateTimeInput *ui;
    QPersianDateTimeWidget *pdDialog;
    QString         format = "dddd dd MMM yy hh:mm a";
    QPersianDateTime pDateTime;

public:
    explicit QPersianDateTimeInput(QWidget *parent = 0);
    void setFormat(QString format_);
    void setPDateTime(QPersianDateTime datetime);
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    ~QPersianDateTimeInput();

private slots:
    void on_btn_calendar_clicked();
};

#endif // QPERSIANDATETIMEINPUT_H
