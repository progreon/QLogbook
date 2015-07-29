#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#include <QDialog>
#include "../model/logbookmodel.h"

namespace Ui {
class DescriptionDialog;
}

class DescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DescriptionDialog(LogbookModel *model, QWidget *parent = 0);
    ~DescriptionDialog();
    QString description() const;

private:
    Ui::DescriptionDialog *ui;
};

#endif // DESCRIPTIONDIALOG_H
