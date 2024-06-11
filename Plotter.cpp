#include "Plotter.h"
#include <QVBoxLayout>
#include <QDateTime>

Plotter::Plotter(QWidget *parent) : QWidget(parent) {
    chartView = new QChartView(new QChart());
    temperatureSeries = new QLineSeries();
    humiditySeries = new QLineSeries();
    axisX = new QValueAxis();
    axisY = new QValueAxis();

    chartView->chart()->addSeries(temperatureSeries);
    chartView->chart()->addSeries(humiditySeries);
    chartView->chart()->setAxisX(axisX, temperatureSeries);
    chartView->chart()->setAxisX(axisX, humiditySeries);
    chartView->chart()->setAxisY(axisY, temperatureSeries);
    chartView->chart()->setAxisY(axisY, humiditySeries);

    axisX->setTickCount(10);
    axisY->setRange(0, 100);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

    serialReader = new SerialReader("COM3", 9600); // Ustaw odpowiedni port
    connect(this, &Plotter::dataReceived, this, &Plotter::updateChart);

    serialReader->startReading([this](float temperature, float humidity) {
        emit dataReceived(temperature, humidity);
    });
}

void Plotter::updateChart(float temperature, float humidity) {
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    temperatureSeries->append(timestamp, temperature);
    humiditySeries->append(timestamp, humidity);

    if (temperatureSeries->count() > 100) {
        temperatureSeries->remove(0);
        humiditySeries->remove(0);
    }

    axisX->setRange(timestamp - 60000, timestamp); // Pokaż ostatnią minutę danych
}
