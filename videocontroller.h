#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QObject>
#include <QTextStream>

class QTimer;
class ModbusTCPServerHandler;
class VideoController: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString videoSrc READ getVideoSrc WRITE setVideoSrc NOTIFY videoSrcChanged)

public:
    explicit VideoController(QObject *parent = nullptr);
    ~VideoController();

    void setVideoSrc(QString videoSrc);
    QString getVideoSrc();

signals:
    void videoSrcChanged(QString src, int loopAllowed);

public slots:
    void timeout();
    void onSwitchTriggered(int switchState);

private:
    QTextStream m_standardOutput;
    QString m_videoSrc;
    QTimer *m_timer;
    ModbusTCPServerHandler *m_modbusDevice;
    int state;
};

#endif // VIDEOCONTROLLER_H
