#ifndef QUANTILE_H
#define QUANTILE_H

#include <cmath>

struct Quantile
{
    static double UQuantile(const double &a){
        double c0 = 2.515517, c1 = 0.802853, c2 = 0.010328;
        double d1 = 1.432788, d2 = 0.1892659, d3 = 0.001308;
        double p = a <= 0.5 ?  a : 1.0 - a;
        double t = sqrt(log(1.0 / pow(p, 2.0)));
        t = t - (c0 + c1 * t + c2 * t * t) / (1.0 + d1 * t + d2 * t * t + d3 * t * t * t);
        return t;
    }
    static double TQuantile(const double &a, const int &v1)
    {
        double u = UQuantile(a / 2.0);
        double g1 = 1.0 / 4.0 * (pow(u, 3.0) + u);
        double g2 = 1.0 / 96.0 * (5 * pow(u, 5.0) + 16 * pow(u, 3) + 3 * u);
        double g3 = 1.0 / 384.0 * (3 * pow(u, 7.0) + 19 * pow(u, 5) + 17 * pow(u, 3) - 15 * u);
        double g4 = 1.0 / 92160.0 * (79 * pow(u, 9.0) + 779 * pow(u, 7) + 1482 * pow(u, 5) - 1920 * pow(u, 3) -  945 * u);
        return u + 1.0 / v1 * g1 + 1.0 / pow(v1, 2) * g2 + 1.0 / pow(v1, 3) * g3 + 1.0 / pow(v1, 4) * g4;
    }
    static double XiQUnatile(const double &a, const double &v1)
    {
        double u = UQuantile(a);
        return v1 * pow(1.0 - 2.0 / (9.0 * v1) + u * sqrt(2.0 / (9.0 * v1)), 3.0);
    }

    static double FQuantile(const double &a, const double &v1, const double &v2)
    {
        double o = 1.0 / v1 + 1.0 / v2;
        double d = 1.0 / v1 - 1.0 / v2;
        double u = UQuantile(a);
        double sqrto = sqrt(o / 2);
        double z = u * sqrto - 1.0/6.0 * d * (pow(u, 2.0) + 2.0) + sqrto * (o / 24.0 * (pow(u, 2) + 3 * u) + 1/72.0 * pow(d, 2) / o * (pow(u, 3) + 11 * u))-
                (d * o) / 120 * (pow(u, 4) + 9 * pow(u, 2) + 8) + pow(d, 3) / (3240 * o) * (3 * pow(u, 4) + 7 * pow(u, 2) - 16) - sqrto *
                (pow(o, 2) / 1920 * (pow(u, 5) + 20 * pow(u, 3) + 15 * u) + pow(d, 4) / 2880 * (pow(u, 5) + 44 * pow(u, 3) + 183 * u) + pow(d, 4) / (155520 * pow(o, 2)) *
                 (9 * pow(u, 5) - 284 * pow(u, 3) - 1513 * u));
        return exp(2 * z);
    }
};

#endif // QUANTILE_H
