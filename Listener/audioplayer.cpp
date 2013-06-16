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


#include "audioplayer.h"
#include <QAudioDeviceInfo>
#include <QAudioFormat>

#include <QDebug>


AudioPlayer::AudioPlayer(QObject* parent)
{
	state = false;
	buffer = new QByteArray;
	buf = new QBuffer;
	buf->setBuffer(buffer);
	QAudioFormat format;
	// Set up the format, eg.
	format.setFrequency(32000);
	format.setChannels(2);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	if (!info.isFormatSupported(format)) {
		qWarning()<<"raw audio format not supported by backend, cannot play audio.";
		return;
	}
	audio = new QAudioOutput(format, this);
	connect(audio,SIGNAL(stateChanged(QAudio::State)),SLOT(finishedPlaying(QAudio::State)));
}

AudioPlayer::~AudioPlayer()
{
	stop();
}

void AudioPlayer::appendData(QByteArray data)
{
	if(state)
	{
		buf->close();
		//FIXME!!!
		buffer->clear();
		buffer->append(data);
		
		buf->open(QIODevice::ReadOnly);
		audio->start(buf);
	}
}

void AudioPlayer::play()
{
	if(!state)
	{
		state = TRUE;
		buf->open(QIODevice::ReadOnly);
		audio->start(buf);
	}
}

void AudioPlayer::stop()
{
	if(state)
	{
		audio->stop();
		buf->close();
	}
}

void AudioPlayer::finishedPlaying(QAudio::State)
{
	if (state == QAudio::IdleState)
	{
		audio->stop();
		qDebug()<<" state:FUCK! idle state";
	}
}

#include "audioplayer.moc"
