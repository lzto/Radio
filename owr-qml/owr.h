/*
 * OWR-backend
 * 2012 by lovewilliam <lovewilliam@gmail.com>
 */

#include <QObject>
#include <QVariant>
#include <QTimer>

class OWR : public QObject
{
	Q_OBJECT
	public:
		OWR();
		~OWR();

	signals:
		void signal_updateFreq(QVariant);

	public slots:
		void slot_pre();
		void slot_next();
		void slot_trigger_update();

	private slots:
		void get_current_freq();

	private:
		double freq;
		QTimer timer;
};


