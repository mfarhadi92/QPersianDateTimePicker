#include "qpersiandatetime.h"
#include <QtMath>

const QList<QString> QPersianDateTime::dayList = QList<QString>() << QString::fromUtf8("دوشنبه") << QString::fromUtf8("سه شنبه") << QString::fromUtf8("چهارشنبه")
                                                                  << QString::fromUtf8("پنجشنبه") << QString::fromUtf8("جمعه") << QString::fromUtf8("شنبه") << QString::fromUtf8("یکشنبه");

const QList<QString> QPersianDateTime::monthList = QList<QString>() << QString::fromUtf8("فروردین") << QString::fromUtf8("اردیبهشت") << QString::fromUtf8("خرداد") << QString::fromUtf8("تیر")
                                                                    << QString::fromUtf8("مرداد") << QString::fromUtf8("شهریور") << QString::fromUtf8("مهر") << QString::fromUtf8("آبان")
                                                                    << QString::fromUtf8("آذر") << QString::fromUtf8("دی") << QString::fromUtf8("بهمن") << QString::fromUtf8("اسفند");


const QList<int> QPersianDateTime::gDaysInMonth = QList<int>() << 31 << 28 << 31 << 30 << 31 << 30 << 31 <<31 << 30 << 31<< 30 << 31;
const QList<int> QPersianDateTime::pDaysInMonth = QList<int>() <<31 <<31 <<31 << 31 << 31 << 31 << 30 << 30 << 30 << 30 << 30 << 29;

QPersianDateTime::QPersianDateTime(quint16 year_, quint8 month_, quint8 day_, Type type)
    :year(year_),month(month_),day(day_)
{
    if( type == PERSIAN )
        toGregorian();
    else
    {
        gDateTime.setDate(QDate(year,month,day));
        toPersian();
    }
    gDateTime.setTime(QTime(0,0,0));
}

QPersianDateTime::QPersianDateTime(QDateTime gDateTime_) : gDateTime(gDateTime_)
{
    toPersian();
}

QPersianDateTime::QPersianDateTime()
{
    gDateTime   = QDateTime::currentDateTime();
    toPersian();
}

bool QPersianDateTime::isLeap()
{
    int yearMod = year%33;
    if (year<=1472 && year >=1343){
        if (yearMod == 1 || yearMod == 5 || yearMod ==9 || yearMod == 13 || yearMod == 17||yearMod==22||yearMod==26||yearMod==23)
            return true;
    }
    else if (year<=1342 && year>=1244 ){
        if (yearMod == 1 || yearMod == 5 || yearMod ==9 || yearMod == 13 || yearMod == 17||yearMod==22||yearMod==26||yearMod==23)
            return true;
    }
    return false;
}

QPersianDateTime QPersianDateTime::currentDateTime()
{
    QPersianDateTime current(QDateTime::currentDateTime());
    return current;
}

QString QPersianDateTime::toString(QString format)
{
    QString strDateTime = format;
    strDateTime = strDateTime.replace("yyyy",intToString(year));
    strDateTime = strDateTime.replace("yy",intToString(year,2));
    strDateTime = strDateTime.replace("MMMM",monthList.at(month-1));
    strDateTime = strDateTime.replace("MMM",monthList.at(month-1));
    strDateTime = strDateTime.replace("MM",intToString(month,2));
    strDateTime = strDateTime.replace("M",intToString(month));
    strDateTime = strDateTime.replace("dddd",dayList.at(gDateTime.date().dayOfWeek()-1));
    strDateTime = strDateTime.replace("ddd",dayList.at(gDateTime.date().dayOfWeek()-1));
    strDateTime = strDateTime.replace("dd",intToString(day,2));
    strDateTime = strDateTime.replace("d",intToString(day));
    static QList<QString> timeFormatStr;
    timeFormatStr<<"ap"<<"a"<<"AP"<<"A"<<"zzz"<<"z"<<"ss"<<"s"<<"mm"<<"m"<<"HH"<<"H"<<"hh"<<"h"<<"t";
    quint8 tfsIdx = 0;
    foreach(QString tf , timeFormatStr)
    {
        QString value = gDateTime.time().toString(tf);
        if( tfsIdx < 4)
        {
            value   = value.toLower();
            value   = value.replace("am",QString::fromUtf8("صبح"));
            value   = value.replace("pm",QString::fromUtf8("عصر"));
        }
        strDateTime = strDateTime.replace(tf,value);
        tfsIdx ++;
    }
    return strDateTime;
}

