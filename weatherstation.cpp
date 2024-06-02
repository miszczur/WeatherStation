#include "weatherstation.h"
#include <QDateTime>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "./ui_weatherstation.h"
#include "serialreader.h"

WeatherStation::WeatherStation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherStation)
{
    ui->setupUi(this);
    this->sr = new SerialReader();
    connect(this->sr,
            SIGNAL(Log(QString)),
            this->ui->textEditLogs,
            SLOT(append(QString))); //nasluchujemy czy przychodzi sygnal z loga i dodajemy msg
    //connect(this->sr,SIGNAL(Log(QString)),this->ui->comboBoxDevices,SLOT(clear()));
    // connect(this->sr,SIGNAL(ClearLog()),this->ui->textEditLogs,SLOT(clear()));           //nasluchujemy czy przychodzi sygnal clearlog i czyscimy loga
    on_pushButtonSearch_clicked();
}

WeatherStation::~WeatherStation()
{
    delete ui;
    delete sr;
}

void WeatherStation::on_pushButtonSearch_clicked()
{
    //TODO: przeniesc do serial readera jak sie da
    ui->comboBoxDevices->clear();
    //emit sr->ClearLog();
    sr->addToLogs("Szukam urządzeń...");
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();
    for (int i = 0; i < devices.count(); i++) {
        QString name = devices.at(i).portName() + " (" + devices.at(i).description() + ")";
        sr->addToLogs(name);
        ui->comboBoxDevices->addItem(name);
    }
    sr->addToLogs("----------------------------------------");
}
void WeatherStation::on_pushButtonConnect_clicked()
{
    if (ui->comboBoxDevices->count() == 0) {
        sr->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }
    QString portName = ui->comboBoxDevices->currentText().split(" ").first();
    sr->OpenPort(portName);
}

void WeatherStation::on_pushButtonDisconnect_clicked()
{
    sr->ClosePort();
}

void WeatherStation::on_pushButtonClearLogs_clicked()
{
    // emit sr->ClearLog();
    this->ui->textEditLogs->clear();
}
