#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "SerialReader.h"

QT_CHARTS_USE_NAMESPACE

    class Plotter : public QWidget {
    Q_OBJECT

public:
    Plotter(QWidget *parent = nullptr);

private:
    QChartView *chartView;
    QLineSeries *temperatureSeries;
    QLineSeries *humiditySeries;
    QValueAxis *axisX;
    QValueAxis *axisY;

    SerialReader *serialReader;

private slots:
    void updateChart(float temperature, float humidity);

signals:
    void dataReceived(float temperature, float humidity);
};

#endif // PLOTTER_H
