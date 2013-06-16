/*
 * OpenWaveRadio - qml
 * 2012 by lovewilliam <lovewilliam@gmail.com>
 */
#include <QApplication>
#include <QDeclarativeView>
#include <QVariant>
#include <QtDeclarative>

#include "owr.h"

#define _APP_VERSION_ "0.0.1"



int main(int argc,char** argv)
{
	QApplication::setGraphicsSystem("opengl");
	QApplication app(argc,argv);
	app.setApplicationName("qr");
	app.setApplicationVersion(_APP_VERSION_);


	OWR owr;

	QDeclarativeView view;
	view.setWindowTitle("OpenWave Radio");
	
	((QDeclarativeContext*)view.rootContext())->setContextProperty("owr", &owr);

	view.setSource(QUrl("./main.qml"));
	
	QObject *rootObject = dynamic_cast<QObject*>(view.rootObject());

	QObject::connect(&owr, SIGNAL(signal_updateFreq(QVariant)),
			rootObject, SLOT(updateFreq(QVariant)));

	owr.slot_trigger_update();
#ifdef __arm__
	view.showFullScreen();
#else
	view.show();
#endif
	return app.exec();
}


