#include "acbcgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ACBCGui w;
    w.show();

    return a.exec();
}
