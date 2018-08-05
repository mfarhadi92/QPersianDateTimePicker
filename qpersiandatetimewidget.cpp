#include "qpersiandatetimewidget.h"
#include "ui_qpersiandatetimewidget.h"
#include <QDebug>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QAnimationGroup>
#include <QPainter>
#include <QTextDocument>
#include <QInputDialog>
#include <QMessageBox>

QPersianDateTimeWidget::QPersianDateTimeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPersianDateTimeWidget)
{
    ui->setupUi(this);
//    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    selectedPDateTime   = new QPersianDateTime(QDateTime::currentDateTime());
    tempPDateTime       = new QPersianDateTime(QDateTime::currentDateTime());
    dayBtnsGroup        = new QButtonGroup(this);
    setWindowTitle("Mehdi Farhadi .::. PersianDate Time");

    QList<QPushButton*> dayBtns = ui->widget_numDays->findChildren<QPushButton*>();
    foreach( QPushButton* btn , dayBtns )
        dayBtnsGroup->addButton(btn,btn->objectName().mid(7).toInt());
    connect(dayBtnsGroup,SIGNAL(buttonClicked(int)),this,SLOT(dayBtns_clicked(int)));
}

QPersianDateTimeWidget::~QPersianDateTimeWidget()
{
    delete ui;
}

void QPersianDateTimeWidget::showEvent(QShowEvent *event)
{
    updateDate();
    updateTime();
    QWidget::showEvent(event);
}

QPersianDateTime QPersianDateTimeWidget::getPDateTime()
{
    return QPersianDateTime(selectedPDateTime->getGDateTime());
}

void QPersianDateTimeWidget::setPDateTime(QPersianDateTime dateTime)
{
    selectedPDateTime->setGDateTime(dateTime.getGDateTime());
    ui->line_min->setText(QString::number(selectedPDateTime->getGDateTime().time().minute()));
    ui->line_hour->setText(selectedPDateTime->intToString(selectedPDateTime->getGDateTime().time().hour()%12,2));
    ui->btn_timeAP->setText(selectedPDateTime->toString("ap"));
}

void QPersianDateTimeWidget::updateDate()
{
    QTextDocument btnDoc;
    QDateTime cDate ;
    lastBtnclicked = 0;
    tempPDateTime->setPersianDate(selectedPDateTime->getYear(),selectedPDateTime->getMonth(),1);
    firstDayOfMonth         = tempPDateTime->getPersianDayOfWeek();
    quint8 dayCountInMonth  = tempPDateTime->getDaysInMonth();
    quint8 dayIdx;
    btnsHtmlText.clear();
    for( dayIdx = 1 ; dayIdx < firstDayOfMonth ; dayIdx++ )
    {
        btnsHtmlText.append("");
        dayBtnsGroup->button(dayIdx)->setIcon(QIcon());
        dayBtnsGroup->button(dayIdx)->setEnabled(false);
    }
    for( ; dayIdx < dayCountInMonth+firstDayOfMonth ; dayIdx++ )
    {
        dayBtnsGroup->button(dayIdx)->setEnabled(true);
        cDate   = tempPDateTime->getGDateTime().addDays(dayIdx-firstDayOfMonth);
        btnsHtmlText.append(QString("<p align=center><span style=\"font-size:16pt;color:%4;\">%1</span><br/>"
                                    "<span style=\"color:%5;font-size:7pt;\">%2&nbsp;</span><span style=\"color:%5;font-size:7pt;\">%3</span></p>")
                            .arg(dayIdx-firstDayOfMonth+1).arg(cDate.toString("MMM")).arg(cDate.date().day()));

        btnDoc.setHtml(btnsHtmlText.last().arg("black").arg("red"));

        btnDoc.setTextWidth(dayBtnsGroup->button(dayIdx)->width());
        QPixmap pixmap(btnDoc.size().width(), btnDoc.size().height());
        pixmap.fill( Qt::transparent );
        QPainter painter(&pixmap);
        btnDoc.drawContents(&painter);
        dayBtnsGroup->button(dayIdx)->setIcon(pixmap);
        dayBtnsGroup->button(dayIdx)->setIconSize(pixmap.size());
    }
    for( ; dayIdx <= dayBtnsGroup->buttons().count() ; dayIdx++ )
    {
        btnsHtmlText.append("");
        dayBtnsGroup->button(dayIdx)->setIcon(QIcon());
        dayBtnsGroup->button(dayIdx)->setEnabled(false);
    }

    dayBtnsGroup->button(selectedPDateTime->getDay()+firstDayOfMonth-1)->setChecked(true);
    ui->btn_changeYear->setText(selectedPDateTime->toString("MMM yyyy"));
    ui->lbl_year->setText(selectedPDateTime->toString("yyyy"));
    ui->lbl_date->setText(selectedPDateTime->toString("dddd , dd MMM"));
    foreach(QPushButton* btn , ui->widget_numDays->findChildren<QPushButton*>() )
    {
        QPropertyAnimation *animation = new QPropertyAnimation(btn, "pos");
        animation->setDuration(300);
        animation->setStartValue(QPointF((ui->widget_numDays->width()/2 + btn->pos().x() ) *.5 ,
                                         (ui->widget_numDays->height()/2 + btn->pos().y() ) *.5));
        animation->setEndValue(btn->pos());
        animation->start();
    }
    dayBtns_clicked(selectedPDateTime->getDay()+firstDayOfMonth-1);
}

