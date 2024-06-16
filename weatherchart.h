#ifndef WEATHERCHART_H
#define WEATHERCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QWidget>


class WeatherChart : public QChartView
{
    Q_OBJECT

public:
    WeatherChart(QWidget *parent = nullptr);
    void clearChart();
public slots:
    void addDataPoint(double temperature, double humidity);
private:
    QLineSeries *temperatureSeries;
    QLineSeries *humiditySeries;
    QChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
    int dataCount;
    void setupChart();

};

#endif // WEATHERCHART_H
