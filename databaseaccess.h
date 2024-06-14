#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include "logger.h"
#include <QtSql>

using namespace std;

// Definicja struktury WeatherRecord, ktora przechowuje dane o aktualnym odczycie parametrow pogodowych
typedef struct
{
    QDateTime time;
    float temperature;
    float humidity;
} WeatherRecord;

// Definicja klasy DataBaseClient, ktora obsluguje polaczenie z baza danych
class DataBaseClient
{
private:
    QSqlDatabase db; // Przechowuje obiekt bazy danych
    Logger* dbLog;

public:
    DataBaseClient();
    ~DataBaseClient();

    // Definiuje typ wyliczeniowy ReturnCodes, ktory zawiera kody bledow
    typedef enum
    {
        NoError = 0,  // Brak bledu
        ConnectionToDataBaseError, // Blad polaczenia z baza danych
        QueryError, // Blad zapytania SQL
        InputParametersError // Blad parametrow wejsciowych (np. NULL wskaznik)
    } ReturnCodes;

    ReturnCodes GetAllRowsFromDataBase(vector<WeatherRecord> * records); // Metoda zwracajaca wszystkie wiersze z tabeli bazy danych

    ReturnCodes AddRecordToDataBase(const WeatherRecord * const newRecord);  // Funkcja dodajaca nowy rekord do tabeli w bazie danych
    ReturnCodes AddMultipleRecordsToDataBase(const vector<WeatherRecord> * const newRecords); // Funcja dodajca wiele nowych rekordow do tabeli w bazie danych
};

#endif // DATABASEACCESS_H
