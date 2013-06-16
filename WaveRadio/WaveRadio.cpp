#include "WaveRadio.h"
#include "aboutwidget.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>


WaveRadio::WaveRadio()
{
	this->setWindowIcon(QPixmap("/usr/share/OpenWave/icons/aol-radio-icon-512x512.png"));
    wWidget = new waveWidget();
    setCentralWidget( wWidget );
    QAction* a = new QAction(this);
    a->setText( "Quit" );
    connect(a, SIGNAL(triggered()), SLOT(close()) );
    
    QMenu *menu = menuBar()->addMenu( tr("&Wave") );
    QAction *actionTray = new QAction(tr("&Tray"),this);
    menu->addAction(actionTray);
    
    menu->addSeparator();
    
    QAction *actionExit = new QAction(tr("E&xit"),this);
    menu->addAction(actionExit);
    
    QMenu *aboutMenu = menuBar()->addMenu(tr("&About"));
    QAction *actionAbout = new QAction(tr("&About"),this);
    aboutMenu->addAction(actionAbout);
    
    connect(actionTray,SIGNAL(triggered(bool)),this,SLOT(slot_tray()));
    connect(actionExit,SIGNAL(triggered(bool)),this,SLOT(slot_exit()));
    connect(actionAbout,SIGNAL(triggered(bool)),this,SLOT(slot_about()));
    
    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon("/usr/share/OpenWave/icons/aol-radio-icon-512x512.png"));
    QMenu *tmenu= new QMenu();

    QAction *ta_up = new QAction(tr("&Up"),this);;
    QAction *ta_down = new QAction(tr("&Down"),this);
    QAction *ta_exit = new QAction(tr("E&xit"),this);
    QAction *ta_about = new QAction(tr("&About"),this);
    
    connect(ta_up,SIGNAL(triggered(bool)),wWidget,SLOT(slot_btnFreqPlus()));
    connect(ta_down,SIGNAL(triggered(bool)),wWidget,SLOT(slot_btnFreqMinus()));
    connect(ta_exit,SIGNAL(triggered(bool)),this,SLOT(slot_exit()));
    connect(ta_about,SIGNAL(triggered(bool)),this,SLOT(slot_about()));
    
    tmenu->addAction(ta_up);
    tmenu->addAction(ta_down);
    tmenu->addSeparator();
    tmenu->addAction(ta_about);
    tmenu->addSeparator();
    tmenu->addAction(ta_exit);
    tray->setContextMenu(tmenu);
    
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	    this,SLOT(slot_tray(QSystemTrayIcon::ActivationReason)));
    
    tray->show();
}

WaveRadio::~WaveRadio()
{}

void WaveRadio::slot_about()
{
	aboutWidget *aboutw = new aboutWidget;
	aboutw->show();
}

void WaveRadio::slot_tray(QSystemTrayIcon::ActivationReason r)
{
	switch (r)
	{
		case(QSystemTrayIcon::Trigger):
		{
			slot_tray();
			break;
		}
		default:
			break;
	}
}


void WaveRadio::slot_tray()
{
	if(this->isVisible())
	{
		hide();
	}
	else
	{
		show();
	}
}

void WaveRadio::slot_exit()
{
	exit(0);
}


#include "WaveRadio.moc"
