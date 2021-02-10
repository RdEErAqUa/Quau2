#include "Data/division.h"

Division::Division(const double &x, const int &n, const double &p): x(x), n(n), p(p)
{

}

QList<Division *> Division::buildDivision(const QList<double> &sample, const double &stepSize, const int &classSize){
    QList<Division*> division;
    QList<double> sampleDivision = DivisionSample(sample.first(), stepSize, classSize);
    QList<int> frequency = Frequency(sample , sampleDivision);
    QList<double> relativeFrequency = RelativeFrequency(frequency);
    for(int i = 0; i < sampleDivision.size(); i++)
    {
        division << (new Division(sampleDivision[i], frequency[i], relativeFrequency[i]));
    }
    return division;
}

QList<double> Division::DivisionSample(const double &sampleFirst, const double &stepSize, const int &classSize)
{
    QList<double> sampleDivision;
    for(int i = 0; i <= classSize; i++)
        sampleDivision << sampleFirst + (i) * (stepSize);
    return sampleDivision;
}

QList<int> Division::Frequency(const QList<double> &sample, const QList<double> &sampleDivision)
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
            else if(i + 1 == classSize && el >= sampleDivision[i + 1])
                count++;
        }
        frequency.append(count);
    }
    frequency.append(0);
    double sfg = 0;
    for(double el : frequency)
        sfg += el;
    return frequency;
}

QList<double> Division::RelativeFrequency(const QList<int> &frequency)
{
    QList<double> relativeFrequency;
    double size = 0;

    for(double el : frequency) size += el;
    for(double el : frequency) relativeFrequency.append(el / size);

    return relativeFrequency;
}
