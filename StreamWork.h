#ifndef STREAMWORK_H
#define STREAMWORK_H
#include "Data/sample.h"
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>

class StreamWork
{
public:
    static QString ReadString(const QString &FileName);
    static QList<double> ReadDouble(const QString &FileName);
    static QList<int> ReadInt(const QString &FileName);
};

#endif // STREAMWORK_H
