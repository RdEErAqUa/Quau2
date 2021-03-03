#ifndef GROUP_H
#define GROUP_H
#include "Data/Sample/OneDimSample/onedimsample.h"
#include "Data/Sample/TwoDimSample/twodimsample.h"
class Group : BaseSampleTree
{
public:
    Group();

    void OneDimSampleAdd(OneDimSample &sample);
    bool OneDimSampleRemoveAt(const int &pos);
    OneDimSample &OneDimSampleGet(const int &pos);
    int OneDimSampleCount();

    void TwoDimSampleAdd(TwoDimSample &sample);
    TwoDimSample &TwoDimSampleGet(const int &pos);
    bool TwoDimSampleRemoveAt(const int &pos);
    int TwoDimSampleCount();

    void NameSet(const QString &name);

private:
    QString name;
    QList<OneDimSample*> one_dim_samples;
    QList<TwoDimSample*> two_dim_samples;
    int one_dim_sample_count;
    int two_dim_sample_count;

    // BaseSampleTree interface
public:
    const QVariant ShowInfo(const int &chosenInfo) const override;
    const QString GetName() const override;
    int RowSize() const override;
    void *GetChild(const int &childId) override;
};

#endif // GROUP_H
