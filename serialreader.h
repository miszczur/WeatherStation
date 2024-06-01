#ifndef SERIALREADER_H
#define SERIALREADER_H
#include "qmainwindow.h"
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui {
class WeatherStation;
}
QT_END_NAMESPACE
class SerialReader: public QMainWindow
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
    QSerialPort* device;
};

#endif // SERIALREADER_H
