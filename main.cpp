#include "schrauber.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Schrauber w;
    w.show();

    return a.exec();
}
