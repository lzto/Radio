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

#include "radioinput.h"

#include <QAudioDeviceInfo>
#include <QList>
#include <QDebug>

RadioInput::RadioInput(QObject *p)
	:QObject(p)
{
	buffer = new QByteArray();
	buf = new QBuffer(this);
	buf->setBuffer(buffer);
	buf->open(QIODevice::WriteOnly);
	QAudioFormat format;
	/*
	 * See http://en.wikipedia.org/wiki/Sampling_rate
	 * and http://en.wikipedia.org/wiki/Sample_size
	 */
	format.setFrequency(32000);
	format.setChannels(2);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
	
	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format)) {
		qWarning()<<"default format not supported try to use nearest";
		format = info.nearestFormat(format);
	}
	qDebug()<<"Using Device:"<<info.deviceName();
	qDebug()<<"Supported Codecs:"<<info.supportedCodecs();
/*	QList<QAudioDeviceInfo> list = info.availableDevices(QAudio::AudioInput);
	for(int i=0;i<list.size();i++)
	{
		qDebug()<<"Available Devices:"<<list.at(i).deviceName();
	}*/
	
	audioInput = new QAudioInput(format, this);
	audioInput->setNotifyInterval(1000);
	connect(audioInput,SIGNAL(notify()),this,SLOT(slot_notify()));
	connect(audioInput,SIGNAL(stateChanged(QAudio::State)),
		this,SLOT(slot_stateChanged(QAudio::State)));
}

RadioInput::~RadioInput()
{

}

void RadioInput::slot_notify()
{
	qDebug()<<"Nofified.";
	emit signal_notify();
}

QByteArray RadioInput::readData()
{
	//qDebug()<<"Fuck #1 Buffer size="<<buf->size();
	buf->close();
	buf->open(QIODevice::ReadOnly);
	QByteArray temp = buf->readAll();
	buf->close();
	buffer->clear();
	buf->open(QIODevice::WriteOnly);
	return temp;
}


void RadioInput::start()
{
	qDebug()<<"Starting .";
	buffer->clear();
	audioInput->start(buf);
}

void RadioInput::stop()
{
	qDebug()<<"Stopping.";
	audioInput->stop();
	buffer->clear();
}

void RadioInput::slot_stateChanged(QAudio::State state)
{
	qDebug()<<"QAudioInput State Changed:"<<state;
	if((state==QAudio::StoppedState)||
		(state==QAudio::SuspendedState))
	{
		qDebug()<<"Error code:"<<audioInput->error();
	}
}

#include "radioinput.moc"
