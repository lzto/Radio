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


#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>

class NetworkManager : public QObject
{
	Q_OBJECT
	public:
		NetworkManager(QObject*);
		~NetworkManager();
		
	public slots:
		void setHost(QString);
		void connectServer();
		void disconnectServer();
	signals:
		void signal_gotData(QByteArray);
		
	private:
		QTcpSocket *socket;
		QString host;
		quint16 port;
		quint64 packetSize;
		QDataStream *in;
		
	private slots:
		void slot_stateChanged(QAbstractSocket::SocketState);
		void slot_fetchData();

};

#endif // NETWORKMANAGER_H
