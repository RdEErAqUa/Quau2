#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "Data/Sample/OneDimSample/onedimsample.h"
#include  "Data/Sample/TwoDimSample/twodimsample.h"
#include "Data/StreamWork/streamwork.h"
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
    parameter_model = nullptr;
    two_dim_parameter = nullptr;
    regression_model = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddSample_triggered()
{
    QList<double> value = StreamWork::ReadDouble(QFileDialog::getOpenFileName(this,
                                                                              tr("Open File"), tr("Text files (*.txt)")));
    QString name = "data1/sample/";
    int f = sample_model->rowCount(sample_model->index(0, 0, QModelIndex()));
    name.append(QString::number(f));
    OneDimSample *s = new OneDimSample(name, value);
    s->PrimaryAnalysis();
    sample_model->addItemOneDimSample(s, QModelIndex());
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

    if(this->parameter_model != NULL){
        delete parameter_model;
        this->parameter_model = nullptr;
    }
    if(this->two_dim_parameter != NULL){
        delete this->two_dim_parameter;
        this->two_dim_parameter = nullptr;
    }

    clear_set_basic_plot(ui->FirstPlot);
    clear_set_basic_plot(ui->SecondPlot);
    clear_set_basic_plot(ui->ThirdPlot);
    switch(static_cast<BaseSampleTree*>(index.internalPointer())->GetSampleType()){
    case 0:
    {
        ui->tabWidget_2->setTabText(0 ,"Гістограма");
        ui->tabWidget_2->setTabText(1 ,"Емпірична функція");
        OneDimSample *sample = static_cast<OneDimSample*>(index.internalPointer());
        build_sample_parameter(sample, this->parameter_model, ui->treeView_2);
        build_sample_plot(sample);
    }
        return;
    case 1:
        {
            ui->tabWidget_2->setTabText(0 ,"Кореляційне поле");
            ui->tabWidget_2->setTabText(1 ,"Гістограма");
            ui->tabWidget_2->setTabText(2, "Графік щільності");
            ui->FirstPlot->setContextMenuPolicy(Qt::CustomContextMenu);

            TwoDimSample *sample = static_cast<TwoDimSample*>(index.internalPointer());
            this->two_dim_parameter = new QTwoDimParameter(sample, this);
            ui->treeView_2->setModel(this->two_dim_parameter);
            int size = sample->sample.size();
            QVector<double> x(size), y(size); // initialize with entries 0..100
            for (int i=0; i< size; ++i)
            {
              x[i] = sample->sample[i].x;
              y[i] = sample->sample[i].y;
            }
            ui->FirstPlot->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(ui->FirstPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

            ui->FirstPlot->addGraph();
            //MNK
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            //Taylor
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            //Parabolic First
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            //Parabolic Second
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            //Pyatorichka
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            //Pyatorichka
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();
            ui->FirstPlot->addGraph();

            add_plot_data(ui->FirstPlot, x, y, QCPGraph::lsNone, QCPScatterStyle::ssCrossCircle);
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

void MainWindow::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    QSignalMapper *mapper = new QSignalMapper();
    QAction *linearMNK = new QAction("Лінійна регресія МНК");
    connect(linearMNK, SIGNAL(triggered()), &*mapper, SLOT(map()));
    mapper->setMapping(linearMNK, 0);
    QAction *linearTaylor = new QAction("Лінійна регресія Тейлора");
    connect(linearTaylor, SIGNAL(triggered()), &*mapper, SLOT(map()));
    mapper->setMapping(linearTaylor, 1);

    QAction *parabolic_first = new QAction("Параболічна регресія fast");
    connect(parabolic_first, SIGNAL(triggered()), &*mapper, SLOT(map()));
    mapper->setMapping(parabolic_first, 2);

    QAction *parabolic_second = new QAction("Параболічна регресія slower");
    connect(parabolic_second, SIGNAL(triggered()), &*mapper, SLOT(map()));
    mapper->setMapping(parabolic_second, 3);

    QAction *pyatorichka = new QAction("5-варіант регресія");
    connect(pyatorichka, SIGNAL(triggered()), &*mapper, SLOT(map()));
    mapper->setMapping(pyatorichka, 4);

    QAction *pyatorichka_without = new QAction("5-варіант регресія без");
    connect(pyatorichka_without, SIGNAL(triggered()), &*mapper, SLOT(map()));
    mapper->setMapping(pyatorichka_without, 5);

    connect(&*mapper, SIGNAL(mapped(int)), this, SLOT(AddRegression(int)));

    menu->addAction(linearMNK);
    menu->addAction(linearTaylor);
    menu->addAction(parabolic_first);
    menu->addAction(parabolic_second);
    menu->addAction(pyatorichka);
    menu->addAction(pyatorichka_without);

    menu->exec(ui->FirstPlot->mapToGlobal(pos));
}

void MainWindow::AddRegression(int regression_value)
{
    double need_regression_value = 7;
    regression_value *= need_regression_value;
    double regression_value_previous = regression_value / need_regression_value;
    bool need_to_continue = false;
    for(int i = 0; i < need_regression_value; i++){
        if(!ui->FirstPlot->graph(regression_value + i + 1)->data()->isEmpty()){
            ui->FirstPlot->graph(regression_value + i + 1)->data()->clear();
            continue;
        }
        if(i == 0) {need_to_continue = true; break;}
    }
    if(need_to_continue){
        TwoDimSample *sample = static_cast<TwoDimSample*>(ui->treeView->currentIndex().internalPointer());
        QList<XY> x_y_value;
        QList<XY> conf_value_min;
        QList<XY> conf_value_max;
        QList<XY> toler_value_min;
        QList<XY> toler_value_max;
        QList<XY> conf_new_value_min;
        QList<XY> conf_new_value_max;
        if(regression_value_previous < 2){
            x_y_value = sample->linear_regression->buildRegression(*sample, (regression_value / need_regression_value));
            sample->AddRegression(regression_value, x_y_value, sample->linear_regression->buildLinearParameter(*sample, (regression_value / need_regression_value)));
        }
        else if(regression_value_previous < 4){
            x_y_value = sample->parabolic_regression->buildRegression(*sample, (regression_value / need_regression_value) - 2);
            sample->AddRegression(regression_value, x_y_value, sample->parabolic_regression->buildParabolicParameter(*sample, (regression_value / need_regression_value) - 2));

            double error_value = (regression_value / need_regression_value) - 2 == 0 ? sample->parabolic_regression->error_first : sample->parabolic_regression->error_second;
            if(sample->GetRegression(regression_value).min_confidence_interval.isEmpty())
                conf_value_min = sample->GetRegression(regression_value).min_confidence_interval = sample->parabolic_regression->MinConfidenceInterval(x_y_value, error_value, *sample);
            else
                conf_value_min = sample->GetRegression(regression_value).min_confidence_interval;
            if(sample->GetRegression(regression_value).max_confidence_interval.isEmpty())
                conf_value_max = sample->GetRegression(regression_value).max_confidence_interval = sample->parabolic_regression->MaxConfidenceInterval(x_y_value, error_value, *sample);
            else
                conf_value_max = sample->GetRegression(regression_value).max_confidence_interval;
            if(sample->GetRegression(regression_value).min_tolerance_interval.isEmpty())
                toler_value_min = sample->GetRegression(regression_value).min_tolerance_interval = sample->parabolic_regression->MinToleranceInterval(x_y_value, error_value, *sample);
            else
                toler_value_min = sample->GetRegression(regression_value).min_tolerance_interval;
            if(sample->GetRegression(regression_value).max_tolerance_interval.isEmpty())
                toler_value_max = sample->GetRegression(regression_value).max_tolerance_interval = sample->parabolic_regression->MaxToleranceInterval(x_y_value, error_value, *sample);
            else
                toler_value_max = sample->GetRegression(regression_value).max_tolerance_interval;
            //
            if(sample->GetRegression(regression_value).min_new_confidence_interval.isEmpty())
                conf_new_value_max = sample->GetRegression(regression_value).min_new_confidence_interval = sample->parabolic_regression->MinNewConfidenceInterval(x_y_value, error_value, *sample);
            else
                conf_new_value_max = sample->GetRegression(regression_value).min_new_confidence_interval;
            if(sample->GetRegression(regression_value).max_new_confidence_interval.isEmpty())
                conf_new_value_min = sample->GetRegression(regression_value).max_new_confidence_interval = sample->parabolic_regression->MaxNewConfidenceInterval(x_y_value, error_value, *sample);
            else
                conf_new_value_min = sample->GetRegression(regression_value).max_new_confidence_interval;
        }
        else{
            bool should_use = regression_value_previous == 5 ? false : true;
            x_y_value = sample->pyatorichka_regression->buildFirst(*sample, should_use);
            sample->AddRegression(regression_value, x_y_value, sample->pyatorichka_regression->buildPyatorichkaParameter(*sample));

            if(sample->GetRegression(regression_value).min_confidence_interval.isEmpty())
                conf_value_min = sample->GetRegression(regression_value).min_confidence_interval = sample->pyatorichka_regression->MinConfidenceInterval(x_y_value, *sample);
            else
                conf_value_min = sample->GetRegression(regression_value).min_confidence_interval;
            if(sample->GetRegression(regression_value).max_confidence_interval.isEmpty())
                conf_value_max = sample->GetRegression(regression_value).max_confidence_interval = sample->pyatorichka_regression->MaxConfidenceInterval(x_y_value, *sample);
            else
                conf_value_max = sample->GetRegression(regression_value).max_confidence_interval;
        }
        int size = x_y_value.size();
        QVector<double> x(size), y(size), conf_max(size), conf_min(size), toler_max(size), toler_min(size), new_conf_max(size), new_conf_min(size);
        for(int i = 0; i < size; i++){
            x[i] = x_y_value[i].x;
            y[i] = x_y_value[i].y;
            if(conf_value_max.size() > 0){
                conf_max[i] = conf_value_max[i].y;
                conf_min[i] = conf_value_min[i].y;
            }
            if(toler_value_max.size() > 0){
                toler_max[i] = toler_value_max[i].y;
                toler_min[i] = toler_value_min[i].y;
            }
            if(conf_new_value_min.size() > 0){
                new_conf_max[i] = conf_value_max[i].y;
                new_conf_min[i] = conf_value_min[i].y;
            }
        }
        QPen pen;
        pen.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));
        ui->FirstPlot->graph(regression_value + 1)->setData(x, y);
        ui->FirstPlot->graph(regression_value + 1)->setPen(pen);
        ui->FirstPlot->graph(regression_value + 1)->setScatterStyle(QCPScatterStyle::ssCrossCircle);

        //
        pen.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));
        ui->FirstPlot->graph(regression_value + 2)->setData(x, conf_max);
        ui->FirstPlot->graph(regression_value + 2)->setPen(pen);

        ui->FirstPlot->graph(regression_value + 3)->setData(x, conf_min);
        ui->FirstPlot->graph(regression_value + 3)->setPen(pen);

        pen.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));
        ui->FirstPlot->graph(regression_value + 4)->setData(x, toler_max);
        ui->FirstPlot->graph(regression_value + 4)->setPen(pen);

        ui->FirstPlot->graph(regression_value + 5)->setData(x, toler_min);
        ui->FirstPlot->graph(regression_value + 5)->setPen(pen);

        pen.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));
        ui->FirstPlot->graph(regression_value + 6)->setData(x, new_conf_max);
        ui->FirstPlot->graph(regression_value + 6)->setPen(pen);

        ui->FirstPlot->graph(regression_value + 7)->setData(x, new_conf_min);
        ui->FirstPlot->graph(regression_value + 7)->setPen(pen);

        //


        if(regression_model != nullptr)
            delete regression_model;
        regression_model = new QRegressionTableModel(sample->GetAllRegressionParameter(), this);
        ui->tableView->setModel(regression_model);
    }
    ui->FirstPlot->rescaleAxes();
    ui->FirstPlot->replot();
}

