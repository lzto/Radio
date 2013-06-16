/*
 * OWR-backend
 * 2012 by lovewilliam <lovewilliam@gmail.com>
 */
#include "owr.h"


#include <QProcess>

#include <QDebug>

#include "stdlib.h"

#define _RADIO_COMMAND_ "setfreq"

OWR::OWR()
{
	connect(&timer,SIGNAL(timeout()),this,SLOT(get_current_freq()));
	timer.start(300);
}

OWR::~OWR()
{
}

void OWR::slot_pre()
{
	//qDebug()<<"OWR::slot_pre()";
	system(QString(_RADIO_COMMAND_" down").toLocal8Bit());
	get_current_freq();
}

void OWR::slot_next()
{
	//qDebug()<<"OWR::slot_next()";
	system(QString(_RADIO_COMMAND_" up").toLocal8Bit());
	get_current_freq();
}

void OWR::slot_trigger_update()
{
	get_current_freq();
}

void OWR::get_current_freq()
{
	//TODO get current freq
	freq = 88700;
	QString program = _RADIO_COMMAND_;
	QStringList arguments;
	arguments << "status";
	
	QProcess *process = new QProcess(this);
	process->start(program, arguments);
	
	if (!process->waitForStarted())
		return;

	if (!process->waitForFinished())
		return;
	
	QString result = QString(process->readAllStandardOutput());

	QStringList list = result.split("\n");
	if(list.count()<3)
	{
		return;
	}
	freq = list.at(1).split(":").at(1).toInt()/1000.0;

	////////////////////////
	emit signal_updateFreq(QString("%1 MHz").arg(freq));
}

