#include "librarysystem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibrarySystem w;
    //w.setGeometry(150,150,1300,800);
    w.show();

    return a.exec();
}
