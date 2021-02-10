#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/Sample/qsampleitemmodel.h"
#include "Models/Sample/qparameteritemmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionAddSample_triggered();

    void on_treeView_clicked(const QModelIndex &index);

    void on_actionAddTwoDimSample_triggered();

    void on_actionLinearRegressionTeylor_triggered();

    void on_actionLinearRegressionMNK_triggered();

private:
    Ui::MainWindow *ui;
    QParameterItemModel *parameter;
    QSampleItemModel *sample_model;
};
#endif // MAINWINDOW_H
