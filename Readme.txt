################# Kompilacja i uruchamianie bazy danych #################

Metoda długa:
1. Instalacja MySQL - należy zainstalować MySQL z serwerem, ponieważ z niego należy wyciągnąć biblioteki potrzebne do kompilacji  - https://dev.mysql.com/downloads/installer/. Użyłam wersji MySQL Installer 8.0.37 i instalacja pełna.
2. Kompilacja biblioteki MySQL w QT (QMYSQL) - Na youtube jest szczegółowa instrukcja, należy postępować dokładnie jak na filmie https://www.youtube.com/watch?v=7YIJUL9pz2U .
3. Kopiowanie bibliotek MySQL do folderu projektu:
	a. C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.dll
	b. C:\Program Files\MySQL\MySQL Server 8.0\bin\libcrypto-3-x64.dll
	c. C:\Program Files\MySQL\MySQL Server 8.0\bin\libssl-3-x64.dll
Wszystkie powyższe pliki należy skopiować do folderu, gdzie jest nasz plik .exe programu, u mnie to C:\Users\XXXXXXX\Desktop\ProjectWeatherStation\WeatherStation\build\Desktop_Qt_6_7_1_MinGW_64_bit-Debug
Oczywiście jeśli używamy buildu Release to tam także należy skopiować powyższe pliki.

Metoda skrócona (niesprawdzona):
0. Wrzuciłam wszystkie potrzebne biblioteki na GH, razem z kodem źródłowym.
1. Skopiować pliki qsqlmysql.debug oraz qsqlmysql.dll do folderu C:\Qt\6.7.1\mingw_64\plugins\sqldrivers
2. Skopiować libmysql.dll, libcrypto-3-x64.dll oraz libssl-3-x64.dll do folderu gdzie jest nasz plik .exe (jak w punkcie 3 metody dłuższej).
