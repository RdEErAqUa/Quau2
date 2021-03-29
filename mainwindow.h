#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/Sample/qsampleitemmodel.h"
#include "Models/Sample/qparameteritemmodel.h"
#include "qcustomplot.h"
#include "Models/Sample/qtwodimparameter.h"
#include "Models/Sample/qregressiontablemodel.h"

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

    void on_actionAddSample_triggered();

    void on_treeView_clicked(const QModelIndex &index);

    void on_actionAddTwoDimSample_triggered();
    void on_actionaddHigherDim_triggered();

public slots:
    void AddRegression(int regression_value);
    void contextMenuRequest(QPoint pos);

private:
    void clear_plot(QCustomPlot *customPlot);
    void set_basic_plot(QCustomPlot *customPlot);
    void clear_set_basic_plot(QCustomPlot *customPlot);
    void add_plot_data(QCustomPlot *customPlot, QVector<double> x, QVector<double> y, QCPGraph::LineStyle lineStyle = QCPGraph::lsLine
            , QCPScatterStyle::ScatterShape scatterStyle = QCPScatterStyle::ssCrossCircle);

    void build_sample_plot(OneDimSample *sample);
    void build_sample_parameter(OneDimSample *sample, QParameterItemModel *_parameter, QAbstractItemView *item);
    void build_two_dim_sample_plot(TwoDimSample *sample);


private:
    Ui::MainWindow *ui;
    QParameterItemModel *parameter_model;
    QTwoDimParameter *two_dim_parameter;
    QSampleItemModel *sample_model;
    QRegressionTableModel *regression_model;
};
#endif // MAINWINDOW_H
