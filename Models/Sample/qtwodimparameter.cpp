#include "qtwodimparameter.h"

QTwoDimParameter::QTwoDimParameter(TwoDimSample *two_dim_sample,QObject *parent)
    : QAbstractItemModel(parent), two_dim_sample(two_dim_sample)
{
}

QModelIndex QTwoDimParameter::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)){
            return QModelIndex();
    }

        if (!parent.isValid())
            return createIndex(row, column, two_dim_sample->parameter[row]);
        if(!parent.parent().isValid()){
            if(row == 0)
                return createIndex(row, column, &two_dim_sample->parameter[parent.row()]->value);
            if(row == 1)
                return createIndex(row, column, &two_dim_sample->parameter[parent.row()]->t_value);
            if(row == 2)
                return createIndex(row, column, &two_dim_sample->parameter[parent.row()]->t_quantile);
            if(row == 3)
                return createIndex(row, column, &two_dim_sample->parameter[parent.row()]->is_significance);
            if(row == 4)
                return createIndex(row, column, &two_dim_sample->parameter[parent.row()]->min_value);
            if(row == 5)
                return createIndex(row, column, &two_dim_sample->parameter[parent.row()]->max_value);
        }
        return QModelIndex();// FIXME: Implement me!
}

QModelIndex QTwoDimParameter::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

        void * p = index.internalPointer();

        for (int i = 0; i < two_dim_sample->parameter.count(); ++i)
        {
            if (p == &two_dim_sample->parameter[i]) return QModelIndex();
            if(p == &two_dim_sample->parameter[i]->value)return createIndex(i, 0, two_dim_sample->parameter[i]);
            if (p == &two_dim_sample->parameter[i]->t_value) return createIndex(i, 0, two_dim_sample->parameter[i]);
            if (p == &two_dim_sample->parameter[i]->is_significance) return createIndex(i, 0, two_dim_sample->parameter[i]);
            if (p == &two_dim_sample->parameter[i]->min_value) return createIndex(i, 0, two_dim_sample->parameter[i]);
            if (p == &two_dim_sample->parameter[i]->max_value) return createIndex(i, 0, two_dim_sample->parameter[i]);
            if (p == &two_dim_sample->parameter[i]->t_quantile) return createIndex(i, 0, two_dim_sample->parameter[i]);
        }

        return QModelIndex();
}

int QTwoDimParameter::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
            return two_dim_sample->parameter.size();
    if(!parent.parent().isValid())
        return 6;
    return 0;
}

int QTwoDimParameter::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant QTwoDimParameter::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();
        if (role != Qt::DisplayRole)
            return QVariant();
        if(index.column() == 0){
            if (!index.parent().isValid())
                return static_cast<TwoDimParameter *>(index.internalPointer())->name;

            if(index.row() == 0)
                return "Оцінка";
            if(index.row() == 1)
                return "Значеня статистики";
            if(index.row() == 2)
                return "Квантиль статистики";
            if(index.row() == 3)
                return "Значущість";
            if(index.row() == 4)
                return "Мінімальне";
            if(index.row() == 5)
                return "Максимальне";
            else
                return QString::number(index.row()) + " this size";
        }
        else if(index.parent().isValid() && index.row() == 3)
            return *static_cast<bool*>(index.internalPointer());
        else if(index.parent().isValid())
            return *static_cast<double*>(index.internalPointer());
        return QVariant();
}
