#ifndef SERIALREADER_H
#define SERIALREADER_H
#include <QSerialPort>
namespace Ui {
class WeatherStation;
}
class SerialReader
{
public:
    SerialReader();
  virtual ~SerialReader();
private slots:
    void readFromPort();
private:
    QSerialPort* device;
};

#endif // SERIALREADER_H
