#include "lorakit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoraKit w;
    w.show();

    return a.exec();
}
