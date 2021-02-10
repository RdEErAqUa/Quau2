#ifndef TWODIMSAMPLE_H
#define TWODIMSAMPLE_H
#include "sample.h"
#include "XY.h"
#include "basesampletree.h"
#include "twodimdivision.h"
#include "distribution.h"
#include "xmultipley.h"
#include "twodimparameter.h"
#include "linearregression.h"

class TwoDimDivision;
class Distribution;
class TwoDimParameter;
class LinearRegression;
class TwoDimSample : public BaseSampleTree
{
public:
    TwoDimSample(QList<XY> sample, const QList<double> &first, const QList<double> &second);

    QList<XY> sample;
    QList<XMultipleY> splitted_sample;
    QList<TwoDimDivision*> two_dim_division;
    QList<TwoDimParameter*> parameter;
    QList<Distribution*> distribution;

    LinearRegression *linear_regression;

    void TwoDimAnalysis(const double &classSizeX = 0, const double &classSizeY = 0);

    QList<XMultipleY> SplitSample();
    QList<TwoDimDivision*> SetDivision();
    QList<TwoDimParameter*> SetParameter();
    QList<Distribution*> SetDistribution();
    double GetParameter(const QString &name) const;

    Sample first;
    Sample second;
    QString name;


public:
    int RowSize() const override;
    const QString GetName() const override;
    const QVariant ShowInfo(const int &chosenInfo) const override;
    void *GetChild(const int &childId) override;
    int GetSampleType() const override;
};

#endif // TWODIMSAMPLE_H
