#include "QListUseful.h"

QList<double> QListUseful::Unique(QList<double> &sample)
{
    QList<double> unique;
    for(double el : sample)
    {
        if(!unique.contains(el))
            unique << el;
    }
    return unique;

}

QList<double> QListUseful::Average(QList<double> &sample)
{
    QList<double> unique;
    for(double el : sample)
    {
        if(!unique.contains(el))
            unique << el;
    }
    return unique;

}
