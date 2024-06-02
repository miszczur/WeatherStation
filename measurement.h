#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "qmainwindow.h"
#include <QObject>

class Measurement: public QMainWindow
{
    Q_OBJECT
public:
    Measurement();
    void Append(QString line);
private:
    QList<int> listOfTemperatures;
    QList<int> listOfHumidities;
    int humidity;
    int temperature;

};

#endif // MEASUREMENT_H