int QPersianDateTime::div(int a,int b)
{
    if( b != 0 )
        return  (a / b);
    return 0;
}

void QPersianDateTime::toPersian()
{
    int gYear   = gDateTime.date().year();
    int gMonth  = gDateTime.date().month();
    int gDay    = gDateTime.date().day();
    int  gy = gYear-1600;
    int  gm = gMonth-1;
    int  gd = gDay-1;
    int  g_day_no = 365*gy+div(gy+3,4)-div(gy+99,100)+div(gy+399,400);
    for (int i=0; i < gm; ++i)
        g_day_no += gDaysInMonth[i];

    if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
        g_day_no++;
    g_day_no += gd;
    int j_day_no = g_day_no-79;
    int  j_np = div(j_day_no, 12053);
    j_day_no = j_day_no % 12053;
    year = 979+33*j_np+4*div(j_day_no,1461);
    j_day_no %= 1461;

    if (j_day_no >= 366) {
        year += div(j_day_no-1, 365);
        j_day_no = (j_day_no-1)%365;
    }
    int ii;
    for (int i = 0; i < 11 && j_day_no >= pDaysInMonth[i]; ++i){
        j_day_no -= pDaysInMonth[i];
        ii=i;
    }
    month   = ii+2;
    day     = j_day_no+1;
}

void QPersianDateTime::toGregorian()
{
    QList<int> tempGDate;
    QList<int> tmpPersianDate;
    tempGDate<<1<<1<<1;
    tmpPersianDate<<1<<1<<1;

    int marchDayDiff;
    int dayCount;
    QList<int> miladiMonth;
    miladiMonth<<30<<31<<30<<31<<31<<30<<31<<30<<31<<31<<28<<31;
    int tmpGYear = year + 621;
    if (QDate::isLeapYear(tmpGYear))
    {
        tmpPersianDate[1] =3;
        tmpPersianDate[2]= 20;
        marchDayDiff = 12;
    }
    else
    {
        tmpPersianDate[1] = 3;
        tmpPersianDate[2] =21;
        marchDayDiff = 11;
    }
    if (QDate::isLeapYear(tmpGYear+1)){
        miladiMonth[10] = miladiMonth[10] + 1;
    }
    if (month >=1 && month<=6)
        dayCount = ((month-1) * 31) + day;
    else
        dayCount =(6 * 31) + ((month - 7) * 30) + day;

    int remainDay = 0;
    if (dayCount <=marchDayDiff)
    {
        tempGDate[2] = dayCount + (31 - marchDayDiff);
        tempGDate[1] = 3;
        tempGDate[0] = tmpGYear;

    }
    else
        remainDay = dayCount - marchDayDiff;

    int i = 0;
    while (remainDay>miladiMonth[i])
        remainDay = remainDay - miladiMonth[i++];

    tempGDate[2] = remainDay;
    if (i>8)
    {
        tempGDate[1] = i - 8;
        tempGDate[0] =  tmpGYear + 1;
    }
    else
    {
        tempGDate[1] = i + 4;
        tempGDate[0] =  tmpGYear;
    }
    gDateTime.setDate(QDate(tempGDate[0],tempGDate[1],tempGDate[2]));
}

QString QPersianDateTime::intToString(int num, int len)
{
    if( len > 0 )
    {
        if( QString::number(num).length() >= len )
            num = num%(int)pow(10,len);

        QString strNum;
        strNum.reserve(len);
        strNum.fill('0',len);
        return strNum.replace(len - QString::number(num).length(),QString::number(num).length()
                              ,QString::number(num));
    }
    return QString::number(num);
}
