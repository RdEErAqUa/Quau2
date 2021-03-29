#ifndef HIGHERDIMSAMPLE_H
#define HIGHERDIMSAMPLE_H
#include <QList>
#include "Data/Sample/OneDimSample/onedimsample.h"
#include "Data/Sample/TwoDimSample/twodimsample.h"

class HigherDimSample : BaseSampleTree
{
public:
    HigherDimSample(const QList<QList<double>> &one_dim_values);
    QList<OneDimSample*> one_dim_samples;
    QList<QList<double>> one_dim_values;
    QList<QList<double>> correlation_matrix;
    QList<QList<Variation*>> higher_dim_variation;
    QList<TwoDimParameter*> partial_correlation;
    QList<TwoDimParameter*> multiple_correlation;
    void PrimaryAnalysis();

    QList<QList<Variation*>> SetVariation();
    QList<QList<double>> SetCorrelationMatrix();
    TwoDimParameter *SetPartial(const QList<QList<double>> &matrix, const int &index_i, const int &index_j, const QList<int> &index_c);
    double GetPartial(const QList<QList<double>> &matrix, const int &index_i, const int &index_j, const QList<int> &index_c);
    double GetPartial(const QList<QList<double>> &matrix,const int &index_i, const int &index_j, const int &index_d);

    TwoDimParameter *SetMultiple(const QList<QList<double>> &matrix, const int &index_i, const int &index_j);
    double GetMultiple(const QList<QList<double>> &matrix, const int &index_i, const int &index_j);

    double Determinant(const QList<QList<double>> &matrix, const int &index_i = -1, const int &index_j = -1);

    // BaseSampleTree interface
public:
    int RowSize() const override;
    const QString GetName() const override;
    const QVariant ShowInfo(const int &chosenInfo) const override;
    int GetSampleType() const override;
    void *GetChild(const int &childId) override;
};

#endif // HIGHERDIMSAMPLE_H
