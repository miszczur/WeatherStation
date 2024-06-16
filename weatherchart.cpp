#include "WeatherChart.h"

WeatherChart::WeatherChart(QWidget *parent)
    : QChartView(parent), dataCount(0)
{
    temperatureSeries = new QLineSeries();
    humiditySeries = new QLineSeries();
    chart = new QChart();
    axisX = new QValueAxis();
    axisY = new QValueAxis();

    setupChart();
}

void WeatherChart::setupChart()
{
    temperatureSeries->setName("°C");
    humiditySeries->setName("% RH");
    chart->setBackgroundBrush(QBrush(QColor("black")));
    chart->addSeries(temperatureSeries);
    chart->addSeries(humiditySeries);

    chart->setAxisX(axisX, temperatureSeries);
    chart->setAxisX(axisX, humiditySeries);
    chart->setAxisY(axisY, temperatureSeries);
    chart->setAxisY(axisY, humiditySeries);

    axisX->setTitleText("Nr pomiaru");
    axisY->setTitleText("Wartość");

    axisX->setRange(0, 5);
    axisY->setRange(0, 100);

    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void WeatherChart::addDataPoint(double temperature, double humidity)
{
    temperatureSeries->append(dataCount, temperature);
    humiditySeries->append(dataCount, humidity);
    dataCount++;

    if (dataCount > axisX->max()) {
        axisX->setMax(dataCount);
    }
}
void WeatherChart::clearChart()
{
    dataCount = 0;
    axisX->setRange(0, 5);
    axisY->setRange(0, 100);
    temperatureSeries->clear();
    humiditySeries->clear();
}
