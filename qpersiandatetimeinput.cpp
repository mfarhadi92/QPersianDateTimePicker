#include "qpersiandatetimeinput.h"
#include "ui_qpersiandatetimeinput.h"
#include "qpersiandatetimewidget.h"

QPersianDateTimeInput::QPersianDateTimeInput(QWidget *parent)
    : QWidget(parent) ,
      ui(new Ui::QPersianDateTimeInput)
{
    ui->setupUi(this);
    ui->line_dateTime->installEventFilter(this);
    pdDialog    = new QPersianDateTimeWidget(this);
}

void QPersianDateTimeInput::setFormat(QString format_)
{
    format  = format_;
    pdDialog->setFormat(format);
    ui->line_dateTime->setText(pDateTime.toString(format));
}

bool QPersianDateTimeInput::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);
    if (event->type() == QEvent::MouseButtonPress)
        on_btn_calendar_clicked();
    return QWidget::eventFilter(object,event);
}


void QPersianDateTimeInput::setPDateTime(QPersianDateTime datetime)
{
    pDateTime = datetime;
    pdDialog->setPDateTime(datetime);
    ui->line_dateTime->setText(pDateTime.toString(format));
}

QPersianDateTimeInput::~QPersianDateTimeInput()
{
    delete ui;
}

void QPersianDateTimeInput::mousePressEvent(QMouseEvent *event)
{
    on_btn_calendar_clicked();
    QWidget::mousePressEvent(event);
}


void QPersianDateTimeInput::on_btn_calendar_clicked()
{
    pdDialog->setPDateTime(pDateTime);
    if( pdDialog->exec() == QDialog::Accepted )
    {
        pDateTime   = pdDialog->getPDateTime();
        ui->line_dateTime->setText(pdDialog->getPDateTime().toString(format));
    }
}
