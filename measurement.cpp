#include "measurement.h"

#include <QDebug>

Measurement::Measurement() {
}

Measurement::~Measurement() {

}

//metoda pobiera dane w Stringu i formatuje je do inta, dodatkowo jest tu także zbieranie danych dla bazy danych
void Measurement::Append(QString line)
{
    //pobranie danych jako string, formatowanie ich do inta
    int posOfHum, posOfTemp, firstPosOfTemp;
    posOfHum = line.indexOf("%");
    firstPosOfTemp = line.indexOf("|") + 1;
    this->humidity = line.left(posOfHum).toInt();
    line.remove(0, firstPosOfTemp);
    posOfTemp = line.indexOf("*C");
    this->temperature = line.left(posOfTemp).toInt();

    //nadanie sygnału newData do przekazania do serialReadera
    emit newData(temperature,humidity);
    // Zapisanie nowego rekordu do wektora
    WeatherRecord record;
    record.time = QDateTime::currentDateTime();
    record.temperature = (float)this->temperature;
    record.humidity = (float)this->humidity;
    newDataBaseRecords.push_back(record);
}

void Measurement::PushRecordsToDataBase(void)
{
    DataBaseClient::ReturnCodes ret;

    // Zapisz wszystkie wpisy w bazie danych
    if ((ret = dbClient.AddMultipleRecordsToDataBase(&newDataBaseRecords)) != DataBaseClient::NoError)
    {
        qDebug() << "Blad podczas zapisu do bazy danych: " << ret;
        return;
    }

    // Wyczysc wektor
    newDataBaseRecords.clear();
}
