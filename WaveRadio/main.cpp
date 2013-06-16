#include <QtGui/QApplication>
#include "WaveRadio.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    WaveRadio foo;
    foo.show();
    return app.exec();
}
