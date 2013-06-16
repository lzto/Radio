/*
    Copyright (C) 2011  lovewilliam <lovewilliam@gmail.com>

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
#include <QtCore/QDebug>
#include <QtCore/QByteArray>

NetworkManager::NetworkManager(QObject *p):
	QObject(p)
{
	host = "211.87.227.81";
	//host = "127.0.0.1";
	port = 1536;
	packetSize = 0;
	socket = new QTcpSocket;
	socket->setReadBufferSize(1024*1024);
	connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
		this,SLOT(slot_stateChanged(QAbstractSocket::SocketState)));
	connect(socket,SIGNAL(readyRead()),this,SLOT(slot_fetchData()));
	in = new QDataStream(socket);
	in->setVersion(QDataStream::Qt_4_6);
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::setHost(QString s)
{
	host = s;
}

void NetworkManager::connectServer()
{
	qDebug()<<"Connecting to server";
	socket->connectToHost(host,port,QIODevice::ReadWrite);
}

void NetworkManager::disconnectServer()
{
	qDebug()<<"Disconnect from server.";
	socket->disconnectFromHost();
}


void NetworkManager::slot_stateChanged(QAbstractSocket::SocketState s)
{
	qDebug()<<"State Changed:"<<s;
}

void NetworkManager::slot_fetchData()
{
	if(packetSize==0)
	{
		if (socket->bytesAvailable() < (int)sizeof(quint64))
		return;
		*in >> packetSize;
		qDebug()<<"In block size:"<<packetSize;
	}
	if (socket->bytesAvailable() < packetSize)
		return;
	qDebug()<<"Emerging data.";
	QByteArray *data = new QByteArray(socket->read(quint64(packetSize)));
	if(data->isEmpty())
	{
		qDebug()<<"void NetworkManager::slot_fetchData()";
		qDebug()<<"Network socket error!";
		exit(-1);
	}

	QDataStream stream(data,QIODevice::ReadOnly);
	qDebug()<<"size="<<data->size();
	QByteArray audioData;
	stream>>audioData;
	packetSize = 0;
	emit signal_gotData(audioData);
}

#include "networkmanager.moc"
