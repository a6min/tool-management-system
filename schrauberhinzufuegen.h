#ifndef SCHRAUBERHINZUFUEGEN_H
#define SCHRAUBERHINZUFUEGEN_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QUuid>
#include <QDebug>

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

signals:
    void schrauber_neuladen();
    
    
private:
    Ui::SchrauberHinzufuegen *ui;
};

#endif // SCHRAUBERHINZUFUEGEN_H
