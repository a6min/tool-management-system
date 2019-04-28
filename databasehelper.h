#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class DatabaseHelper
{
public:
    QSqlDatabase schauberDb;
    DatabaseHelper();
    bool verbinden();
    void trennen();
};

#endif // DATABASEHELPER_H
