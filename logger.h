#ifndef LOGGER_H
#define LOGGER_H

#include "qmainwindow.h"
class Logger : public QMainWindow
{
    Q_OBJECT
public:
    Logger();
signals:
    void AddLog(QString msg);
public slots:
    void addToLogWindow(QString msg);
};

#endif // LOGGER_H
