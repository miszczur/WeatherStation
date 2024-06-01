#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <QMainWindow>
#include <QSerialPort>
#include "serialreader.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class WeatherStation;
}
QT_END_NAMESPACE

class WeatherStation : public QMainWindow
{
    Q_OBJECT

public:
    WeatherStation(QWidget *parent = nullptr);
    ~WeatherStation();
private slots:

    void on_pushButtonSearch_clicked();
    void addToLogs(QString message);
    void on_pushButtonConnect_clicked();
    void on_pushButtonDisconnect_clicked();
    void readFromPort();

    void on_pushButtonClearLogs_clicked();

private:
    Ui::WeatherStation *ui;
    QSerialPort* device;
    SerialReader* sr;
};
#endif // WEATHERSTATION_H

