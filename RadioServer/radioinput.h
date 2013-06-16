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

#ifndef RADIOINPUT_H
#define RADIOINPUT_H

#include <QObject>
#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QAudioInput>
#include <QAudioFormat>

/*
 * Sample and provide buffer
 */

class RadioInput : public QObject
{
	Q_OBJECT
	public:
		RadioInput(QObject *parent);
		~RadioInput();
		QByteArray readData();
	signals:
		void signal_notify();
		
	public slots:
		void start();
		void stop();
		
	private:
		QAudioInput *audioInput;
		QBuffer *buf;
		QByteArray *buffer;
		
	private slots:
		void slot_notify();
		void slot_stateChanged ( QAudio::State state ) ;
		
};

#endif // RADIOINPUT_H
