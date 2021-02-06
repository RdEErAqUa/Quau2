#ifndef STREAMWORK_H
#define STREAMWORK_H
#include "Data/sample.h"
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>

struct StreamWork
{
    static QString ReadString(const QString &FileName)
    {
        QFile file(FileName);
        QString fileData;
        if(file.exists() && (file.open(QIODevice::ReadOnly))){
            while(!file.atEnd()){
                fileData += file.readLine();
            }
            file.close();
        }
        return fileData;
    }
    static QList<double> ReadDouble(const QString &FileName){
        QString FileData = ReadString(FileName);

        QList<QString> data;
        QString temp;
        QList<double> returnValue;
        for(QChar value : FileData)
        {
            if(value.isDigit() || value == '.' ) {
                temp += value;
            }
            else
            {
                if(!temp.isNull() && !temp.isEmpty())
                    returnValue << temp.toDouble();
                temp = "";
            }
        }
        return returnValue;
    }
    static QList<int> ReadInt(const QString &FileName){
        QString FileData = ReadString(FileName);

        QList<QString> data;
        QString temp;
        QList<int> returnValue;
        for(QChar value : FileData)
        {
            if(value.isDigit()) {
                temp += value;
            }
            else
            {
                if(!temp.isNull() && !temp.isEmpty())
                    returnValue << temp.toInt();
                temp = "";
            }
        }
        return returnValue;
    }
};

#endif // STREAMWORK_H
