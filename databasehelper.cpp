#include "databasehelper.h"

const QString DRIVER("QSQLITE");

DatabaseHelper::DatabaseHelper()
{
}

bool DatabaseHelper::verbinden()
{
    bool connected = false;
    if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        QString dbpfad = "data/schrauber.db";
        schauberDb = QSqlDatabase::addDatabase(DRIVER);
        schauberDb.setDatabaseName(dbpfad);
        connected = schauberDb.open();
    }

    return connected;
}

void DatabaseHelper::trennen()
{
    QString connection;
    connection=schauberDb.connectionName();
    schauberDb.close();
    schauberDb=QSqlDatabase();
    schauberDb.removeDatabase(connection);
    schauberDb.removeDatabase(QSqlDatabase::defaultConnection);
    qWarning()<<("Verbindung mit der Datenbank wurde getrennt!");
}



