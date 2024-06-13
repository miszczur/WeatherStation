#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include "qmainwindow.h"
#include "databaseaccess.h"

class Measurement : public QMainWindow
{
    Q_OBJECT
public:
    Measurement();
    void Append(QString line);

private:
    int humidity;
    int temperature;
    DataBaseClient dbClient; // Obiekt dostepu do bazy danych
    WeatherRecord newDataBaseRecord;
};

#endif // MEASUREMENT_H
