#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../model/logtablemodel.h"
#include "../model/logbookmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnNew_clicked();

    void on_btnEdit_clicked();

    void on_btnDelete_clicked();

    void on_btnPdf_clicked();

    void on_action_Save_triggered();

    void on_action_Open_triggered();

    void on_action_Save_As_triggered();

    void on_action_Nieuw_triggered();

    void on_actionE_xit_triggered();

private:
    void updateView();
    Ui::MainWindow *ui;
    LogbookModel *_model;
    LogTableModel *tableModel;
    QString windowTitle;
    QString currDir;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
