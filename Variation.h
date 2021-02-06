#ifndef VARIATION_H
#define VARIATION_H
#include <QList>
#include "Data/sample.h"
#include "QListUseful.h"

struct Variation
{
    double x;
    int n;
    double p;

    Variation(const double &x, const int &n, const double &p): x(x), n(n), p(p)
    {

    }

    static QList<Variation*> buildVariation(QList<double> &sample){
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

    static QList<int> Frequency(const QList<double> &sample, const QList<double> &sampleUnique)
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

    static QList<double> RelativeFrequency(const QList<int> &frequency)
    {
        QList<double> relativeFrequency;
        double size = 0;

        for(double el : frequency) size += el;
        for(double el : frequency) relativeFrequency.append(el / size);

        return relativeFrequency;
    }
};

#endif // VARIATION_H
