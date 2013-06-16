/*
    Copyright (C) 2010 lovewilliam <lovewilliam@gmail.com>

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

#include "aboutwidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QFile>

#include <QDebug>

aboutWidget::aboutWidget()
{
    setWindowIcon(QIcon("/usr/share/OpenWave/icons/aol-radio-icon-512x512.png"));
    setFixedSize(180,260);
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    setWindowTitle(tr("About OpenWave Radio"));
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap("/usr/share/OpenWave/icons/aol-radio-icon-512x512.png").scaledToHeight(128).scaledToWidth(128));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,0,0);
    QLabel *despLabel = new QLabel;
    despLabel->setTextFormat(Qt::RichText);
    despLabel->setText(tr("OpenWave Radio <br>"
			"Hardware & Software By<br>"
			"lovewilliam AT "
			"<font color=\"Red\">S</font>"
			"<font color=\"Orange\">D</font>"
			"<font color=\"Blue\">U</font>"
			"<font color=\"Yellow\">.</font>"
			"<font color=\"Green\">S</font>"
			"<font color=\"Purple\">C</font>"
			"<br>"
			"Visit "
			"<a href=\"http://www.bigstarstar.tk/\">http://www.bigstarstar.tk</a><br>"
			"Or <a href=\"mailto:lovewilliam@gmail.com\">lovewilliam@gmail.com</a>"));
    despLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(despLabel,1,0);
    QPushButton *btnOK = new QPushButton;
    btnOK->setText(tr("I Know!:)"));
    layout->addWidget(btnOK,2,0);
    connect(btnOK,SIGNAL(clicked(bool)),this,SLOT(deleteLater()));
    //setMaximumHeight(height());
    //setMaximumWidth(width());

    setFixedSize(300,320);
    
//    setMinimumHeight(height());
//    setMinimumWidth(width());
}

aboutWidget::~aboutWidget()
{
//    qDebug()<<"Destroyed";
}

void aboutWidget::deleteLater()
{
    delete this;
}

void aboutWidget::closeEvent(QCloseEvent* event)
{
    delete this;
}


#include "aboutwidget.moc"

