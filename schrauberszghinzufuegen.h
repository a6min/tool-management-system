#ifndef SCHRAUBERSZGHINZUFUEGEN_H
#define SCHRAUBERSZGHINZUFUEGEN_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <databasehelper.h>
namespace Ui {
class SchrauberSZGHinzufuegen;
}

class SchrauberSZGHinzufuegen : public QDialog
{
    Q_OBJECT

public:
    explicit SchrauberSZGHinzufuegen(QWidget *parent = nullptr, QString *szgref = nullptr);
    ~SchrauberSZGHinzufuegen();

private slots:
    void on_abbrechen_clicked();

    void on_speichern_clicked();

private:
    Ui::SchrauberSZGHinzufuegen *ui;
    QString szgref;
};

#endif // SCHRAUBERSZGHINZUFUEGEN_H
