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
    Logger *serialLog;
signals:
    void Log(QString msg);
    void ClearLog();
    void srData(int temperature, int humidity);
public slots:
    void OpenPort(QString pn);
    void ClosePort();
    void readFromPort();
    bool isOpen();
private slots:
    void HandleData(int temperature, int humidity);

private:
    QSerialPort *device;
    Measurement *ms;

};

#endif // SERIALREADER_H
