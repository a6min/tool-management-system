#ifndef PRUEFUNGDURCHFUEHREN_H
#define PRUEFUNGDURCHFUEHREN_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include "databasehelper.h"

namespace Ui {
class PruefungDurchfuehren;
}

class PruefungDurchfuehren : public QDialog
{
    Q_OBJECT

public:
    explicit PruefungDurchfuehren(QWidget *parent = nullptr, QString *pruefref = nullptr, QString *szgref= nullptr);
    ~PruefungDurchfuehren();


private slots:
    void on_abbrechen_clicked();

    void on_speichern_clicked();

private:
    Ui::PruefungDurchfuehren *ui;
    QString pruefref;
    QString szgref;
};

#endif // PRUEFUNGDURCHFUEHREN_H
