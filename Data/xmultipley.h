#ifndef XMULTIPLEY_H
#define XMULTIPLEY_H

#include "QList"

class XMultipleY{
public:
    double x;
    QList<double> y;

    XMultipleY(const double &x, const QList<double> &y);
};

#endif // XMULTIPLEY_H
