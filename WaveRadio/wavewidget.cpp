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

#include "wavewidget.h"

#include <QGridLayout>
#include <QDebug>

waveWidget::waveWidget()
{
	freq = 88700;
	backend = new waveRadioBackend;
	backend->slot_setFreq(freq);

	QGridLayout *layout = new QGridLayout();
	setLayout(layout);
	dashBoard = new QLCDNumber;
	dashBoard->display(freq/1000.0);
	layout->addWidget(dashBoard,0,0,2,4);
	
	slider = new QSlider(Qt::Horizontal);
	layout->addWidget(slider,2,0,1,4);
	btnPlay = new QPushButton("Play");
	layout->addWidget(btnPlay,3,0,1,1);
	btnFreqMinus = new QPushButton("<");
	layout->addWidget(btnFreqMinus,3,1,1,1);
	btnFreqPlus = new QPushButton(">");
	layout->addWidget(btnFreqPlus,3,2,1,1);
	labelInfo = new QLabel;
	layout->addWidget(labelInfo,4,0,1,1);
	
	dashBoard->setMinimumSize(300,160);
	slider->setMinimum(76000);
	slider->setMaximum(108000);
	slider->setValue(freq);
	slider->setSingleStep(100);
	
	connect(btnPlay,SIGNAL(clicked(bool)),this,SLOT(slot_btnPlay()));
	connect(btnFreqMinus,SIGNAL(clicked(bool)),this,SLOT(slot_btnFreqMinus()));
	connect(btnFreqPlus,SIGNAL(clicked(bool)),this,SLOT(slot_btnFreqPlus()));
	connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slot_slider(int)));
	btnPlay->hide();
}

waveWidget::~waveWidget()
{

}

void waveWidget::slot_btnPlay()
{
	if(btnPlay->text()=="Play")
	{
		btnPlay->setText("Stop");
		backend->slot_Play(FALSE);
		labelInfo->setText(QString("Playing %1 Mhz").arg(freq/1000.0));
	}else
	{
		btnPlay->setText("Play");
		backend->slot_Play(TRUE);
		labelInfo->setText("Stopped");
	}
}

void waveWidget::slot_btnFreqMinus()
{
	freq-=100;
	if((freq>108000)||(freq<76000))
	{
		freq+=100;
		return;
	}
	dashBoard->display(freq/1000.0);
	labelInfo->setText(QString("Playing %1 Mhz").arg(freq/1000.0));
	backend->slot_freqDown();
	slider->setValue(freq);
}

void waveWidget::slot_btnFreqPlus()
{
	freq+=100;
	if((freq>108000)||(freq<76000))
	{
		freq-=100;
		return;
	}
	dashBoard->display(freq/1000.0);
	labelInfo->setText(QString("Playing %1 Mhz").arg(freq/1000.0));
	backend->slot_freqUp();
	slider->setValue(freq);
}

void waveWidget::slot_slider(int target)
{
	freq = target;
	backend->slot_setFreq(freq);
	dashBoard->display(freq/1000.0);
	labelInfo->setText(QString("Playing %1 Mhz").arg(freq/1000.0));
}



#include "wavewidget.moc"
