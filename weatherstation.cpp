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
    sr = new SerialReader();
    log = new Logger();
    connect(this->log,               //nasluchujemy czy przychodzi sygnal AddLog i dodajemy komunikat
            SIGNAL(AddLog(QString)),
            this->ui->textEditLogs,
            SLOT(append(QString)));
    connect(sr->serialLog,
            SIGNAL(AddLog(QString)), //nasluchujemy czy przychodzi sygnal AddLog z obiektu serialreader i dodajemy komunikat
            this->ui->textEditLogs,
            SLOT(append(QString)));
}

WeatherStation::~WeatherStation()
{
    delete device;
    delete sr;
    delete ui;
}

void WeatherStation::on_pushButtonSearch_clicked()
{
    //dodanie do comboboxa listy wykrytych urzadzen
    ui->comboBoxDevices->clear();
    log->addToLogWindow("Szukam urządzeń...");
    log->addToLogWindow("----------------------------------------");
    //Wyszukanie urzadzen wykrytych jako port COM i dodanie ich do comboboxa w widoku glownym
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();
    for (int i = 0; i < devices.count(); i++) {
        QString name = devices.at(i).portName() + " (" + devices.at(i).description() + ")";
        log->addToLogWindow(name);
        ui->comboBoxDevices->addItem(name);
    }

    log->addToLogWindow("----------------------------------------");
}
void WeatherStation::on_pushButtonConnect_clicked()
{
    // zabezpieczenie przed wykryciem pustej lisity urzadzen
    if (ui->comboBoxDevices->count() == 0) {
        log->addToLogWindow("Nie wykryto żadnych urządzeń!");
        return;
    }
    else{
    QString portName = ui->comboBoxDevices->currentText().split(" ").first();
    sr->OpenPort(portName);
    }

}

void WeatherStation::on_pushButtonDisconnect_clicked()
{
    //zamkniecie   portu COM
    sr->ClosePort();

    // TEST: Wpisanie rekordu do bazy danych
    /*WeatherRecord record;
    record.time = QDateTime::currentDateTime();
    record.temperature = 72.3;
    record.humidity = 99.2;
    dbClient.AddRecordToDataBase(&record);*/
}

void WeatherStation::on_pushButtonClearLogs_clicked()
{
    // emit sr->ClearLog();
    this->ui->textEditLogs->clear();


    // TEST: odczytu calej tablicy z bazy danych (wyswietla wyniki do gDebug)
    /*vector<WeatherRecord> records;
    dbClient.GetAllRowsFromDataBase(&records); // do usuniecia!!!!!!!!!!!!!!
    records.clear();*/
}

void WeatherStation::on_pushButtonSendToDB_clicked()
{
    // Wyslij wszystkie zapisane rekordy do bazy danych
      sr->PushRecordsToDataBase();
}

