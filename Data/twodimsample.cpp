#include "twodimsample.h"

TwoDimSample::TwoDimSample(QList<XY> sample, const QList<double> &first, const QList<double> &second) : sample(sample), first(Sample("first", first)), second(Sample("second", second)),
    linear_regression(new LinearRegression())
{

}

void TwoDimSample::TwoDimAnalysis(const double &classSizeX, const double &classSizeY)
{
    first.PrimaryAnalysis(classSizeX);
    second.PrimaryAnalysis(classSizeY);

    this->two_dim_division = SetDivision();
    this->splitted_sample = SplitSample();
    this->distribution = SetDistribution();
    this->parameter = SetParameter();
}

QList<XMultipleY> TwoDimSample::SplitSample()
{
    int class_size = first.class_size;
    double step_size = first.step_size;
    QList<XMultipleY> *value = new QList<XMultipleY>();
    QList<double> y_value_sample = second.sample;
    for(int i = 0; i < class_size; i++){
        QList<double> y_value;

        for(int j = 0; j < first.sample.size(); j++){
            if((first.division[i]->x - step_size / 2.0) <= first.sample[j] && (first.division[i + 1]->x - step_size / 2.0) > first.sample[j]){
                y_value.append(second.sample[j]);
            }
            else if(i + 1 == class_size && (first.division[i + 1]->x - step_size / 2.0) < first.sample[j]){
                y_value.append(second.sample[j]);
            }
        }

        XMultipleY *data = new XMultipleY(first.division[i]->x, y_value);
        value->append(*data);
    }
    return *value;
}

QList<TwoDimDivision *> TwoDimSample::SetDivision()
{
    return TwoDimDivision::buildDivision(sample, first.samplesorted.first(), second.samplesorted.first(),
                                   first.step_size, second.step_size,
                                         first.class_size, second.class_size);
}

QList<TwoDimParameter*> TwoDimSample::SetParameter()
{
    return TwoDimParameter::buildParameters(*this);
}

QList<Distribution *> TwoDimSample::SetDistribution()
{
    return Distribution::TwoDimDistributionIndependentBuild(first, second);
}

double TwoDimSample::GetParameter(const QString &name) const
{
    for(TwoDimParameter *param : parameter)
        if(param->name == name)
            return param->value;
}

int TwoDimSample::RowSize() const
{
    return 2;
}

const QString TwoDimSample::GetName() const
{
    return name;
}

const QVariant TwoDimSample::ShowInfo(const int &chosenInfo) const
{
    return "Nothing right now";
}

void *TwoDimSample::GetChild(const int &childId)
{
    switch(childId){
    case 0:
        return &first;
    case 1:
        return &second;
    }
}

int TwoDimSample::GetSampleType() const
{
    return 1;
}
