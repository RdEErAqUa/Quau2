#ifndef QREGRESSIONTABLEMODEL_H
#define QREGRESSIONTABLEMODEL_H

#include <QAbstractTableModel>
#include "Data/Sample/TwoDimSample/twodimsample.h"

class QRegressionTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QRegressionTableModel(const QList<TwoDimParameter*> parameter, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<TwoDimParameter*> parameter;
};

#endif // QREGRESSIONTABLEMODEL_H
