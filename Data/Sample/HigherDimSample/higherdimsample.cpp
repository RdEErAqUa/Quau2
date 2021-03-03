#include "higherdimsample.h"

HigherDimSample::HigherDimSample(const QList<QList<double>> &one_dim_values) : one_dim_values(one_dim_values)
{

}

void HigherDimSample::PrimaryAnalysis()
{
    higher_dim_variation = SetVariation();
}

QList<QList<Variation*> > HigherDimSample::SetVariation()
{
    int size_samples = 0;

    QList<QList<Variation*>> variation = QList<QList<Variation*>>();
    foreach(OneDimSample *el, one_dim_samples)
        size_samples += el->sample.size();
    foreach(OneDimSample *el, one_dim_samples){
        QList<Variation*> el_variation = QList<Variation*>();
        foreach(Variation *el_2, el->variation)
            el_variation.append(new Variation(el_2->x, el_2->n, (double)(el_2->n) / (double)(size_samples)));
        variation.append(el_variation);
    }
    return variation;
}
