// Autor: Alberto Aguilar
// Fecha: Junio de 2021


#include "Flowchart.h"
#include <QtWidgets/QApplication>

using namespace vista;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Flowchart w;
    w.show();
    return a.exec();
}
