#ifndef WaveRadio_H
#define WaveRadio_H

#include <QtGui/QMainWindow>
#include <QSystemTrayIcon>

#include "wavewidget.h"

class WaveRadio : public QMainWindow
{
Q_OBJECT
	public:
		WaveRadio();
		virtual ~WaveRadio();
	private:
		waveWidget* wWidget;
		QSystemTrayIcon *tray;
		
	private slots:
		void slot_about();
		void slot_tray();
		void slot_exit();
		void slot_tray(QSystemTrayIcon::ActivationReason);
};

#endif // WaveRadio_H
