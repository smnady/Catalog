#include "catalog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Catalog w;
    w.resize(400, 400);
    w.show();
    return a.exec();
}
