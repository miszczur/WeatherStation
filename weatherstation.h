#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H
#include <QMainWindow>
#include "logger.h"
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
signals:
private slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonConnect_clicked();
    void on_pushButtonDisconnect_clicked();
    void on_pushButtonClearLogs_clicked();

private:
    Ui::WeatherStation *ui;
    QSerialPort *device;
    SerialReader *sr;
    Logger* log;
};
#endif // WEATHERSTATION_H
