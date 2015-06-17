#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logtablemodel.h"

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

private:
    Ui::MainWindow *ui;
    LogTableModel *tableModel;
};

#endif // MAINWINDOW_H
