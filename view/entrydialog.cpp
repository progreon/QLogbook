#include "entrydialog.h"
#include "ui_entrydialog.h"

EntryDialog::EntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);
    setLogEntry(LogEntry(QDate::currentDate(), QTime(0, 0), 0, ""));
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

LogEntry EntryDialog::logEntry() const
{
    return LogEntry(ui->dateEdit->date(), QTime(ui->spinHours->value(), ui->spinMinutes->value()), 0, ui->txtDescription->toPlainText());
}

void EntryDialog::setLogEntry(const LogEntry &logEntry)
{
    ui->dateEdit->setDate(logEntry.date());
    ui->spinHours->setValue(logEntry.duration().hour());
    ui->spinMinutes->setValue(logEntry.duration().minute());
    ui->txtDescription->setPlainText(logEntry.description());
}
