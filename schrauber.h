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
#include "pruefungdurchfuehren.h"
#include <schrauberszghinzufuegen.h>

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

    void on_actionSchliessen_triggered();

    void on_szgHinzufuegen_clicked();

    void on_pruefen_clicked();

    void on_schrauberTabelle_clicked(const QModelIndex &index);

    void on_neuLaden_clicked();

    void on_szgTabelle_clicked(const QModelIndex &index);

    void on_schrauber_laden();

private:
    Ui::Schrauber *ui;
    QString foreignKeyPruefung;
    QString foreignKeySZG;
    QString foreignKeyPruefungSZG;
    void dbTabellePruefenUndErzeugen();
    void schrauberLaden();
};

#endif // SCHRAUBER_H
