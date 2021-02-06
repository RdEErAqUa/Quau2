#ifndef DIVISION_H
#define DIVISION_H
#include "Data/sample.h"

struct Division
{
    double x;
    int n;
    double p;

    Division(const double &x, const int &n, const double &p): x(x), n(n), p(p)
    {

    }

    static QList<Division*> buildDivision(QList<double> &sample, double &stepSize, int &classSize){
        QList<Division*> division;
        QList<double> sampleDivision = DivisionSample(sample.first(), sample.last(), stepSize, classSize);
        QList<int> frequency = Frequency(sample , sampleDivision);
        QList<double> relativeFrequency = RelativeFrequency(frequency);
        for(int i = 0; i < sampleDivision.size(); i++)
        {
            division << (new Division(sampleDivision[i], frequency[i], relativeFrequency[i]));
        }

        return division;
    }

    static QList<double> DivisionSample(const double &sampleFirst, const double &sampleLast,const double &stepSize, const int &classSize)
    {
        QList<double> sampleDivision;

        for(int i = 0; i < classSize; i++)
            sampleDivision << sampleFirst + i * stepSize;
        sampleDivision << sampleLast;
        return sampleDivision;

    }

    static QList<int> Frequency(const QList<double> &sample, const QList<double> &sampleDivision)
    {
        QList<int> frequency;
        int classSize = sampleDivision.size() - 1;
        for(int i = 0; i < classSize; i++)
        {
            int count = 0;
            for(double el : sample)
            {
                if(el >= sampleDivision[i] && el < sampleDivision[i + 1])
                    count++;
            }
            frequency.append(count);
        }
        frequency.append(0);
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

#endif // DIVISION_H
