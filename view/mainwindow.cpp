#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include "entrydialog.h"
#include "descriptiondialog.h"

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

void MainWindow::updateTotals()
{
    if (_model->entries()->count() > 0) {
        QVector<double> totals = _model->durations();

        QString str("Totaal: ");
        for (int i = 0; i < _model->types().count(); i++) {
            str.append(_model->types().at(i).name()).append(": ").append(QString::number(totals.at(i))).append("h ");
        }
        ui->lblTotal->setText(str);
    } else {
        ui->lblTotal->setText("");
    }
}

void MainWindow::updateView()
{
    setWindowTitle(windowTitle + QString(" - ") + QString(_model->isEdited()?" *":" ") + _model->currentOpenFile());
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    updateTotals();
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

void MainWindow::on_actionE_xit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (_model->isEdited()) {
        int result = QMessageBox::question(this, "Open bestand opslaan?", "Wilt u het open bestand eerst opslaan?", QMessageBox::Cancel, QMessageBox::No, QMessageBox::Yes);
        if (result == QMessageBox::Yes) {
            on_action_Save_triggered();
            if (_model->isEdited()) {
                e->ignore();
                return; // we did not save!
            }
        } else if (result == QMessageBox::Cancel) {
            e->ignore();
            return;
        }
    }
    e->accept();
}

void MainWindow::on_action_Nieuw_2_triggered()
{
    on_btnNew_clicked();
}

void MainWindow::on_actionB_ewerk_triggered()
{
    on_btnEdit_clicked();
}

void MainWindow::on_actionVerwij_der_triggered()
{
    on_btnDelete_clicked();
}

void MainWindow::on_actionExporteer_pdf_triggered()
{
    on_btnPdf_clicked();
}

void MainWindow::on_action_Beschrijving_triggered()
{
    DescriptionDialog dialog(_model, this);
    int result = dialog.exec();
    if (result == 1) {
        _model->setDescription(dialog.description());
    }
}

void MainWindow::on_actionExporter_csv_triggered()
{
    QString fileName = _model->currentOpenFile().right(_model->currentOpenFile().count() - _model->currentOpenFile().lastIndexOf(QDir::separator()) - 1);
    if (fileName.endsWith(".qlog")) {
        fileName = fileName.left(fileName.lastIndexOf(".qlog"));
    }
    QFileDialog fileDialog(this, "Exporteer csv", currDir.append(QDir::separator()).append(fileName).append(".csv"), tr("CSV Bestanden (*.csv)"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec() == QFileDialog::AcceptSave) {
        QString filePath = fileDialog.selectedFiles().at(0);
        qDebug() << "exporting csv to:" << filePath;
        _model->exportLogbookCSV(filePath);
        currDir = fileDialog.directory().absolutePath();
    }
}
