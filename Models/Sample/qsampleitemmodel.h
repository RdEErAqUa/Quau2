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

    void addItemOneDimSample(OneDimSample *sample, const QModelIndex &parentId);
    void addItemTwoDimSample(TwoDimSample *twoDimSample, const QModelIndex &parentId);
    bool addItemGroup(Group *group, const QModelIndex &parentId);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected:
    QList<Group*> groups;
};

#endif // QSAMPLEITEMMODEL_H
