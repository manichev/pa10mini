#include "pax_prototype.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_ALL, "C");
    PAX_Prototype w;
    w.show();
    return a.exec();
}
