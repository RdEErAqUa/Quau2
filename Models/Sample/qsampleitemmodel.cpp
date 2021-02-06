#include "qsampleitemmodel.h"
#include "StreamWork.h"

QSampleItemModel::QSampleItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    Group *first = new Group();
    first->NameSet("data1");
    QList<double> fr = {1.3, 2.0, 3.1};
    Sample *sample = new Sample("hello", fr);
    first->SampleAdd(*sample);

    QList<double> fr2 = {1.3, 2.0, 3.1};
    Sample *sample2 = new Sample("hello", fr2);
    first->SampleAdd(*sample2);
    groups.append(first);
}


QModelIndex QSampleItemModel::index(int row, int column, const QModelIndex &parent) const
{
    std::cout << "index" << std::endl;
    if (!hasIndex(row, column, parent))
            return QModelIndex();

        if (!parent.isValid())
            return createIndex(row, column, groups[row]);
        if (Group * g = static_cast<Group *>(parent.internalPointer()))
            return createIndex(row, column, &g->SampleGet(row));
        return QModelIndex();
}

QModelIndex QSampleItemModel::parent(const QModelIndex &index) const
{
    std::cout << "parent" << std::endl;
    if (!index.isValid())
            return QModelIndex();

        void * p = index.internalPointer();

        for (int i = 0; i < groups.count(); ++i)
        {
            if (p == &groups[i]) return QModelIndex();
            for (int j = 0; j < groups[i]->SampleCount(); j++)
            {
                if (p == &groups[i]->SampleGet(j)) return createIndex(i, 0, groups[i]);
            }
        }

        return QModelIndex();
}

int QSampleItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
            return groups.count();
        else if (Group * g = static_cast<Group *>(parent.internalPointer()))
            return g->SampleCount();
    return 0;
}

int QSampleItemModel::columnCount(const QModelIndex &parent) const
{
    std::cout << "column" << std::endl;
    return 3;
}

QVariant QSampleItemModel::data(const QModelIndex &index, int role) const
{
    std::cout << "data" << std::endl;
    if (!index.isValid())
            return QVariant();
        if (role != Qt::DisplayRole)
            return QVariant();

        if (!index.parent().isValid())
            return static_cast<Group *>(index.internalPointer())->NameGet();

        return static_cast<Sample *>(index.internalPointer())->name;
}

void QSampleItemModel::addItem(Sample *sample, const QModelIndex &parentId)
{
    beginInsertRows(parentId, rowCount(parentId), rowCount(parentId));
    if(!parentId.isValid()) groups[0]->SampleAdd(*sample);
    static_cast<Group *>(parentId.internalPointer())->SampleAdd(*sample);
    endInsertRows();
}
