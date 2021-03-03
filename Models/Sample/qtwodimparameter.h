#ifndef QTWODIMPARAMETER_H
#define QTWODIMPARAMETER_H

#include <QAbstractItemModel>
#include "Data/Sample/TwoDimSample/twodimparameter.h"

class QTwoDimParameter : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QTwoDimParameter(TwoDimSample *two_dim_sample,QObject *parent = nullptr);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    TwoDimSample *two_dim_sample;
};

#endif // QTWODIMPARAMETER_H
