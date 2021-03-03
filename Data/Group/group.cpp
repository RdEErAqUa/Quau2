#include "Data/Group/group.h"

Group::Group() : one_dim_sample_count(0), two_dim_sample_count(0)
{
}

void Group::OneDimSampleAdd(OneDimSample &sample)
{
    one_dim_samples << &sample;
    one_dim_sample_count++;
}

bool Group::OneDimSampleRemoveAt(const int &pos)
{
    if(!(one_dim_samples.size() > pos)) return false;
    one_dim_samples.removeAt(pos);
    return true;
}

OneDimSample &Group::OneDimSampleGet(const int &pos)
{
    return *one_dim_samples.at(pos);
}

int Group::OneDimSampleCount(){
    return one_dim_sample_count;
}

void Group::TwoDimSampleAdd(TwoDimSample &sample)
{
    two_dim_samples << &sample;
    two_dim_sample_count++;
}

TwoDimSample &Group::TwoDimSampleGet(const int &pos)
{
    return *two_dim_samples.at(pos);
}

bool Group::TwoDimSampleRemoveAt(const int &pos)
{
    if(!(two_dim_samples.size() > pos)) return false;
    two_dim_samples.removeAt(pos);
    return true;
}

int Group::TwoDimSampleCount()
{
    return two_dim_sample_count;
}
void Group::NameSet(const QString &name){
    this->name = name;
}

const QVariant Group::ShowInfo(const int &chosenInfo) const
{
    return QVariant();
}

const QString Group::GetName() const
{
    return this->name;
}

int Group::RowSize() const
{
    return one_dim_sample_count + two_dim_sample_count;
}

void *Group::GetChild(const int &childId)
{
    if(childId >= one_dim_samples.size())
        return two_dim_samples.at(childId - one_dim_samples.size());
    else
        return one_dim_samples.at(childId);
}
