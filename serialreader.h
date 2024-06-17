#ifndef SERIALREADER_H
#define SERIALREADER_H
#include <QSerialPort>
#include "logger.h"
#include "measurement.h"
#include "qmainwindow.h"

class SerialReader : public QMainWindow
{
    Q_OBJECT
public:

    SerialReader();
    virtual ~SerialReader();
    void PushRecordsToDataBase(void);
    Logger *serialLog; //logger do przesylania danych na okno z informacjami
signals:
    void Log(QString msg); //sygnał do przechwytywania w klasie weatherstation, żeby wyświetlić logi
    void srData(int temperature, int humidity); //sygnał do przechywytwania w klasie weatherstation dla
public slots:
    void OpenPort(QString pn); //otwieranie portu
    void ClosePort();          //zamykanie portu
    void readFromPort();       //czytanie danych z otwartego portu
    bool isOpen();             //metoda do sprawdzania, czy port otwarty
private slots:
    void HandleData(int temperature, int humidity); //metoda do przechwytywania danych z pomiaru i nadawania sygnału srData

private:
    QSerialPort *device;
    Measurement *ms;

};

#endif // SERIALREADER_H
