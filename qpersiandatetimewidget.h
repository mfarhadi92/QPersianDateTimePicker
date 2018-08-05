#ifndef QPERSIANDATETIMEWIDGET_H
#define QPERSIANDATETIMEWIDGET_H
/****************************************************************************
** QPersianDateTimeWidget
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

class QButtonGroup;

namespace Ui {
class QPersianDateTimeWidget;
}

class QPersianDateTimeWidget : public QDialog
{
    Q_OBJECT
private:
    Ui::QPersianDateTimeWidget *ui;
    QPersianDateTime    *selectedPDateTime;
    QPersianDateTime    *tempPDateTime;
    QButtonGroup        *dayBtnsGroup;
    quint8              firstDayOfMonth;
    quint8              lastBtnclicked=0;
    QStringList         btnsHtmlText;
    QString             format = "yyyy-MM-dd hh:mm:ss";

public:
    explicit QPersianDateTimeWidget(QWidget *parent = 0);
    ~QPersianDateTimeWidget();
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    QPersianDateTime    getPDateTime();
    void    setPDateTime(QPersianDateTime dateTime);
    void    setFormat(QString format_){ format = format_; }

private slots:
    void on_btn_changeYear_clicked();
    void on_btn_nextMonth_clicked();
    void dayBtns_clicked(int btnIdx);
    void on_btn_preMonth_clicked();
    void on_btn_toggleDateTimeWidget_clicked();
    void on_btn_up_hour_clicked();
    void on_btn_down_hour_clicked();
    void on_btn_up_min_clicked();
    void on_btn_down_min_clicked();
    void on_btn_timeAP_clicked();

private:
    void updateDate();
    void updateTime();
};

#endif // QPERSIANDATETIMEWIDGET_H