void QPersianDateTimeWidget::updateTime()
{
    qint8 hour  = ui->line_hour->text().toInt() + ( 12*((ui->btn_timeAP->text()==QString::fromUtf8("عصر") )?1:0) );
    qint8 min   = ui->line_min->text().toInt();
    selectedPDateTime->setTime(QTime(hour,min,QTime::currentTime().second()));
    ui->lbl_currentTime->setText(selectedPDateTime->toString(format));
}

void QPersianDateTimeWidget::dayBtns_clicked(int btnIdx)
{
    selectedPDateTime->setPersianDate(selectedPDateTime->getYear(),selectedPDateTime->getMonth(),btnIdx-firstDayOfMonth+1);
    ui->lbl_year->setText(selectedPDateTime->toString("yyyy"));
    ui->lbl_date->setText(selectedPDateTime->toString("dddd , dd MMM"));
    QTextDocument btnDoc;
    btnDoc.setHtml(btnsHtmlText.at(btnIdx-1).arg("white").arg("#ccc"));
    btnDoc.setTextWidth(dayBtnsGroup->button(btnIdx)->width());
    QPixmap pixmap(btnDoc.size().width(), btnDoc.size().height());
    pixmap.fill( Qt::transparent );
    QPainter painter(&pixmap);
    btnDoc.drawContents(&painter);
    dayBtnsGroup->button(btnIdx)->setIcon(pixmap);
    dayBtnsGroup->button(btnIdx)->setIconSize(pixmap.size());

    if( lastBtnclicked > 0 )
    {
        btnDoc.clear();
        btnDoc.setHtml(btnsHtmlText.at(lastBtnclicked-1).arg("black").arg("red"));
        btnDoc.setTextWidth(dayBtnsGroup->button(lastBtnclicked)->width());
        pixmap.fill(Qt::transparent);
        painter.end();
        painter.begin(&pixmap);
        btnDoc.drawContents(&painter);
        dayBtnsGroup->button(lastBtnclicked)->setIcon(pixmap);
        dayBtnsGroup->button(lastBtnclicked)->setIconSize(pixmap.size());
    }
    lastBtnclicked  = btnIdx;
}

void QPersianDateTimeWidget::on_btn_changeYear_clicked()
{
    bool ok;
    QStringList years;
    for( quint8 yearIdx = 0 ; yearIdx < 10 ; yearIdx++ )
        years.append(QString::number(selectedPDateTime->getYear()-5+yearIdx));

    QString selectedYearSTR = QInputDialog::getItem(this,QString::fromUtf8("وارد کردن سال"),QString::fromUtf8("لطفاً سال مد نظر خود را انتخاب نمایید"),years,0,true,&ok);
    if( selectedYearSTR.toInt() > 0 )
    {
        quint8 currentMonth = selectedPDateTime->getMonth();
        quint8 currentDay   = selectedPDateTime->getDay();

        selectedPDateTime->setPersianDate(selectedYearSTR.toInt(),currentMonth,
                                          currentDay > selectedPDateTime->getDaysInMonth(currentMonth) ? selectedPDateTime->getDaysInMonth(currentMonth) : currentDay );
        updateDate();
    }
    else
        QMessageBox::warning(this,QString::fromUtf8("انتخاب سال"),QString::fromUtf8("سال انتخاب شده معتبر نمی باشد"));
}

