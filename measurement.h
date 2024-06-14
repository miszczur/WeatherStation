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
    ~Measurement();
    void Append(QString line);
    void PushRecordsToDataBase(void);

private:
    int humidity;
    int temperature;
    vector<WeatherRecord> newDataBaseRecords; // Wektor wpisow czekajacych na wpis do bazy danych
    DataBaseClient dbClient; // Obiekt dostepu do bazy danych
};

#endif // MEASUREMENT_H
