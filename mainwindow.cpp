#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "Data/sample.h"
#include "StreamWork.h"
#include "Models/Sample/qsampleitemmodel.h"

#define F_NAME "objectName"
#define F_AGE "age"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sampleModel = new QSampleItemModel(this);
    ui->treeView->setModel(sampleModel);
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
    QModelIndex fg = sampleModel->index(0, 0, QModelIndex());
    int f = sampleModel->rowCount(QModelIndex());
    name.append(QString::number(f));
    Sample *s = new Sample(name, value);
    s->PrimaryAnalysis();
    sampleModel->addItem(s, QModelIndex());

}
