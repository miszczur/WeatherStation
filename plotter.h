#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>



    class Plotter : public QWidget
{
    Q_OBJECT

public:
    explicit Plotter(QWidget *parent = nullptr);

public slots:
    void updateChart(int temperature, int humidity);

private:
    QChartView *chartView;
    QLineSeries *temperatureSeries;
    QLineSeries *humiditySeries;
    QValueAxis *axisX;
    QValueAxis *axisY;
};

#endif // PLOTTER_H
