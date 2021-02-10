#include "StreamWork.h"


QString StreamWork::ReadString(const QString &FileName)
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

QList<double> StreamWork::ReadDouble(const QString &FileName){
    QString FileData = ReadString(FileName);
    QList<QString> data;
    QString temp;
    QList<double> returnValue;
    for(int i = 0; i <= FileData.size(); i++)
    {
        QChar value = i < FileData.size() ? FileData.at(i) : 's';
        if(value == '-' && (temp.isNull() || temp.isEmpty()) ){
            temp+=value;
        }
        else if(value.isDigit() || value == '.' ) {
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

QList<int> StreamWork::ReadInt(const QString &FileName){
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
