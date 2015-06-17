#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include "../model/logentry.h"

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(QWidget *parent = 0);
    ~EntryDialog();
    LogEntry logEntry() const;
    void setLogEntry(const LogEntry &logEntry);

private:
    Ui::EntryDialog *ui;
};

#endif // ENTRYDIALOG_H
