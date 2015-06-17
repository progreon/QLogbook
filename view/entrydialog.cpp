#include "entrydialog.h"
#include "ui_entrydialog.h"

EntryDialog::EntryDialog(LogbookModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog),
    _model(model)
{
    ui->setupUi(this);
    for (int i=0; i<_model->types().count(); i++) {
        EntryType type = _model->types().at(i);
//        ui->comboTypes->setItemText(type.id(), type.name());
        ui->comboTypes->addItem(type.name());
    }
    setLogEntry(LogEntry(QDate::currentDate(), QTime(0, 0), model->types().at(0), ""));
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

LogEntry EntryDialog::logEntry() const
{
    return LogEntry(ui->dateEdit->date(), QTime(ui->spinHours->value(), ui->spinMinutes->value()), _model->types().at(ui->comboTypes->currentIndex()), ui->txtDescription->toPlainText());
}

void EntryDialog::setLogEntry(const LogEntry &logEntry)
{
    ui->dateEdit->setDate(logEntry.date());
    ui->spinHours->setValue(logEntry.duration().hour());
    ui->spinMinutes->setValue(logEntry.duration().minute());
    ui->comboTypes->setCurrentIndex(logEntry.type().id());
    ui->txtDescription->setPlainText(logEntry.description());
}
