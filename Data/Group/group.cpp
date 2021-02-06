#include "Data/Group/group.h"

Group::Group() : sampleCount(0)
{
}
struct Group::SampleInfo
{
    Group *parent;
    Sample sample;

    SampleInfo(Group *parent, const Sample &sample) : parent(parent), sample(sample){}
};

void Group::SampleAdd(const Sample &sample)
{
    SampleInfo *sampleInfo = new SampleInfo(this, sample);
    samples.append(sampleInfo);
    sampleCount++;
}

bool Group::SampleRemoveAt(const int &pos)
{
    if(!(samples.size() > pos)) return false;
    samples.removeAt(pos);
    sampleCount--;
    return true;
}

Sample &Group::SampleGet(const int &pos)
{
    SampleInfo &sampleInfo = *samples.at(pos);
    return sampleInfo.sample;
}

int Group::SampleCount()
{
    return sampleCount;
}

void Group::NameSet(const QString &name){
    this->name = name;
}

QString &Group::NameGet()
{
    return this->name;
}
