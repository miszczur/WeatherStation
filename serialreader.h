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
    Logger *serialLog;
    SerialReader();
    virtual ~SerialReader();
signals:
    void Log(QString msg);
    void ClearLog();
public slots:
    void OpenPort(QString pn);
    void ClosePort();
    void readFromPort();

private:
    QSerialPort *device;
    Measurement *ms;
  //  Logger *serialLog;
};

#endif // SERIALREADER_H
