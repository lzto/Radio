#include <QCoreApplication>
#include "RadioServer.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    RadioServer foo;
    return app.exec();
}
