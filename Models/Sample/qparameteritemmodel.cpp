#include "qparameteritemmodel.h"

QParameterItemModel::QParameterItemModel(Sample* sample, QObject *parent)
    : QAbstractItemModel(parent), sample(sample)
{
}


QModelIndex QParameterItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

        if (!parent.isValid())
            return createIndex(row, column, sample->parameter[row]);
        if(!parent.parent().isValid()){
            if(row == 0)
                return createIndex(row, column, &sample->parameter[parent.row()]->value);
            if(row == 1)
                return createIndex(row, column, &sample->parameter[parent.row()]->dispersion);
            if(row == 2)
                return createIndex(row, column, &sample->parameter[parent.row()]->min_value);
            if(row == 3)
                return createIndex(row, column, &sample->parameter[parent.row()]->max_value);
        }
        return QModelIndex();
}

QModelIndex QParameterItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

        void * p = index.internalPointer();

        for (int i = 0; i < sample->parameter.count(); ++i)
        {
            if (p == &sample->parameter[i]) return QModelIndex();
            if(p == &sample->parameter[i]->value)return createIndex(i, 0, &sample->parameter[i]);
            if (p == &sample->parameter[i]->dispersion) return createIndex(i, 0, &sample->parameter[i]);
            if (p == &sample->parameter[i]->min_value) return createIndex(i, 0, &sample->parameter[i]);
            if (p == &sample->parameter[i]->max_value) return createIndex(i, 0, &sample->parameter[i]);
        }

        return QModelIndex();
}

int QParameterItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
            return sample->parameter.size();
    if(!parent.parent().isValid())
        return 4;
    return 0;
}

int QParameterItemModel::columnCount(const QModelIndex &parent) const
{
    return 2;

    // FIXME: Implement me!
}

QVariant QParameterItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();
        if (role != Qt::DisplayRole)
            return QVariant();
        if(index.column() == 0){
            if (!index.parent().isValid())
                return static_cast<Parameter *>(index.internalPointer())->name;

            if(index.row() == 0)
                return "Оцінка";
            if(index.row() == 1)
                return "Дисперсія";
            if(index.row() == 2)
                return "xMin";
            if(index.row() == 3)
                return "xMax";
        }
        else if(index.parent().isValid())
            return *static_cast<double*>(index.internalPointer());
        return QVariant();

}
