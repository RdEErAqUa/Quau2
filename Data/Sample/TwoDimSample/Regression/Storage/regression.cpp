#include "regression.h"

Regression::Regression(const int &regression_type, const QList<XY> &regression_value, QList<TwoDimParameter*> parameter) :
    regression_type(regression_type), regression_value(regression_value), parameter(parameter)
{

}
