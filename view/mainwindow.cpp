#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "entrydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windowTitle = "Logboek";
    currDir = ".";
    _model = new LogbookModel;
    tableModel = new LogTableModel(_model);
    ui->tableView->setModel(tableModel);
    updateView();
    //    ui->tableView->resizeColumnsToContents();
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
        updateView();
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
            updateView();
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
            updateView();
        }
    }
}

void MainWindow::on_btnPdf_clicked()
{
    QString fileName = _model->currentOpenFile().right(_model->currentOpenFile().count() - _model->currentOpenFile().lastIndexOf(QDir::separator()) - 1);
    if (fileName.endsWith(".qlog")) {
        fileName = fileName.left(fileName.lastIndexOf(".qlog"));
    }
    QFileDialog fileDialog(this, "Exporteer pdf", currDir.append(QDir::separator()).append(fileName).append(".pdf"), tr("PDF Bestanden (*.pdf)"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec() == QFileDialog::AcceptSave) {
        QString filePath = fileDialog.selectedFiles().at(0);
        qDebug() << "exporting pdf to:" << filePath;
        _model->exportLogbookPDF(filePath);
        currDir = fileDialog.directory().absolutePath();
    }
}

void MainWindow::on_action_Save_As_triggered()
{
    QFileDialog saveAsDialog(this, "Opslaan Als", currDir.append(QDir::separator()).append(".qlog"), tr("QLogbook Files (*.qlog)"));
    saveAsDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (saveAsDialog.exec()) {
        QString filePath = saveAsDialog.selectedFiles().at(0);
        qDebug() << "saving to:" << filePath;
        _model->saveAsLogbookJSON(filePath);
        currDir = saveAsDialog.directory().absolutePath();
        updateView();
    }
}

void MainWindow::on_action_Save_triggered()
{
    if (_model->isNew()) {
        on_action_Save_As_triggered();
    } else {
        _model->saveLogbookJSON();
        updateView();
    }
}

void MainWindow::on_action_Open_triggered()
{
    if (_model->isEdited()) {
        int result = QMessageBox::question(this, "Open bestand opslaan?", "Wilt u het open bestand eerst opslaan?", QMessageBox::Cancel, QMessageBox::No, QMessageBox::Yes);
        if (result == QMessageBox::Yes) {
            on_action_Save_triggered();
            if (_model->isEdited()) {
                return; // we did not save!
            }
        } else if (result == QMessageBox::Cancel) {
            return;
        }
    }
    QFileDialog openDialog(this, "Openen", currDir, tr("QLogbook files (*.qlog)"));
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (openDialog.exec()) {
        _model->loadLogbookJSON(openDialog.selectedFiles().at(0));
        currDir = openDialog.directory().absolutePath();
        tableModel->refreshTable();
        updateView();
    }
}

void MainWindow::updateView()
{
    setWindowTitle(windowTitle + QString(" - ") + QString(_model->isEdited()?" *":" ") + _model->currentOpenFile());
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

void MainWindow::on_action_Nieuw_triggered()
{
    if (_model->isEdited()) {
        int result = QMessageBox::question(this, "Open bestand opslaan?", "Wilt u het open bestand eerst opslaan?", QMessageBox::Cancel, QMessageBox::No, QMessageBox::Yes);
        if (result == QMessageBox::Yes) {
            on_action_Save_triggered();
            if (_model->isEdited()) {
                return; // we did not save!
            }
        } else if (result == QMessageBox::Cancel) {
            return;
        }
    }
    _model->startEmptyLogbook();
    tableModel->refreshTable();
    updateView();
}