void QPersianDateTimeWidget::on_btn_nextMonth_clicked()
{
    quint8 currentMonth = selectedPDateTime->getMonth();
    quint8 currentDay   = selectedPDateTime->getDay();

    if( currentMonth == 12 )
        selectedPDateTime->setPersianDate(selectedPDateTime->getYear()+1,1,
                                          currentDay > selectedPDateTime->getDaysInMonth(1) ? selectedPDateTime->getDaysInMonth(1) : currentDay );
    else
    {
        selectedPDateTime->setPersianDate(selectedPDateTime->getYear(),currentMonth+1,
                                          currentDay > selectedPDateTime->getDaysInMonth(currentMonth+1) ? selectedPDateTime->getDaysInMonth(currentMonth+1) : currentDay );
    }
    updateDate();
}

void QPersianDateTimeWidget::on_btn_preMonth_clicked()
{
    quint8 currentMonth = selectedPDateTime->getMonth();
    quint8 currentDay   = selectedPDateTime->getDay();

    if( currentMonth == 1 )
        selectedPDateTime->setPersianDate(selectedPDateTime->getYear()-1,12,
                                          currentDay > selectedPDateTime->getDaysInMonth(12) ? selectedPDateTime->getDaysInMonth(12) : currentDay );
    else
    {
        selectedPDateTime->setPersianDate(selectedPDateTime->getYear(),currentMonth-1,
                                          currentDay > selectedPDateTime->getDaysInMonth(currentMonth-1) ? selectedPDateTime->getDaysInMonth(currentMonth-1) : currentDay );
    }
    updateDate();
}

void QPersianDateTimeWidget::on_btn_toggleDateTimeWidget_clicked()
{
    ui->stack_dateTimeWidget->setCurrentIndex(ui->stack_dateTimeWidget->currentIndex()==0?1:0);
    if( ui->stack_dateTimeWidget->currentIndex() == 0 )
    {
        ui->widget_topControll->setVisible(true);
        ui->btn_toggleDateTimeWidget->setIcon(QIcon(":/icon/res/images/time.png"));
    }
    else
    {
        ui->widget_topControll->setVisible(false);
        ui->btn_toggleDateTimeWidget->setIcon(QIcon(":/icon/res/images/date.png"));
    }
    updateDate();
    updateTime();
}

void QPersianDateTimeWidget::on_btn_up_hour_clicked()
{
    qint8 hour = ui->line_hour->text().toInt();
    hour ++;
    if( hour > 12 )
        hour = 1;
    ui->line_hour->setText(selectedPDateTime->intToString(hour,2));
    updateTime();
}

void QPersianDateTimeWidget::on_btn_down_hour_clicked()
{
    qint8 hour = ui->line_hour->text().toInt();
    hour --;
    if( hour <= 0  )
        hour = 12;
    ui->line_hour->setText(selectedPDateTime->intToString(hour,2));
    updateTime();
}

void QPersianDateTimeWidget::on_btn_up_min_clicked()
{
    qint8 min = ui->line_min->text().toInt();
    min ++;
    if( min >= 60  )
        min = 0;
    ui->line_min->setText(selectedPDateTime->intToString(min,2));
    updateTime();
}

void QPersianDateTimeWidget::on_btn_down_min_clicked()
{
    qint8 min = ui->line_min->text().toInt();
    min --;
    if( min < 0  )
        min = 59;
    ui->line_min->setText(selectedPDateTime->intToString(min,2));
    updateTime();
}

void QPersianDateTimeWidget::on_btn_timeAP_clicked()
{
    if( ui->btn_timeAP->text() == QString::fromUtf8("صبح") )
        ui->btn_timeAP->setText(QString::fromUtf8("عصر"));
    else
        ui->btn_timeAP->setText(QString::fromUtf8("صبح"));
    updateTime();
}
