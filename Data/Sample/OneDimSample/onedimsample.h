#ifndef ONEDIMSAMPLE_H
#define ONEDIMSAMPLE_H
#include <QList>
#include <cmath>
#include <iostream>
#include "XY.h"
#include "Variation.h"
#include "Data/division.h"
#include "Data/parameter.h"
#include "Data/basesampletree.h"

class Variation;
class Division;
class OneDimSample : BaseSampleTree
{
public:
    QString name;
    QList<double> sample;
    QList<double> samplesorted;
    QList<Variation*> variation;
    QList<Division*> division;
    QList<Parameter*> parameter;
    double step_size;
    int class_size;

    OneDimSample(const QString &name, const QList<double> sample);
    void PrimaryAnalysis(double classSize = 0);
    double SetClassSize(int size);
    QList<Variation*> SetVariation();
    QList<Division*> SetDivision();
    QList<Parameter*> SetParameter();
    double GetParameter(const QString &name) const;

    // BaseSampleTree interface
public:
    int RowSize() const override;
    const QString GetName() const override;
    const QVariant ShowInfo(const int &chosenInfo) const override;
    int GetSampleType() const override;
};

#endif // ONEDIMSAMPLE_H
