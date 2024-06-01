#include "serialreader.h"
#include<QDateTime>

SerialReader::SerialReader() {
    this->device = new QSerialPort();
}

SerialReader::~SerialReader()
{
    delete device;
}
void SerialReader::readFromPort()
{
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        //qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);

        //this->addToLogs(line.left(pos));
    }
}

