#include "databasehelper.h"

const QString DRIVER("QSQLITE");

QSqlDatabase DatabaseHelper::getSchrauberDb() const
{
    return schrauberDb;
}

void DatabaseHelper::setSchrauberDb(const QSqlDatabase &value)
{
    schrauberDb = value;
}

bool DatabaseHelper::verbinden()
{
    bool connected = false;
    if(schrauberDb.open()) {
        connected = true;
    } else {
        if(QSqlDatabase::isDriverAvailable(DRIVER)) {
            QString dbpfad = "data/schrauber.db";
            schrauberDb = QSqlDatabase::addDatabase(DRIVER);
            schrauberDb.setDatabaseName(dbpfad);
            connected = schrauberDb.open();
        }
    }
    return connected;
}

void DatabaseHelper::trennen()
{
    QString connection;
    connection=schrauberDb.connectionName();
    schrauberDb.close();
    schrauberDb=QSqlDatabase();
    schrauberDb.removeDatabase(connection);
    schrauberDb.removeDatabase(QSqlDatabase::defaultConnection);
    qWarning()<<("Verbindung mit der Datenbank wurde getrennt!");
}



