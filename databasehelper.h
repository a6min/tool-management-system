#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class DatabaseHelper
{
public:
    static DatabaseHelper& getInstance()
    {
        static DatabaseHelper instance; // Guaranteed to be destroyed.
                                        // Instantiated on first use.
        return instance;
    }
    bool verbinden();
    void trennen();
    QSqlDatabase getSchrauberDb() const;
    void setSchrauberDb(const QSqlDatabase &value);
private:
    QSqlDatabase schrauberDb;
    DatabaseHelper() {}                    // Constructor? (the {} brackets) are needed here

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
public:
    DatabaseHelper(DatabaseHelper const&)   = delete;
    void operator=(DatabaseHelper const&)   = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status


};

#endif // DATABASEHELPER_H
