#ifndef MODBUSTCPSERVERHANDLER_H
#define MODBUSTCPSERVERHANDLER_H

#include <QObject>
#include <QModbusDevice>
#include <QTextStream>
#include <QModbusDataUnit>

class QModbusTcpServer;

class ModbusTCPServerHandler: public QObject
{
    Q_OBJECT

public:

    explicit ModbusTCPServerHandler(QObject *parent = nullptr);
    ~ModbusTCPServerHandler();

signals:
    void switchTrigger(int switch_no);

private slots:
    void dataWritten(QModbusDataUnit::RegisterType table, int address, int size);
    void stateChanged(int state);
    void handleDeviceError(QModbusDevice::Error newError);

private:
    void startEstablishedConnection();

private:
    QModbusTcpServer *m_modbusTcpServer;
    QTextStream m_standardOutput;
};

#endif // MODBUSTCPSERVERHANDLER_H
