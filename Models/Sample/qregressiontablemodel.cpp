#include "qregressiontablemodel.h"

QRegressionTableModel::QRegressionTableModel(const QList<TwoDimParameter*> parameter,QObject *parent)
    : QAbstractTableModel(parent), parameter(parameter)
{
}

QVariant QRegressionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        if(section == 0)
            return "Параметр";
        else if(section == 1)
            return "Значення";
        else if(section == 2)
            return "Т-статистика";
        else if(section == 3)
            return "Т-квантиль";
        else if(section == 4)
            return "Значущість";
        else if(section == 5)
            return "Мінімальне";
        else if(section == 6)
            return "Максимальне";
    }
    else{
        return QVariant();
    }
    return QVariant();
}

int QRegressionTableModel::rowCount(const QModelIndex &parent) const
{
    return parameter.size();
}

int QRegressionTableModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}

QVariant QRegressionTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();
    TwoDimParameter *param = parameter.at(index.row());

    switch(index.column()){
    case 0:
        return param->ua_name;
    case 1:
        return param->value;
    case 2:
        return param->t_value;
    case 3:
        return param->t_quantile;
    case 4:
        return param->is_significance;
    case 5:
        return param->min_value;
    case 6:
        return param->max_value;
    }

    return QVariant();
}
