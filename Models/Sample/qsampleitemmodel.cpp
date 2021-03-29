#include "qsampleitemmodel.h"
#include "Data/StreamWork/streamwork.h"

QSampleItemModel::QSampleItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}


QModelIndex QSampleItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

        if (!parent.isValid())
            return createIndex(row, column, groups[row]);
        return createIndex(row, column, static_cast<BaseSampleTree*>(parent.internalPointer())->GetChild(row));
}

QModelIndex QSampleItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

        void * p = index.internalPointer();
        for (int i = 0; i < groups.count(); ++i)
        {
            if (p == &groups[i]) return QModelIndex();
            for (int j = 0; j < groups[i]->RowSize(); j++)
            {
                if (j < groups[i]->OneDimSampleCount() && p == &groups[i]->OneDimSampleGet(j)) return createIndex(i, 0, groups[i]);
                if (j >= groups[i]->OneDimSampleCount() && j < groups[i]->TwoDimSampleCount() && p == &groups[i]->TwoDimSampleGet(j - groups[i]->OneDimSampleCount())) return createIndex(i, 0, groups[i]);
                if (j >= groups[i]->TwoDimSampleCount() && j >= groups[i]->OneDimSampleCount() && p == &groups[i]->HigherDimSampleGet(j - groups[i]->OneDimSampleCount() - groups[i]->TwoDimSampleCount())) return createIndex(i, 0, groups[i]);
            }
            for (int j = 0; j < groups[i]->TwoDimSampleCount(); j++)
            {
                if(p == &groups[i]->TwoDimSampleGet(j).first || p == &groups[i]->TwoDimSampleGet(j).second) return createIndex(i, 0, &groups[i]->TwoDimSampleGet(j));
            }
            for(int j = 0; j < groups[i]->HigherDimSampleCount(); j++){
                for(int f = 0; f < groups[i]->HigherDimSampleGet(j).one_dim_samples.size(); f++){
                    if(p == groups[i]->HigherDimSampleGet(j).one_dim_samples[f]) return createIndex(i, 0, &groups[i]->HigherDimSampleGet(j));
                }
            }
        }

        return QModelIndex();
}

int QSampleItemModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
        return 0;
    else if (!parent.isValid())
            return groups.count();
    return static_cast<BaseSampleTree*>(parent.internalPointer())->RowSize();
}

int QSampleItemModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant QSampleItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();
        switch(role){
        case Qt::DisplayRole:
            {
                if(index.column() == 0)
                    return static_cast<BaseSampleTree*>(index.internalPointer())->GetName();
                if(index.column() == 1)
                    return static_cast<BaseSampleTree*>(index.internalPointer())->ShowInfo(0);
                if(index.column() == 2)
                    return static_cast<BaseSampleTree*>(index.internalPointer())->ShowInfo(1);
            }
        case Qt::EditRole:
            if(index.column() == 1)
                return static_cast<BaseSampleTree*>(index.internalPointer())->ShowInfo(0);
        default:
            return QVariant();
        }
}
/*
 * Вся модель построенная на принципе что если в группе i есть n одномерных выборок и m двомерных, то ВСЕГДА
 * row от 0 до n - это строчки ОДНОМЕРНЫХ ВЫБОРОК, а row от n(включительно) до n + m - это строчки ДВОМЕРНЫХ ВЫБОРОК
 * В добавлении сдвиг не предусматривается, и по-этому программа неправильно идентеицирует такие выборки при добавлении
 * В будущем нужно добавить сдвиг в добавлении, чтобы не возникло проблем при удалении выборки(или нет. 08.02.2020 моих знаний не хватало, чтобы дать на
 * это 100% ответ, может модели в qt умнее и умеют сами такой сдвиг определять)
 */
void QSampleItemModel::addItemOneDimSample(OneDimSample *sample, const QModelIndex &parentId)
{
    QModelIndex indexValue;
    if(!parentId.isValid()){
        if(!(groups.size() > 0)){
            Group *group = new Group();
            group->NameSet("data1");
            addItemGroup(group, QModelIndex());
        }
        indexValue = index(0, 0, parentId);
    }
    else indexValue = parentId;
    beginInsertRows(indexValue, rowCount(indexValue), rowCount(indexValue));
    groups[indexValue.row()]->OneDimSampleAdd(*sample);
    endInsertRows();
}

void QSampleItemModel::addItemTwoDimSample(TwoDimSample *twoDimSample, const QModelIndex &parentId)
{
    QModelIndex indexValue;
    if(!parentId.isValid()){
        if(!(groups.size() > 0)){
            Group *group = new Group();
            group->NameSet("data1");
            addItemGroup(group, QModelIndex());
        }
        indexValue = index(0, 0, parentId);
    }
    else indexValue = parentId;
    beginInsertRows(indexValue, rowCount(indexValue), rowCount(indexValue));
    groups[indexValue.row()]->TwoDimSampleAdd(*twoDimSample);
    endInsertRows();
}

void QSampleItemModel::addItemHigherDimSample(HigherDimSample *higherDimSample, const QModelIndex &parentId)
{
    QModelIndex indexValue;
    if(!parentId.isValid()){
        if(!(groups.size() > 0)){
            Group *group = new Group();
            group->NameSet("data1");
            addItemGroup(group, QModelIndex());
        }
        indexValue = index(0, 0, parentId);
    }
    else indexValue = parentId;
    beginInsertRows(indexValue, rowCount(indexValue), rowCount(indexValue));
    groups[indexValue.row()]->HigherDimSampleAdd(*higherDimSample);
    endInsertRows();
}

bool QSampleItemModel::addItemGroup(Group *group, const QModelIndex &parentId)
{
    if(parentId.isValid()) return false;
    beginInsertColumns(parentId, rowCount(parentId), rowCount(parentId));
    groups.append(group);
    endInsertRows();
    return true;
}

Qt::ItemFlags QSampleItemModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    if(static_cast<BaseSampleTree*>(index.internalPointer())->GetSampleType() == 0 && (index.column() > 0))
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool QSampleItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
        case Qt::EditRole:
            if(static_cast<BaseSampleTree*>(index.internalPointer())->GetSampleType() == 0 && index.column() == 1){
                if(static_cast<BaseSampleTree*>(index.parent().internalPointer())->GetSampleType() == 1){
                    TwoDimSample* twoDimSample = static_cast<TwoDimSample*>(index.parent().internalPointer());
                    if(index.internalPointer() == &twoDimSample->first)
                        twoDimSample->TwoDimAnalysis(value.toDouble(), twoDimSample->second.class_size);
                    else
                        twoDimSample->TwoDimAnalysis(twoDimSample->first.class_size, value.toDouble());
                }
                else{
                    static_cast<OneDimSample*>(index.internalPointer())->PrimaryAnalysis(value.toDouble());
                }
                return true;

            }
    }
    return false;
}

QVariant QSampleItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        if(section == 0)
            return "Data";
        else if(section == 1)
            return "ClassSize";
        else if(section == 2)
            return "Distribution";
    }
    else{
        return QVariant();
    }
    return QVariant();
}
