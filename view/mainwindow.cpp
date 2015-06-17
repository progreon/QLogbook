#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableModel = new LogTableModel;
    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableView->resizeColumnsToContents();
    //    ui->tableView->resizeRowsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnNew_clicked()
{
    EntryDialog dialogNew(this);
    int result = dialogNew.exec();
    if (result == 1) {
        tableModel->addEntry(dialogNew.logEntry());
    }
}

void MainWindow::on_btnEdit_clicked()
{
    if (ui->tableView->selectionModel()->selectedRows().count() > 0) {
        EntryDialog dialogEdit(this);
        dialogEdit.setWindowTitle("Bewerken");
        int selectedRow = ui->tableView->selectionModel()->selectedRows().at(0).row();
        dialogEdit.setLogEntry(tableModel->entries().at(selectedRow));
        int result = dialogEdit.exec();
        if (result == 1) {
            tableModel->modifyEntry(selectedRow, dialogEdit.logEntry());
        }
    }
}

void MainWindow::on_btnDelete_clicked()
{
    if (ui->tableView->selectionModel()->selectedRows().count() > 0) {
        int selectedRow = ui->tableView->selectionModel()->selectedRows().at(0).row();
        int result = QMessageBox::warning(this, "Verwijderen", "Bent u zeker dat u deze entry wilt verwijderen?", QMessageBox::Cancel, QMessageBox::Ok);
        if (result == QMessageBox::Ok) {
            tableModel->removeEntry(selectedRow);
        }
    }
}

void MainWindow::on_btnPdf_clicked()
{

}
