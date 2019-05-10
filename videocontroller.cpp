#include "videocontroller.h"
#include "modbustcpserverhandler.h"

#include <QTimer>
#include <QCoreApplication>

VideoController::VideoController(QObject *parent) :
    QObject (parent),
    m_standardOutput(stdout),
    m_videoSrc(QString("")),
    state(0)
{

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    //m_timer->start(5000);

    m_modbusDevice = new ModbusTCPServerHandler(this);
    connect(m_modbusDevice, SIGNAL(switchTrigger(int)), this, SLOT(onSwitchTriggered(int)));
}

VideoController::~VideoController()
{
    m_timer->deleteLater();
    delete m_modbusDevice;
}

void VideoController::setVideoSrc(QString videoSrc)
{
    m_videoSrc = videoSrc;
}

QString VideoController::getVideoSrc()
{
    return m_videoSrc;
}

void VideoController::timeout(){
    m_standardOutput << QObject::tr("Timeout...") << endl;

}

void VideoController::onSwitchTriggered(int switchState)
{
    /**To do: Make state machine on this***/
    m_standardOutput << QObject::tr("Switch Triggered: %1").arg(switchState) << endl;

    if(switchState == 3) {
        emit videoSrcChanged(QString("file:///e:/Projects/Qt/Video-Switcher/Rooster.mp4"), 0);
    }
    else {
        emit videoSrcChanged(QString("file:///e:/Projects/Qt/Video-Switcher/waterfalls.mp4"), 1);
    }
}
