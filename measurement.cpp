#include "measurement.h"

#include <QDebug>

Measurement::Measurement() {}

void Measurement::Append(QString line)
{
    int posOfHum, posOfTemp, firstPosOfTemp;
    WeatherRecord newDataBaseRecord;
    //  qDebug() << line;
    posOfHum = line.indexOf("%");
    firstPosOfTemp = line.indexOf("|") + 1;
    this->humidity = line.left(posOfHum).toInt();
    listOfHumidities.append(line.left(posOfHum).toInt());
    line.remove(0, firstPosOfTemp);
    posOfTemp = line.indexOf("*C");
    this->temperature = line.left(posOfTemp).toInt();
    listOfTemperatures.append(line.left(posOfTemp).toInt());
    // qDebug() << humidity << temperature;

    // Wpisanie rekordu do bazy danych
    newDataBaseRecord.time = QDateTime::currentDateTime();
    newDataBaseRecord.temperature = (float)this->temperature;
    newDataBaseRecord.humidity = (float)this->humidity;
    dbClient.AddRecordToDataBase(&newDataBaseRecord);
}
