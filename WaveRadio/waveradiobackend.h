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

#ifndef WAVERADIOBACKEND_H
#define WAVERADIOBACKEND_H

#include <QtCore/QObject>

#define RADIO_CMD "setfreq "

class waveRadioBackend : public QObject
{
	Q_OBJECT
	public:
		waveRadioBackend();
		~waveRadioBackend();
	public slots:
		void slot_Play(bool);
		void slot_freqUp();
		void slot_freqDown();
		void slot_setFreq(long int);
	private:
		QString cmd;
};

#endif // WAVERADIOBACKEND_H
