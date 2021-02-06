#ifndef QSAMPLEITEMMODEL_H
#define QSAMPLEITEMMODEL_H

#include <QAbstractItemModel>
#include "Data/Group/group.h"

class QSampleItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
     QSampleItemModel(QObject *parent = nullptr);
    // Header:
    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addItem(Sample *sample, const QModelIndex &parentId);

protected:
    QList<Group*> groups;

};

#endif // QSAMPLEITEMMODEL_H
