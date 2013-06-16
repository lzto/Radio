#include "Listener.h"

Listener::Listener()
{
	network = new NetworkManager(this);
	player = new AudioPlayer(this);
	connect(network,SIGNAL(signal_gotData(QByteArray)),
		player,SLOT(appendData(QByteArray)));
	player->play();
	network->connectServer();
}

Listener::~Listener()
{
	
}

#include "Listener.moc"
