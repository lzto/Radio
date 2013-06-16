#include <QCoreApplication>
#include "Listener.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    Listener foo;
    return app.exec();
}
