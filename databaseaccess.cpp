#include "databaseaccess.h"
#include <QDebug>

DataBaseClient::DataBaseClient()
{
    this->dbLog = new Logger();
    // Tworzenie obiektu bazy danych
    db = QSqlDatabase::addDatabase("QMYSQL"); // Stworzenie obiektu bazy danych MyQSL
    db.setHostName("db4free.net");         // Adres serwera
    db.setPort(3306);                      // Port serwera MySQL (domyślnie 3306)
    db.setDatabaseName("mysqldatabase33"); // Nazwa bazy danych
    db.setUserName("mysqluser33");         // Nazwa użytkownika
    db.setPassword("1234TestUser");        // Hasło
}

DataBaseClient::ReturnCodes DataBaseClient::GetAllRowsFromDataBase(vector<WeatherRecord> * records)
{
    // Sprawdzenie parametrow wejsciowych
    if (records == nullptr)
    {
        qDebug() << "Error: Przekazany parametr to NULL.";
        return InputParametersError;
    }

    // Otwarcie bazy danych
    if (!db.open())
    {
        qDebug() << "Nie mozna otworzyc bazy danych: " << db.lastError().text();
        return ConnectionToDataBaseError;
    }

    // Tworzenie zapytania SQL
    QSqlQuery query;

    // Wykonanie zapytania do pobrania danych z tabeli
    if (!query.exec("SELECT DateTime, Temperature, Humidity FROM WeatherData"))
    {
        qDebug() << "Blad wykonania zapytania: " << query.lastError().text();

        // Zamkniecie bazy danych
        db.close();
        return QueryError;
    }

    // Pobieranie danych i zapisywanie ich do wektora
    while (query.next())
    {
        WeatherRecord record;
        record.time = query.value(0).toDateTime();
        record.temperature = query.value(1).toFloat();
        record.humidity = query.value(2).toFloat();

        records->push_back(record);
        //qDebug() << "Temperature:" << record.temperature << ", humidity:" << record.humidity << ", time:" << record.time.toString();
    }

    // Zamkniecie bazy danych
    db.close();

    return NoError;
}

DataBaseClient::ReturnCodes DataBaseClient::AddRecordToDataBase(const WeatherRecord * const newRecord)
{
    // Sprawdzenie parametrow wejsciowych
    if (newRecord == nullptr)
    {
        qDebug() << "Error: Przekazany parametr to NULL.";
        return InputParametersError;
    }

    // Otwarcie bazy danych
    if (!db.open())
    {
        qDebug() << "Nie mozna otworzyc bazy danych: " << db.lastError().text();
        return ConnectionToDataBaseError;
    }

    // Stworzenie zapytania do bazy danych o dodanie wpisu
    QSqlQuery query;
    query.prepare("INSERT INTO WeatherData (DateTime, Temperature, Humidity) VALUES (:DateTime, :Temperature, :Humidity)");
    query.bindValue(":DateTime", newRecord->time);
    query.bindValue(":Temperature", newRecord->temperature);
    query.bindValue(":Humidity", newRecord->humidity);

    // Wykonaj zapytanie (wpis)
    if (!query.exec())
    {
        qDebug() << "Blad wykonania zapytania: " << query.lastError().text();

        // Zamknięcie bazy danych
        db.close();
        return QueryError;
    }

    // Zamknięcie bazy danych
    db.close();
    return NoError;
}

DataBaseClient::ReturnCodes DataBaseClient::AddMultipleRecordsToDataBase(const vector<WeatherRecord> * const newRecords)
{
    // Sprawdzenie parametrow wejsciowych
    if (newRecords == nullptr)
    {
        qDebug() << "Error: Przekazany parametr to NULL.";
        return InputParametersError;
    }

    // Sprawdzenie czy przekazana lista jest pusta
    if (newRecords->empty())
        return NoError; // Lista pusta, czyli nie ma co zapisac -> to nie blad

    // Otwarcie bazy danych
    if (!db.open())
    {
        qDebug() << "Nie mozna otworzyc bazy danych: " << db.lastError().text();
        return ConnectionToDataBaseError;
    }

    for (const WeatherRecord& record : *newRecords)
    {
        // Stworzenie zapytania do bazy danych o dodanie wpisu
        QSqlQuery query;
        query.prepare("INSERT INTO WeatherData (DateTime, Temperature, Humidity) VALUES (:DateTime, :Temperature, :Humidity)");
        query.bindValue(":DateTime", record.time);
        query.bindValue(":Temperature", record.temperature);
        query.bindValue(":Humidity", record.humidity);

        // Wykonaj zapytanie (wpis)
        if (!query.exec())
        {
            qDebug() << "Blad wykonania zapytania: " << query.lastError().text();

            // Zamknięcie bazy danych
            db.close();
            return QueryError;
        }
    }

    // Zamknięcie bazy danych
    db.close();
    return NoError;
}

DataBaseClient::~DataBaseClient() {}
