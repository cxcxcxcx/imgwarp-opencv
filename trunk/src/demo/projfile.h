#ifndef PROJFILE_H
#define PROJFILE_H

#include<QString>
#include<QList>
#include<QPoint>

class ProjFile
{
public:
    QString picSrc;
    QList< QPoint > qlSrc, qlDest;

    QString fileName;

    void save();
    void open(QString fileN = "");

    ProjFile();
};

#endif // PROJFILE_H
