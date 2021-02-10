#include "Data/twodimdivision.h"


TwoDimDivision::TwoDimDivision(const double &X, const double &Y, const double &N, const double &P) : x(X), y(Y), n(N), p(P){}

QList<TwoDimDivision *> TwoDimDivision::buildDivision(const QList<XY> &sample, const double &sampleFirstX, const double &sampleFirstY, const double &stepSizeX, const double &stepSizeY, const int &classSizeX, const int &classSizeY){
    QList<TwoDimDivision*> division;
    QList<XY> sampleDivision = DivisionSample(sampleFirstX, sampleFirstY,
                                              stepSizeX, stepSizeY,
                                              classSizeX, classSizeY);
    QList<int> frequency = Frequency(sample, classSizeX, classSizeY , sampleDivision);
    QList<double> relativeFrequency = RelativeFrequency(frequency);
    for(int i = 0; i < sampleDivision.size(); i++)
    {
        division << (new TwoDimDivision(sampleDivision[i].x, sampleDivision[i].y, frequency[i], relativeFrequency[i]));
    }
    return division;
}

QList<XY> TwoDimDivision::DivisionSample(const double &sampleFirstX, const double &sampleFirstY, const double &stepSizeX, const double &stepSizeY, const int &classSizeX, const int &classSizeY)
{
    QList<XY> sampleDivision;
    for(int i = 0; i <= classSizeX; i++)
        for(int j = 0; j <= classSizeY; j++)
            sampleDivision << XY(sampleFirstX + i * stepSizeX, sampleFirstY + j * stepSizeY);
    return sampleDivision;
}

QList<int> TwoDimDivision::Frequency(const QList<XY> &sample, const double &classSizeX, const double &classSizeY, const QList<XY> &sampleDivision)
{
    QList<int> frequency;
    double r = 0;
    for(int i = 0; i < classSizeX; i++)
    {
        for(int j = 0; j < classSizeY; j++){
            int count = 0;
            for(XY el : sample)
            {
                if((el.x >= sampleDivision[i * (classSizeY)].x && el.x < sampleDivision[(i + 1) * (classSizeY)].x) &&
                        (el.y >= sampleDivision[j].y && el.y < sampleDivision[j + 1].y))
                {
                    r++;
                    count++;
                }
                else if(i + 1 == classSizeX && el.x >= sampleDivision[i * (classSizeY + 1)].x && (el.y >= sampleDivision[j].y && el.y < sampleDivision[j + 1].y))
                    count++;
                else if(j + 1 == classSizeX && el.y >= sampleDivision[j + 1].y && (el.x >= sampleDivision[i * (classSizeY)].x && el.x < sampleDivision[i * (classSizeY + 1)].x))
                    count++;
                else if(i + 1 == classSizeX && j + 1 == classSizeY && (el.y >= sampleDivision[i * (classSizeY + 1)].y && el.y >= sampleDivision[j + 1].y))
                    count++;
            }
            frequency << count;
        }
        frequency << 0;
    }
    for(int i = 0; i <= classSizeY; i++)
        frequency << 0;
    return frequency;
}

QList<double> TwoDimDivision::RelativeFrequency(const QList<int> &frequency)
{
    QList<double> relativeFrequency;
    double size = 0;
    for(double el : frequency) size += el;
    for(double el : frequency) relativeFrequency.append(el / size);
    return relativeFrequency;
}
