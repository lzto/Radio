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

#include "waveradiobackend.h"

#include <stdlib.h>

#include <QDebug>

waveRadioBackend::waveRadioBackend()
{
	cmd = RADIO_CMD;
}

waveRadioBackend::~waveRadioBackend()
{

}

void waveRadioBackend::slot_Play(bool play)
{
	
}

void waveRadioBackend::slot_freqUp()
{
	QString command = cmd;
	command+="up";
	system(command.toAscii());
}


void waveRadioBackend::slot_freqDown()
{
	QString command = cmd;
	command+="down";
	system(command.toAscii());
}


void waveRadioBackend::slot_setFreq(long int freq)
{
	QString command = QString(" set %1").arg(freq);
	command = cmd+command;
	system(command.toAscii());
}



#include "waveradiobackend.moc"

