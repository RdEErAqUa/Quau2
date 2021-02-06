#ifndef QLISTUSEFUL_H
#define QLISTUSEFUL_H

#include <QList>

struct QListUseful
{
    static QList<double> Unique(QList<double> &sample)
    {
        QList<double> unique;
        for(double el : sample)
        {
            if(!unique.contains(el))
                unique << el;
        }
        return unique;

    }

    static QList<double> Average(QList<double> &sample)
    {
        QList<double> unique;
        for(double el : sample)
        {
            if(!unique.contains(el))
                unique << el;
        }
        return unique;

    }
};

#endif // QLISTUSEFUL_H
