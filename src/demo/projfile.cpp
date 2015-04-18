#include "projfile.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

ProjFile::ProjFile()
{
}

void ProjFile::save() {
    int i;
    QFile data(fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);

        // If the two files are in the same directory, use rel path
        if (QFileInfo(picSrc).path() == QFileInfo(fileName).path())
            out << QFileInfo(picSrc).fileName() << endl;
        else
            out << picSrc << endl;

        out << qlSrc.size() << endl;
        for (i = 0; i < qlSrc.size(); i++)
            out << qlSrc[i].x() << " " << qlSrc[i].y() << endl;
        out << qlDest.size() << endl;
        for (i = 0; i < qlDest.size(); i++)
            out << qlDest[i].x() << " " << qlDest[i].y() << endl;
        data.close();
    }
}

void ProjFile::open(QString fileN) {
    if (fileN == "")
        fileN = fileName;
    else
        fileName = fileN;

    QFile data(fileName);
    int i, l;
    if (data.open(QFile::ReadOnly)) {
        QTextStream dataS(&data);
        picSrc = dataS.readLine();
        if (QFileInfo(picSrc).isRelative())
            picSrc = QFileInfo(fileName).path() + "/" + picSrc;

        dataS >> l;
        int a, b;
        qlSrc.clear();
        qlDest.clear();
        for (i = 0; i < l; i++) {
            dataS >> a >> b;
            qlSrc.push_back(QPoint(a, b));
        }
        dataS >> l;
        for (i = 0; i < l; i++) {
            dataS >> a >> b;
            qlDest.push_back(QPoint(a, b));
        }
        data.close();
    }
}
