#ifndef RadioServer_H
#define RadioServer_H

#include <QtCore/QObject>
#include "radioinput.h"
#include "networkmanager.h"

class RadioServer : public QObject
{
	Q_OBJECT
	public:
		RadioServer();
		virtual ~RadioServer();
	private slots:
	private:
		RadioInput *radioInput;
		NetworkManager *mgr;
};

#endif // RadioServer_H
