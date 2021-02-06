#ifndef GROUP_H
#define GROUP_H
#include "Data/sample.h"

class Group
{
public:
    struct SampleInfo;
    Group();

    void SampleAdd(const Sample &sample);
    void SampleRemove(const Sample &sample);
    bool SampleRemoveAt(const int &pos);
    Sample &SampleGet(const int &pos);
    int SampleCount();

    void NameSet(const QString &name);
    QString &NameGet();

private:
    QString name;
    QList<SampleInfo*> samples;
    int sampleCount;
};

#endif // GROUP_H
