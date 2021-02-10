#include "Variation.h"

Variation::Variation(const double &x, const int &n, const double &p): x(x), n(n), p(p)
{

}

QList<Variation *> Variation::buildVariation(QList<double> &sample){
    QList<Variation*> variation;
    QList<double> sampleUnique = QListUseful::Average(sample);
    QList<int> frequency = Frequency(sample , sampleUnique);
    QList<double> relativeFrequency = RelativeFrequency(frequency);

    for(int i = 0; i < sampleUnique.size(); i++)
    {
        variation << (new Variation(sampleUnique[i], frequency[i], relativeFrequency[i]));
    }

    return variation;

}

QList<int> Variation::Frequency(const QList<double> &sample, const QList<double> &sampleUnique)
{
    QList<int> frequency;
    for(double el : sampleUnique)
    {
        int count = 0;
        for(double el2 : sample)
        {
            if(el == el2) count++;
        }
        frequency.append(count);
    }
    return frequency;
}

QList<double> Variation::RelativeFrequency(const QList<int> &frequency)
{
    QList<double> relativeFrequency;
    double size = 0;

    for(double el : frequency) size += el;
    for(double el : frequency) relativeFrequency.append(el / size);

    return relativeFrequency;
}
