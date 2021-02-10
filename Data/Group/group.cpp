#include "Data/Group/group.h"

Group::Group() : sample_count(0), two_dim_sample_count(0)
{
}
struct Group::SampleInfo
{
    Group *parent;
    Sample sample;
    TwoDimSample twoDimSample;

    SampleInfo(Group *parent, const Sample &sample, const TwoDimSample *twoDimSample = nullptr) : parent(parent), sample(sample), twoDimSample(*twoDimSample){}
    SampleInfo(Group *parent, const TwoDimSample &twoDimSample, const Sample *sample = nullptr) : parent(parent), sample(*sample),twoDimSample(twoDimSample){}
};

void Group::SampleAdd(Sample &sample)
{
    samples << &sample;
    sample_count++;
}

bool Group::SampleRemoveAt(const int &pos)
{
    if(!(samples.size() > pos)) return false;
    samples.removeAt(pos);
    return true;
}

Sample &Group::SampleGet(const int &pos)
{
    return *samples.at(pos);
}

int Group::SampleCount(){
    return sample_count;
}

void Group::TwoSampleAdd(TwoDimSample &sample)
{
    two_dim_samples << &sample;
    two_dim_sample_count++;
}

TwoDimSample &Group::TwoSampleGet(const int &pos)
{
    return *two_dim_samples.at(pos);
}

bool Group::TwoSampleRemoveAt(const int &pos)
{
    if(!(two_dim_samples.size() > pos)) return false;
    two_dim_samples.removeAt(pos);
    return true;
}

int Group::TwoSampleCount()
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
    return sample_count + two_dim_sample_count;
}

void *Group::GetChild(const int &childId)
{
    if(childId >= samples.size())
        return two_dim_samples.at(childId - samples.size());
    else
        return samples.at(childId);
}
