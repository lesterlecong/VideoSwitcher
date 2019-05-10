#include "modbustcpserverhandler.h"

#include <QModbusTcpServer>

ModbusTCPServerHandler::ModbusTCPServerHandler(QObject *parent) :
    QObject (parent),
    m_standardOutput(stdout)
{
    m_modbusTcpServer = new QModbusTcpServer(this);

    if(m_modbusTcpServer)
    {
        QModbusDataUnitMap reg;
        reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10});
        reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
        reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
        reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });

        m_modbusTcpServer->setMap(reg);

        connect(m_modbusTcpServer, &QModbusServer::dataWritten, this, &ModbusTCPServerHandler::dataWritten);
        connect(m_modbusTcpServer, &QModbusServer::stateChanged, this, &ModbusTCPServerHandler::stateChanged);
        connect(m_modbusTcpServer, &QModbusServer::errorOccurred, this, &ModbusTCPServerHandler::handleDeviceError);

        startEstablishedConnection();
    }
}

void ModbusTCPServerHandler::startEstablishedConnection()
{
    m_standardOutput << QObject::tr("ModbusTCPServer startEstablishedConnection") << endl;

    if(m_modbusTcpServer->state() == QModbusDevice::UnconnectedState)
    {
        m_modbusTcpServer->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_modbusTcpServer->setConnectionParameter(QModbusDevice::NetworkAddressParameter, QString("127.0.0.1") );
        m_modbusTcpServer->setServerAddress(1);

        if(!m_modbusTcpServer->connectDevice())
        {
            m_standardOutput << QObject::tr("ModbusTCPServer connection failed: %1").arg(m_modbusTcpServer->errorString()) << endl;
        }
    }
}

ModbusTCPServerHandler::~ModbusTCPServerHandler()
{
    if(m_modbusTcpServer->state() == QModbusDevice::ConnectedState)
    {
        m_modbusTcpServer->disconnectDevice();
    }

    m_modbusTcpServer->deleteLater();
}

void ModbusTCPServerHandler::dataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
    m_standardOutput << QObject::tr("ModbusTCPServer type: %1, address: %2, size: %3").arg(table).arg(address).arg(size) << endl;
    int switchState = 0;
    if(table == QModbusDataUnit::Coils)
    {
        quint16 value;
        m_modbusTcpServer->data(QModbusDataUnit::Coils, address, &value);
        switchState = value;
        m_modbusTcpServer->data(QModbusDataUnit::Coils, address + 1, &value);
        switchState = (switchState << 1) | value;

        emit switchTrigger(switchState);
    }
    /*
    for(int i = 0; i < size; i++)
    {

        quint16 value;
        QString text;
        switch (table) {
        case QModbusDataUnit::Coils:
            m_modbusTcpServer->data(QModbusDataUnit::Coils, address + i, &value);
            if((address + i) == 0 || (address + i) == 1)
            {
                switchState = switchState << (address + i) | value;
                emit switchTrigger(switchState);
            }

            break;
        case QModbusDataUnit::HoldingRegisters:
            m_modbusTcpServer->data(QModbusDataUnit::HoldingRegisters, address + i, &value);
            break;
        default:
            break;
        }
    }*/
}

void ModbusTCPServerHandler::stateChanged(int state)
{
    if(state == QModbusDevice::UnconnectedState)
    {
        m_standardOutput << QObject::tr("ModbusTCPServer disconnected") << endl;
    }
    else if(state == QModbusDevice::ConnectedState)
    {
        m_standardOutput << QObject::tr("ModbusTCPServer connected") << endl;
    }
}

void ModbusTCPServerHandler::handleDeviceError(QModbusDevice::Error newError)
{
    if (newError == QModbusDevice::NoError || !m_modbusTcpServer)
        return;

    m_standardOutput << QObject::tr("ModbusTCPServer error: %1").arg(m_modbusTcpServer->errorString()) << endl;

}


