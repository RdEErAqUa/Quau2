#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "Data/sample.h"
#include "StreamWork.h"
#include "Models/Sample/qsampleitemmodel.h"
#include "Delegate/qcomboboxdelegate.h"

#define F_NAME "objectName"
#define F_AGE "age"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sample_model = new QSampleItemModel(this);
    QComboBoxDelegate *delegate = new QComboBoxDelegate();
    ui->treeView->setModel(sample_model);
    ui->treeView->setItemDelegateForColumn(2, delegate);
    parameter = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_actionAddSample_triggered()
{
    QList<double> value = StreamWork::ReadDouble(QFileDialog::getOpenFileName(this,
                                                                              tr("Open File"), tr("Text files (*.txt)")));
    QString name = "data1/sample/";
    int f = sample_model->rowCount(sample_model->index(0, 0, QModelIndex()));
    name.append(QString::number(f));
    Sample *s = new Sample(name, value);
    s->PrimaryAnalysis();
    sample_model->addItemSample(s, QModelIndex());
}

void MainWindow::on_actionAddTwoDimSample_triggered()
{
    QList<double> value = StreamWork::ReadDouble(QFileDialog::getOpenFileName(this,
                                                                              tr("Open File"), tr("Text files (*.txt)")));
    if(value.size() % 2 != 0) {
        QMessageBox msgBox;
        msgBox.setText("Двовимірна вибірка не відповідає критерію");
        msgBox.exec();
        return;
    }
    QString name = "data1/towDimSample/";
    int f = sample_model->rowCount(sample_model->index(0, 0, QModelIndex()));
    name.append(QString::number(f));
    QList<double> X;
    QList<double> Y;
    QList<XY> XYValue;

    for(int i = 0; i < value.size(); i += 2){
        X << value.at(i);
        Y << value.at(i + 1);
        XYValue << XY(value.at(i), value.at(i + 1));
    }

    TwoDimSample *s = new TwoDimSample(XYValue, X, Y);
    s->TwoDimAnalysis();
    sample_model->addItemTwoDimSample(s, QModelIndex());
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if(ui->FirstPlot->actions().size() != 0){
        ui->FirstPlot->removeAction(ui->actionLinearRegressionMNK);
        ui->FirstPlot->removeAction(ui->actionLinearRegressionTeylor);
    }

    ui->SecondPlot->plotLayout()->clear();
    ui->SecondPlot->plotLayout()->addElement(0, 0, new QCPAxisRect(ui->SecondPlot));
    ui->FirstPlot->clearGraphs();
    ui->SecondPlot->clearGraphs();
    ui->ThirdPlot->clearGraphs();
    ui->FirstPlot->clearItems();
    ui->SecondPlot->clearItems();
    ui->ThirdPlot->clearItems();
    ui->FirstPlot->clearPlottables();
    ui->SecondPlot->clearPlottables();
    ui->ThirdPlot->clearPlottables();
    ui->FirstPlot->clearMask();
    ui->SecondPlot->clearMask();
    ui->ThirdPlot->clearMask();
    ui->FirstPlot->clearFocus();
    ui->SecondPlot->clearFocus();
    ui->ThirdPlot->clearFocus();

    if(ui->SecondPlot->plotLayout()->hasElement(0, 1))
         ui->SecondPlot->plotLayout()->removeAt(1);
    if(ui->ThirdPlot->plotLayout()->hasElement(0, 1))
         ui->ThirdPlot->plotLayout()->removeAt(1);

    ui->FirstPlot->addGraph();
    ui->SecondPlot->addGraph();
    ui->ThirdPlot->addGraph();

    ui->FirstPlot->xAxis->setLabel("x");
    ui->FirstPlot->yAxis->setLabel("y");
    ui->SecondPlot->xAxis->setLabel("x");
    ui->SecondPlot->yAxis->setLabel("y");
    ui->ThirdPlot->xAxis->setLabel("x");
    ui->ThirdPlot->yAxis->setLabel("y");
    switch(static_cast<BaseSampleTree*>(index.internalPointer())->GetSampleType()){
    case 0:
    {
        ui->tabWidget_2->setTabText(0 ,"Гістограма");
        ui->tabWidget_2->setTabText(1 ,"Емпірична функція");
        Sample *sample = static_cast<Sample*>(index.internalPointer());
        if(parameter != NULL)
            delete parameter;
        parameter = new QParameterItemModel(sample, this);
        ui->treeView_2->setModel(parameter);
        int size = sample->division.size();
        QVector<double> x(size), y(size);
        QVector<double>  yemp(size);
        double p = 0;
        for (int i=0; i< size; ++i)
        {
          x[i] = sample->division[i]->x;
          y[i] = sample->division[i]->p;
          p += sample->division[i]->p;
          yemp[i] = p;
        }
        ui->FirstPlot->graph(0)->setData(x, y);
        ui->FirstPlot->graph(0)->setLineStyle(QCPGraph::lsStepLeft);
        ui->FirstPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCrossCircle);
        ui->FirstPlot->rescaleAxes();
        ui->FirstPlot->replot();
        ui->SecondPlot->graph(0)->setData(x, yemp);
        ui->SecondPlot->graph(0)->setLineStyle(QCPGraph::lsStepLeft);
        ui->SecondPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCrossCircle);
        ui->SecondPlot->rescaleAxes();
        ui->SecondPlot->replot();


    }
        return;
    case 1:
        {
            ui->tabWidget_2->setTabText(0 ,"Кореляційне поле");
            ui->tabWidget_2->setTabText(1 ,"Гістограма");
            ui->tabWidget_2->setTabText(2, "Графік щільності");
            ui->FirstPlot->addAction(ui->actionLinearRegressionMNK);
            ui->FirstPlot->addAction(ui->actionLinearRegressionTeylor);
            TwoDimSample *sample = static_cast<TwoDimSample*>(index.internalPointer());
            int size = sample->sample.size();
            QVector<double> x(size), y(size); // initialize with entries 0..100
            for (int i=0; i< size; ++i)
            {
              x[i] = sample->sample[i].x;
              y[i] = sample->sample[i].y;
            }
            // create graph and assign data to it:
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->graph(0)->setData(x, y);
            ui->FirstPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
            ui->FirstPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCrossCircle);
            ui->FirstPlot->xAxis->setLabel("x");
            ui->FirstPlot->yAxis->setLabel("y");
            ui->FirstPlot->rescaleAxes();
            ui->FirstPlot->replot();
        }
        {
            TwoDimSample *sample = static_cast<TwoDimSample*>(index.internalPointer());
            ui->SecondPlot->xAxis->setLabel("x");
            ui->SecondPlot->yAxis->setLabel("y");
            ui->SecondPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
            QCPColorMap *colorMap = new QCPColorMap(ui->SecondPlot->xAxis, ui->SecondPlot->yAxis);
            colorMap->data()->setSize(sample->first.class_size, sample->second.class_size);
            colorMap->data()->setRange(QCPRange(sample->first.samplesorted.first(), sample->first.samplesorted.last()),
                                       QCPRange(sample->second.samplesorted.first(), sample->second.samplesorted.last()));
            for (int i=0; i < sample->first.class_size; i++)
            {
                for(int j = 0; j < sample->second.class_size; j++)
                {
                    colorMap->data()->setCell(i, j, sample->two_dim_division[i * (sample->second.class_size + 1) + j]->p);
                }
            }
            QCPColorScale *colorScale = new QCPColorScale(ui->SecondPlot);
            ui->SecondPlot->plotLayout()->addElement(0, 1, colorScale);
            colorScale->setType(QCPAxis::atRight);
            colorMap->setColorScale(colorScale);
            colorScale->axis()->setLabel("Гістограма оцінок");
            colorMap->setGradient(QCPColorGradient::gpPolar);
            colorMap->rescaleDataRange();
            ui->SecondPlot->rescaleAxes();
            ui->SecondPlot->replot();
        }
    {
        TwoDimSample *sample = static_cast<TwoDimSample*>(index.internalPointer());
        ui->ThirdPlot->xAxis->setLabel("x");
        ui->ThirdPlot->yAxis->setLabel("y");
        ui->ThirdPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
        QCPColorMap *colorMap = new QCPColorMap(ui->ThirdPlot->xAxis, ui->ThirdPlot->yAxis);
        colorMap->data()->setSize(sample->first.class_size, sample->second.class_size);
        colorMap->data()->setRange(QCPRange(sample->first.samplesorted.first(), sample->first.samplesorted.last()),
                                   QCPRange(sample->second.samplesorted.first(), sample->second.samplesorted.last()));
        for (int i=0; i < sample->first.class_size; i++)
        {
            for(int j = 0; j < sample->second.class_size; j++)
            {
                colorMap->data()->setCell(i, j, sample->distribution[i * (sample->second.class_size + 1) + j]->p);
            }
        }
        QCPColorScale *colorScale = new QCPColorScale(ui->ThirdPlot);
        ui->ThirdPlot->plotLayout()->addElement(0, 1, colorScale);
        colorScale->setType(QCPAxis::atRight);
        colorMap->setColorScale(colorScale);
        colorScale->axis()->setLabel("Функція щільності");
        colorMap->setGradient(QCPColorGradient::gpPolar);
        colorMap->rescaleDataRange();
        ui->ThirdPlot->rescaleAxes();
        ui->ThirdPlot->replot();
    }
        return;
    default:
        return;
    }
}

