#ifndef SERIALREADER_H
#define SERIALREADER_H
#include <QSerialPort>
#include "measurement.h"
#include "qmainwindow.h"

class SerialReader : public QMainWindow
{
    Q_OBJECT
public:
    SerialReader();
    virtual ~SerialReader();
signals:
    void Log(QString msg);
    void ClearLog();
public slots:
    void addToLogs(QString msg);
    void OpenPort(QString pn);
    void ClosePort();
    void readFromPort();

private:
    QSerialPort *device;
    Measurement *ms;
};

#endif // SERIALREADER_H
