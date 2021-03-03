#ifndef TWODIMSAMPLE_H
#define TWODIMSAMPLE_H
#include "Data/Sample/OneDimSample/onedimsample.h"
#include "XY.h"
#include "Data/basesampletree.h"
#include "Data/twodimdivision.h"
#include "Data/distribution.h"
#include "Data/xmultipley.h"
#include "Data/Sample/TwoDimSample/twodimparameter.h"
#include "Data/Sample/TwoDimSample/Regression/linearregression.h"
#include "Data/Sample/TwoDimSample/Regression/parabolicregression.h"
#include "Data/Sample/TwoDimSample/Regression/Storage/regression.h"
#include "Data/Sample/TwoDimSample/Regression/pyatorichkaregression.h"

class TwoDimDivision;
class Distribution;
class TwoDimParameter;
class LinearRegression;
class ParabolicRegression;
class PyatorichkaRegression;
class Regression;
class TwoDimSample : public BaseSampleTree
{
public:
    TwoDimSample(QList<XY> sample, const QList<double> &first, const QList<double> &second);

    QList<XY> sample;
    QList<XMultipleY> splitted_sample;
    QList<TwoDimDivision*> two_dim_division;
    QList<TwoDimParameter*> parameter;
    QList<Distribution*> distribution;
    QList<Regression*> regression_data;

    LinearRegression *linear_regression;
    ParabolicRegression *parabolic_regression;
    PyatorichkaRegression *pyatorichka_regression;

    void TwoDimAnalysis(const double &classSizeX = 0, const double &classSizeY = 0);

    QList<XMultipleY> SplitSample();
    QList<TwoDimDivision*> SetDivision();
    QList<TwoDimParameter*> SetParameter();
    QList<Distribution*> SetIndependentDistribution();
    QList<Distribution*> SetDistribution();
    double GetValueParameter(const QString &name) const;
    TwoDimParameter &GetParameter(const QString &name);
    Regression& GetRegression(const int &regression_type);

    QList<TwoDimParameter*> &GetRegressionParameter(const int &regression_type);
    QList<TwoDimParameter*> &GetAllRegressionParameter();
    bool AddRegression(const int &regression_type, const QList<XY> &regression_value, QList<TwoDimParameter*> parameter);

    OneDimSample first;
    OneDimSample second;
    QString name;


public:
    int RowSize() const override;
    const QString GetName() const override;
    const QVariant ShowInfo(const int &chosenInfo) const override;
    void *GetChild(const int &childId) override;
    int GetSampleType() const override;
};

#endif // TWODIMSAMPLE_H
