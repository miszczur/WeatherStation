#include "serialreader.h"
#include <QDateTime>
#include "measurement.h"
SerialReader::SerialReader()
{
    this->device = new QSerialPort();
}

SerialReader::~SerialReader()
{
    delete device;
}

void SerialReader::readFromPort()
{
    this->ms = new Measurement();

    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        addToLogs(line.left(pos));
        ms->Append(line.left(pos));

    }
}

void SerialReader::OpenPort(QString pn)
{
    this->device->setPortName(pn);
    if(!device->isOpen())  //ZABEZPIECZENIE PRZED POLACZENIEM SIE DO OTWARTEGO JUZ PORTU COM
    {
        if(device->open(QSerialPort::ReadOnly)) {
            this->device->setBaudRate(QSerialPort::Baud9600); //BAUDRATE 9600
            this->device->setDataBits(QSerialPort::Data8); //8 BITOW DANYCH
            this->device->setParity(QSerialPort::NoParity); //BRAK PARZYSTOSCI
            this->device->setStopBits(QSerialPort::OneStop); // JEDEN BIT STOPU
            this->device->setFlowControl(QSerialPort::NoFlowControl); //BEZ KONTROLI PRZEPLYWU
            addToLogs("Otwarto port szeregowy "+ device->portName());
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));  // CONNECT: PODLACZANIE SYGNALU DO ODCZYTYWANIA Z ARDUINO POD SLOT READFROMPORT
        }
        else {
            addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    } else {
       addToLogs("Port już jest otwarty!");
    }
}

void SerialReader::ClosePort()
{

    if(this->device->isOpen()) {
        this->device->close();
        addToLogs("Zamknięto połączenie.");
    } else {
        addToLogs("Port nie jest otwarty!");
        return;
    }
}

void SerialReader::addToLogs(QString msg)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    emit Log(currentDateTime + " " + msg); //EMIT NADAJE SYGNAL PRZEZ CO MOZEMY ODEBRAC GO W KLASIE WEATHERSTATION I NASLUCHIWAC I PRZEKAZYWAC DO LOGA
}
