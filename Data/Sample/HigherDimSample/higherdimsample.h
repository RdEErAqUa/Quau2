#ifndef HIGHERDIMSAMPLE_H
#define HIGHERDIMSAMPLE_H
#include <QList>
#include "Data/Sample/OneDimSample/onedimsample.h"

class HigherDimSample
{
public:
    HigherDimSample(const QList<QList<double>> &one_dim_values);
    QList<OneDimSample*> one_dim_samples;
    QList<QList<double>> one_dim_values;
    QList<QList<Variation*>> higher_dim_variation;
    void PrimaryAnalysis();

    QList<QList<Variation*>> SetVariation();

};

#endif // HIGHERDIMSAMPLE_H
