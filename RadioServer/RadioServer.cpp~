#include "RadioServer.h"

#include <QTimer>

RadioServer::RadioServer()
{
	radioInput = new RadioInput(this);
	mgr = new NetworkManager(this);
	mgr->setRadio(radioInput);
	connect(radioInput,SIGNAL(signal_notify()),mgr,SLOT(slot_sendData()));
	radioInput->start();
}

RadioServer::~RadioServer()
{
}

#include "RadioServer.moc"
