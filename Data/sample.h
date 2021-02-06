#ifndef SAMPLE_H
#define SAMPLE_H
#include <QString>
#include <QList>
#include <cmath>
#include <iostream>
#include "XY.h"
#include "Variation.h"
#include "Data/division.h"
#include "Data/parameter.h"

struct Sample
{
    QString name;
    QList<double> sample;
    QList<double> samplesorted;
    QList<Variation*> variation;
    QList<Division*> division;
    double stepSize;
    int classSize;

    Sample(const QString &name, const QList<double> &sample);
    void PrimaryAnalysis(double classSize = 0);
    double SetClassSize(int size);
    QList<Variation*> SetVariation();
    QList<Division*> SetDivision();
    QList<Parameter*> SetParameter();

};
#endif // SAMPLE_H
