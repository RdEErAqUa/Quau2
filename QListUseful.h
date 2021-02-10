#ifndef QLISTUSEFUL_H
#define QLISTUSEFUL_H

#include <QList>

class QListUseful
{
public:
    static QList<double> Unique(QList<double> &sample);

    static QList<double> Average(QList<double> &sample);
};

#endif // QLISTUSEFUL_H
