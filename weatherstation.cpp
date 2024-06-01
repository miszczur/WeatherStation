#include "weatherstation.h"
#include "./ui_weatherstation.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QDateTime>
#include"serialreader.h"
WeatherStation::WeatherStation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherStation)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
    this->sr = new SerialReader();
}

WeatherStation::~WeatherStation()
{
    delete ui;
    //delete device;
    delete sr;
}

void WeatherStation::on_pushButtonSearch_clicked()
{

    ui->comboBoxDevices->clear();
    QList<QSerialPortInfo> devices;
    addToLogs("Szukam urządzeń...");
    devices = QSerialPortInfo::availablePorts();
    for(int i = 0; i < devices.count(); i++) {
        this->addToLogs(devices.at(i).portName() +" "+ devices.at(i).description());
        ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }
    addToLogs("----------------------------------------");

}

void WeatherStation::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + " " + message);
}

void WeatherStation::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0) {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString portName = ui->comboBoxDevices->currentText().split(" ").first();
    this->device->setPortName(portName);

    // OTWIERANIE PORTU COM:
    if(!device->isOpen())  //ZABEZPIECZENIE PRZED POLACZENIEM SIE DO OTWARTEGO JUZ PORTU COM
    {
        if(device->open(QSerialPort::ReadWrite)) {
            this->device->setBaudRate(QSerialPort::Baud9600); //BAUDRATE 9600
            this->device->setDataBits(QSerialPort::Data8); //8 BITOW DANYCH
            this->device->setParity(QSerialPort::NoParity); //BRAK PARZYSTOSCI
            this->device->setStopBits(QSerialPort::OneStop); // JEDEN BIT STOPU
            this->device->setFlowControl(QSerialPort::NoFlowControl); //BEZ KONTROLI PRZEPLYWU
            this->addToLogs("Otwarto port szeregowy "+ device->portName());
            // CONNECT:
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
        }
        else {
            this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    } else {
        this->addToLogs("Port już jest otwarty!");
        return;
    }
}


void WeatherStation::on_pushButtonDisconnect_clicked()
{
    if(this->device->isOpen()) {
        this->device->close();
        this->addToLogs("Zamknięto połączenie.");
    } else {
        this->addToLogs("Port nie jest otwarty!");
        return;
    }
}

void WeatherStation::readFromPort()
{
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        //qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        //qDebug() << line.left(pos);

        this->addToLogs(line.left(pos));
    }
}


void WeatherStation::on_pushButtonClearLogs_clicked()
{
    ui->textEditLogs->clear();
}

