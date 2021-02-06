#include "Data/sample.h"
#include "Data/division.h"

void Sample::PrimaryAnalysis(double classSize)
{
    this->classSize = classSize <= 0 ? SetClassSize(sample.size()) : classSize;
    this->variation = SetVariation();
    this->stepSize = (samplesorted.last() - samplesorted.first()) / this->classSize;
    this->division = SetDivision();
}
QList<Variation*> Sample::SetVariation(){
    return Variation::buildVariation(samplesorted);
}

QList<Division*> Sample::SetDivision(){
    return Division::buildDivision(samplesorted, stepSize, classSize);
}

Sample::Sample(const QString &name, const QList<double> &sample) : name(name), sample(sample), samplesorted(sample)
{
    qSort(samplesorted.begin(), samplesorted.end());
}
double Sample :: SetClassSize(int size){
    if(size < 100){
        switch(size % 2)
        {
            case 0:
            return sqrt(size) - 1;
            break;
        case 1:
            return sqrt(size);
            break;
        default:
            break;
        }
    }
    else{
        switch(size % 2)
        {
        case 0:
            return sqrt(size) - 1;
            break;
        case 1:
            return sqrt(size);
            break;
        default:
            break;
        }
    }
    return 0;
}
