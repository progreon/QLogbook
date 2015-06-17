#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include "../model/logentry.h"
#include "../model/logbookmodel.h"

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(LogbookModel *model, QWidget *parent = 0);
    ~EntryDialog();
    LogEntry logEntry() const;
    void setLogEntry(const LogEntry &logEntry);

private:
    Ui::EntryDialog *ui;
    LogbookModel *_model;
};

#endif // ENTRYDIALOG_H
