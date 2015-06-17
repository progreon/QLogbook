#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "entrydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new LogbookModel;
    tableModel = new LogTableModel(_model);
    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableView->resizeColumnsToContents();
    //    ui->tableView->resizeRowsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

void MainWindow::on_btnNew_clicked()
{
    EntryDialog dialogNew(_model, this);
    int result = dialogNew.exec();
    if (result == 1) {
        _model->addEntry(dialogNew.logEntry());
        tableModel->refreshTable();
    }
}

void MainWindow::on_btnEdit_clicked()
{
    if (ui->tableView->selectionModel()->selectedRows().count() > 0) {
        EntryDialog dialogEdit(_model, this);
        dialogEdit.setWindowTitle("Bewerken");
        int selectedRow = ui->tableView->selectionModel()->selectedRows().at(0).row();
        dialogEdit.setLogEntry(_model->entries()->at(selectedRow));
        int result = dialogEdit.exec();
        if (result == 1) {
            _model->modifyEntry(selectedRow, dialogEdit.logEntry());
        }
    }
}

void MainWindow::on_btnDelete_clicked()
{
    if (ui->tableView->selectionModel()->selectedRows().count() > 0) {
        int selectedRow = ui->tableView->selectionModel()->selectedRows().at(0).row();
        int result = QMessageBox::warning(this, "Verwijderen", "Bent u zeker dat u deze entry wilt verwijderen?", QMessageBox::Cancel, QMessageBox::Ok);
        if (result == QMessageBox::Ok) {
            _model->deleteEntry(selectedRow);
            tableModel->refreshTable();
        }
    }
}

void MainWindow::on_btnPdf_clicked()
{

}
