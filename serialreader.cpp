#include "serialreader.h"
#include <QDateTime>
#include "measurement.h"
SerialReader::SerialReader()
{
    //INICJALIZACJA POTRZEBNYCH OBIEKTÓW
    this->device = new QSerialPort();
    this->ms = new Measurement();
    this->serialLog = new Logger();

    //DOMYŚLNA KONFIGURACJA SERIAL PORTU
    this->device->setBaudRate(QSerialPort::Baud9600);         //BAUDRATE 9600
    this->device->setDataBits(QSerialPort::Data8);            //8 BITOW DANYCH
    this->device->setParity(QSerialPort::NoParity);           //BRAK PARZYSTOSCI
    this->device->setStopBits(QSerialPort::OneStop);          // JEDEN BIT STOPU
    this->device->setFlowControl(QSerialPort::NoFlowControl); //BEZ KONTROLI PRZEPLYWU


    connect(this->ms, &Measurement::newData, this, &SerialReader::HandleData);
}

SerialReader::~SerialReader()
{
    delete device;
    delete ms;
    delete serialLog;
}

void SerialReader::readFromPort()
{
    //POBRANIE DANYCH Z POLACZENIA, PRZETWORZENIE I DODANIE DO OBIEKTU POMIARU
    while (this->device->canReadLine()) {

        QString line = this->device->readLine();
        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        serialLog->addToLogWindow(line.left(pos));
        ms->Append(line.left(pos));
    }
}

bool SerialReader::isOpen()
{
    if (device->isOpen()) return true;
    else return false;
}

void SerialReader::HandleData(int temperature, int humidity)
{
    emit srData(temperature, humidity);
}

void SerialReader::OpenPort(QString pn)
{
    this->device->setPortName(pn); //USTAWIENIE ODPOWIEDNIEGO PORTU COM
    if (!device->isOpen()) //ZABEZPIECZENIE PRZED POLACZENIEM SIE DO OTWARTEGO JUZ PORTU COM
    {
        if (device->open(QSerialPort::ReadOnly)) {

            serialLog->addToLogWindow("Otwarto port szeregowy " + device->portName());

            connect(this->device,
                    SIGNAL(readyRead()),
                    this,
                    SLOT(readFromPort())); // CONNECT: PODLACZANIE SYGNALU DO ODCZYTYWANIA Z ARDUINO POD SLOT READFROMPORT
        } else {
            serialLog->addToLogWindow("Otwarcie portu szeregowego się nie powiodło!");
        }
    } else {
        serialLog->addToLogWindow("Port już jest otwarty!");
    }
}

void SerialReader::ClosePort()
{
    //ZAMYKANIE POLACZENIA Z ZABEZPIECZENIEM PRZED NIEOTWARTYM PORTEM
    if (this->device->isOpen()) {
        this->device->close();
        serialLog->addToLogWindow("Zamknięto połączenie.");
    } else {
        serialLog->addToLogWindow("Port nie jest otwarty!");
        return;
    }
}

void SerialReader::PushRecordsToDataBase(void)
{
    // Wyslij wszystkie wpisy z pamieci do bazy danych
    if(device->isOpen()){
    ms->PushRecordsToDataBase();
    } else {
        serialLog->addToLogWindow("Port nie jest otwarty! Nie można wysłać nic do bazy!");
        return;
    }
}

