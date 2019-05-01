#ifndef SCHRAUBER_H
#define SCHRAUBER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include "schrauberhinzufuegen.h"
#include "databasehelper.h"
#include "schrauberanzeigen.h"
#include "pruefungdurchfuehren.h"

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

    void on_laden_clicked();

    void on_pushButton_clicked();

    void on_actionSchliessen_triggered();

private:
    Ui::Schrauber *ui;
    SchrauberHinzufuegen *schrauberHinzufuegen;
    SchrauberAnzeigen *schrauberAnzeigen;
    PruefungDurchfuehren *pruefungDurchfueren;
    DatabaseHelper dbhelper;
};

#endif // SCHRAUBER_H