void MainWindow::on_actionLinearRegressionTeylor_triggered()
{
    if(!ui->FirstPlot->graph(2)->data()->isEmpty())
        ui->FirstPlot->graph(2)->data()->clear();
    else{
        TwoDimSample *sample = static_cast<TwoDimSample*>(ui->treeView->currentIndex().internalPointer());
        QList<XY> x_y_value = sample->linear_regression->buildRegression(*sample, 1);
        int size = x_y_value.size();
        QVector<double> x(size), y(size);
        for(int i = 0; i < size; i++){
            x[i] = x_y_value[i].x;
            y[i] = x_y_value[i].y;
        }
        ui->FirstPlot->graph(2)->setData(x, y);
        ui->FirstPlot->rescaleAxes();
        ui->FirstPlot->replot();
    }
    ui->FirstPlot->rescaleAxes();
    ui->FirstPlot->replot();
}

void MainWindow::on_actionLinearRegressionMNK_triggered()
{
    if(!ui->FirstPlot->graph(1)->data()->isEmpty())
        ui->FirstPlot->graph(1)->data()->clear();
    else{
        TwoDimSample *sample = static_cast<TwoDimSample*>(ui->treeView->currentIndex().internalPointer());
        QList<XY> x_y_value = sample->linear_regression->buildRegression(*sample, 0);
        int size = x_y_value.size();
        QVector<double> x(size), y(size);
        for(int i = 0; i < size; i++){
            x[i] = x_y_value[i].x;
            y[i] = x_y_value[i].y;
        }
        ui->FirstPlot->graph(1)->setData(x, y);
    }
    ui->FirstPlot->rescaleAxes();
    ui->FirstPlot->replot();
}