void MainWindow::clear_plot(QCustomPlot *customPlot)
{
    customPlot->plotLayout()->clear();
    customPlot->plotLayout()->addElement(0, 0, new QCPAxisRect(customPlot));
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearPlottables();
    customPlot->clearMask();
    customPlot->clearFocus();
}

void MainWindow::set_basic_plot(QCustomPlot *customPlot)
{
    customPlot->addGraph();

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
}

void MainWindow::clear_set_basic_plot(QCustomPlot *customPlot)
{
    clear_plot(customPlot);
    set_basic_plot(customPlot);
}

void MainWindow::add_plot_data(QCustomPlot *customPlot, QVector<double> x, QVector<double> y, QCPGraph::LineStyle lineStyle
        , QCPScatterStyle::ScatterShape scatterStyle)
{
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(0)->setLineStyle(lineStyle);
    customPlot->graph(0)->setScatterStyle(scatterStyle);
    customPlot->rescaleAxes();
    customPlot->replot();
}

void MainWindow::build_sample_plot(OneDimSample *sample)
{
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
    add_plot_data(ui->FirstPlot, x, y, QCPGraph::lsStepLeft, QCPScatterStyle::ssCrossCircle);
    add_plot_data(ui->SecondPlot, x, yemp, QCPGraph::lsStepLeft, QCPScatterStyle::ssCrossCircle);
}

void MainWindow::build_sample_parameter(OneDimSample *sample, QParameterItemModel *_parameter, QAbstractItemView *item)
{
    if(_parameter != NULL)
        delete _parameter;
    _parameter = new QParameterItemModel(sample, this);
    item->setModel(_parameter);
}
