#include <QtGui/QApplication>

#include <iostream>
#include "deformwin.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeformWin w;

    w.show();
    return a.exec();
}
