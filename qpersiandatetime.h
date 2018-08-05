#ifndef QPERSIANDATETIME_MFARHADI_H
#define QPERSIANDATETIME_MFARHADI_H
/****************************************************************************
**
** Copyright (C) 2018 Mehdi Farhadi <mfarhadi.ece.iut.ac.ir>
** Contact: 09134223351
**
** Examples:
**  QPersianDateTime::currentDateTime().toString();
**
**
** QPersianDateTime p(1397,4,20,QPersianDateTime::PERSIAN);
** p.setTime(QTime::currentTime());
** qDebug() << p.toString() << p.getGDateTime().toString();
** output : "1396-04-20 14:56:03" "Tue Jul 11 14:56:03 2017"
**
**
** QPersianDateTime gd(2018,7,11,QPersianDateTime::GREGORIAN);
** qDebug() << gd.toString("dddd dd MMM yy hh:mm a");
** output : "چهارشنبه 20 تير 97 00:00 صبح"
**
** Licensed for distribution under the GPL version3
****************************************************************************/

#include <QDate>

class QPersianDateTime
{
    static const QList<QString> monthList;
    static const QList<QString> dayList;
    static const QList<int> gDaysInMonth,pDaysInMonth;

    quint16 year;
    quint8 month,day;
    QDateTime gDateTime;

public:
    enum Type { GREGORIAN = 0 , PERSIAN };


private:
    int div(int,int);

public:
    QPersianDateTime(quint16 year_ , quint8 month_ , quint8 day_ , Type type = GREGORIAN);
    QPersianDateTime(QDateTime gDateTime_);
    QPersianDateTime();

    inline quint8   getDay() { return day; }
    inline quint8   getMonth() { return month; }
    inline quint16  getYear() { return year; }
    inline QDateTime    getGDateTime(){ return gDateTime; }

    inline void setPersianDate(const quint16 year_ , const quint8 month_ , const quint8 day_ ) { year = year_; month = month_; day = day_; toGregorian(); }
    inline void setTime( const QTime time){ gDateTime.setTime(time); }
    inline void setGDateTime(QDateTime gDateTime_){ gDateTime = gDateTime_; toPersian(); }
    inline quint8 getPersianDayOfWeek(){ qint8 gDOW = gDateTime.date().dayOfWeek()-1; return gDOW > 4 ? gDOW-4 : gDOW+3; }
    inline quint8 getDaysInMonth(){ return pDaysInMonth[month-1]; }
    inline quint8 getDaysInMonth(quint8 monthIdx){ return pDaysInMonth[monthIdx-1]; }

    bool isLeap();

    static QPersianDateTime currentDateTime();

    QString toString(QString format="yyyy-MM-dd hh:mm:ss");
    QString intToString(int num,int len=-1);

private:
    void toPersian();
    void toGregorian();
    
};
#endif // QPERSIANDATETIME_MFARHADI_H
