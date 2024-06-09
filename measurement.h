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
    QList<int> listOfTemperatures; //stworzylem liste odczytow temperatur, w zaleznosci od potrzeby i budowy dalej mozna ja wykorzystywac, tak samo liste wilgotnosci
    QList<int> listOfHumidities;
    int humidity;
    int temperature;
    DataBaseClient dbClient; // Obiekt dostepu do bazy danych
};

#endif // MEASUREMENT_H
