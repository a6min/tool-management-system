#ifndef SCHRAUBER_H
#define SCHRAUBER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include "schrauberhinzufuegen.h"

namespace Ui {
class Schrauber;
}

class Schrauber : public QMainWindow
{
    Q_OBJECT

public:
    explicit Schrauber(QWidget *parent = nullptr);
    ~Schrauber();

private slots:
    void on_hinzufuegen_clicked();

private:
    Ui::Schrauber *ui;
    SchrauberHinzufuegen *schrauberHinzufuegen;
};

#endif // SCHRAUBER_H
