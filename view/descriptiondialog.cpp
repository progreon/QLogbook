#include "descriptiondialog.h"
#include "ui_descriptiondialog.h"

DescriptionDialog::DescriptionDialog(LogbookModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DescriptionDialog)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText(model->description());
}

DescriptionDialog::~DescriptionDialog()
{
    delete ui;
}

QString DescriptionDialog::description() const
{
    return ui->plainTextEdit->toPlainText();
}
