#ifndef SCHRAUBERHINZUFUEGEN_H
#define SCHRAUBERHINZUFUEGEN_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

#include "databasehelper.h"
namespace Ui {
class SchrauberHinzufuegen;
}

class SchrauberHinzufuegen : public QDialog
{
    Q_OBJECT

public:
    explicit SchrauberHinzufuegen(QWidget *parent = nullptr);
    ~SchrauberHinzufuegen();

private slots:
    void on_speichern_clicked();

    void on_abbrechen_clicked();
    
    
private:
    Ui::SchrauberHinzufuegen *ui;
    DatabaseHelper *dbhelper;
};

#endif // SCHRAUBERHINZUFUEGEN_H
