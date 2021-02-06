#include "Data/parameter.h"

Parameter::Parameter(const QString &name,const double &value,const double dispersion,const double rootMeanSquare,const double maxValue,const double minValue)
    : name(name), value(value), dispersion(dispersion), rootMeanSquare(rootMeanSquare), maxValue(maxValue), minValue(minValue){};

