#include "Data/distribution.h"


Distribution::Distribution(const double &x, const double &y, const double &p) : x(x), y(y), p(p){}

QList<Distribution *> Distribution::TwoDimDistributionIndependentBuild(OneDimSample &first, OneDimSample &second){
    QList<Distribution *> returnValue;
    for(int i = 0; i <= first.class_size; i++){
        for(int j = 0; j <= second.class_size; j++){
            returnValue << new Distribution(first.division[i]->x, second.division[j]->x,
                                            TwoDimDistributionIndependentValue(first.GetParameter("Dispersion"), second.GetParameter("Dispersion"),
                                                                               first.division[i]->x, second.division[j]->x,
                                                                               first.GetParameter("Average"), second.GetParameter("Average")) * first.step_size * second.step_size);
        }
    }
    return returnValue;
}

double Distribution::TwoDimDistributionIndependentValue(const double &_firstDispersion, const double &_secondDispersion, const double &_x, const double &_y, const double &_xAverage, const double &_yAverage){
    return 1.0 / (2.0 * 3.14 * _firstDispersion * _secondDispersion) * exp(-1.0 / 2.0 * (pow((_x - _xAverage)/_firstDispersion, 2.0 )
                                                                                         + pow((_y - _yAverage) / _secondDispersion, 2.0)));
}

QList<Distribution *> Distribution::TwoDimDistributionBuild(OneDimSample &first, OneDimSample &second, double correlationCoefficient){
    QList<Distribution *> returnValue;
    for(int i = 0; i <= first.class_size; i++){
        for(int j = 0; j <= second.class_size; j++){
            returnValue << new Distribution(first.division[i]->x, second.division[j]->x,
                                            TwoDimDistributionValue(first.GetParameter("Dispersion"), second.GetParameter("Dispersion"),
                                                                               first.division[i]->x, second.division[j]->x,
                                                                               first.GetParameter("Average"), second.GetParameter("Average"), correlationCoefficient) * first.step_size * second.step_size);
        }
    }
    return returnValue;
}

double Distribution::TwoDimDistributionValue(const double &_firstDispersion, const double &_secondDispersion, const double &_x, const double &_y,
                                             const double &_xAverage, const double &_yAverage, const double &correlationCoefficient){
    double correlationCoefficientSquare = correlationCoefficient * correlationCoefficient;
    return 1.0 / (2.0 * 3.14 * _firstDispersion * _secondDispersion * sqrt(1.0 - correlationCoefficientSquare)) *
            exp(-1.0 / (2.0 * (1.0 - correlationCoefficientSquare)) * (pow((_x - _xAverage)/_firstDispersion, 2.0 )
                + pow((_y - _yAverage) / _secondDispersion, 2.0)) + 2.0 * correlationCoefficient *((_x - _xAverage) / (_firstDispersion))* (_y - _yAverage) / _secondDispersion);
}
