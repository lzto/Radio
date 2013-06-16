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

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QBuffer>
#include <QThread>
#include <QVector>

#include "radioinput.h"

class NetworkManager : public QObject
{
	Q_OBJECT
	public:
		NetworkManager(QObject *p);
		~NetworkManager();
		void setRadio(RadioInput *r);
		
	public slots:
		void slot_sendData();
		
	private slots:
		void acceptConnection();
		//void slot_stateChanged(QAbstractSocket::SocketState);
		void slot_peerConnected();
		void slot_peerDisconnected();

	private:
		QTcpServer *servSocket;
		QVector<QTcpSocket*>* sockets;
		RadioInput *radio;
};

#endif // NETWORKMANAGER_H
