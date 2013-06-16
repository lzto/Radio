/*
    Copyright (C) 2011 lovewilliam <lovewilliam@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "networkmanager.h"

#define _AUDIO_SERVER_PORT_ 554
//#define _AUDIO_SERVER_PORT_ 1518


NetworkManager::NetworkManager(QObject* p): QObject(p)
{
	radio = NULL;
	sockets = new QVector<QTcpSocket*>;
	servSocket = new QTcpServer(this);
	QHostAddress *hostaddr = new QHostAddress();
	hostaddr->setAddress("0.0.0.0");
	servSocket->listen(*hostaddr,_AUDIO_SERVER_PORT_);
	connect(servSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
	qDebug()<<"Server Socket Initialized!";
}


NetworkManager::~NetworkManager()
{

}

void NetworkManager::setRadio(RadioInput* r)
{
	radio = r;
}


void NetworkManager::acceptConnection()
{
	qDebug()<<"Got new Connection";
	QTcpSocket *socket = servSocket->nextPendingConnection();
	connect(socket,SIGNAL(connected()),this,SLOT(slot_peerConnected()));
	connect(socket,SIGNAL(disconnected()),this,SLOT(slot_peerDisconnected()));
	sockets->append(socket);
}

void NetworkManager::slot_peerConnected()
{
	qDebug()<<"Conencted";
}

void NetworkManager::slot_peerDisconnected()
{
	//Clean up disconnected socket
	for(int i=0;i<sockets->size();i++)
	{
		if(sockets->at(i)->state()==QAbstractSocket::UnconnectedState)
		{
			qDebug()<<"Got Disconnected from "<<sockets->at(i)->peerAddress();
			sockets->remove(i);
			i--;
		}
	}
}

void NetworkManager::slot_sendData()
{
	if(radio==NULL)
	{
		qDebug()<<"Haven't set datastream";
		return;
	}
	
	QByteArray *block = new QByteArray();
	QDataStream mk(block,QIODevice::ReadWrite);
	mk.setVersion(QDataStream::Qt_4_6);
	mk<<(quint64)0;
	QByteArray tempData;
	tempData = radio->readData();//128000
	mk<<tempData;
	mk.device()->seek(0);
	mk<<(quint64)(block->size()-sizeof(quint64));
	qDebug()<<"block size:"<<block->size()-sizeof(quint64);
	
	for(int i=0;i<sockets->size();i++)
	{
		sockets->at(i)->write(*block);
	}
}


#include "networkmanager.moc"
