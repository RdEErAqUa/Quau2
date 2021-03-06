#include "Data/sample.h"
#include "Data/division.h"

void Sample::PrimaryAnalysis(double classSize)
{
    this->class_size = classSize <= 0 ? SetClassSize(sample.size()) : classSize;
    this->variation = SetVariation();
    this->step_size = (samplesorted.last() - samplesorted.first()) / this->class_size;
    this->division = SetDivision();
    this->parameter = SetParameter();
}
QList<Variation*> Sample::SetVariation(){
    return Variation::buildVariation(samplesorted);
}

QList<Division*> Sample::SetDivision(){
    return Division::buildDivision(samplesorted, step_size, class_size);
}

QList<Parameter *> Sample::SetParameter()
{
    return Parameter::buildParameters(samplesorted, Quantile::TQuantile(0.95, samplesorted.size()));
}

double Sample::GetParameter(const QString &name) const
{
    for(Parameter *param : parameter)
        if(param->name == name)
            return param->value;
}

int Sample::RowSize() const
{
    return 0;
}

const QString Sample::GetName() const
{
    return name;
}

const QVariant Sample::ShowInfo(const int &chosenInfo) const
{
    switch(chosenInfo){
    case 0:
        return this->class_size;
    case 1:
        return "распределение";
    }
    return "hello";
}

int Sample::GetSampleType() const
{
    return 0;
}

Sample::Sample(const QString &name, const QList<double> sample) : name(name), sample(sample), samplesorted(sample)
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
