#include "logger.h"
#include "qdatetime.h"

Logger::Logger() {}

void Logger::addToLogWindow(QString msg)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    emit AddLog(
        currentDateTime + " "
        + msg); //EMIT NADAJE SYGNAL PRZEZ CO MOZEMY ODEBRAC GO W KLASIE WEATHERSTATION I NASLUCHIWAC I PRZEKAZYWAC DO LOGA
}
