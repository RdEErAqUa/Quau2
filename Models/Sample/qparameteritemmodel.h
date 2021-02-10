#ifndef QPARAMETERITEMMODEL_H
#define QPARAMETERITEMMODEL_H

#include <QAbstractItemModel>
#include "Data/sample.h"

class QParameterItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QParameterItemModel(Sample *sample,QObject *parent = nullptr);


    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Sample *sample;
};

#endif // QPARAMETERITEMMODEL_H
