#ifndef GROUP_H
#define GROUP_H
#include "Data/sample.h"
#include "Data/twodimsample.h"

class Group : BaseSampleTree
{
public:
    struct SampleInfo;
    Group();

    void SampleAdd(Sample &sample);
    bool SampleRemoveAt(const int &pos);
    Sample &SampleGet(const int &pos);
    int SampleCount();

    void TwoSampleAdd(TwoDimSample &sample);
    TwoDimSample &TwoSampleGet(const int &pos);
    bool TwoSampleRemoveAt(const int &pos);
    int TwoSampleCount();

    void NameSet(const QString &name);

private:
    QString name;
    QList<Sample*> samples;
    QList<TwoDimSample*> two_dim_samples;
    int sample_count;
    int two_dim_sample_count;

    // BaseSampleTree interface
public:
    const QVariant ShowInfo(const int &chosenInfo) const override;
    const QString GetName() const override;
    int RowSize() const override;
    void *GetChild(const int &childId) override;
};

#endif // GROUP_H
