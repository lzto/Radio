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


#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QBuffer>
#include <QtMultimedia/QAudioOutput>

class AudioPlayer : public QObject
{
	Q_OBJECT
	public:
		explicit AudioPlayer(QObject* parent = 0);
		virtual ~AudioPlayer();

	public slots:
		void appendData(QByteArray);
		void play();
		void stop();

	private slots:
		void finishedPlaying(QAudio::State);

	private:
		QAudioOutput *audio;
		QByteArray *buffer;
		QBuffer *buf;
		bool state;
};

#endif // AUDIOPLAYER_H
