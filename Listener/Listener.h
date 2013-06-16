#ifndef Listener_H
#define Listener_H

#include <QtCore/QObject>

#include "networkmanager.h"
#include "audioplayer.h"

class Listener : public QObject
{
	Q_OBJECT
	public:
		Listener();
		virtual ~Listener();
		
	private:
		NetworkManager *network;
		AudioPlayer *player;
	private slots:
};

#endif // Listener_H
