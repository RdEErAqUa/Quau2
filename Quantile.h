#ifndef QUANTILE_H
#define QUANTILE_H

#include <cmath>

class Quantile
{
public:
    static double UQuantile(const double &a);
    static double TQuantile(const double &a, const int &v1);
    static double XiQUnatile(const double &a, const double &v1);

    static double FQuantile(const double &a, const double &v1, const double &v2);
};

#endif // QUANTILE_H
