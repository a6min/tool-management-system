#include "pruefungdurchfuehren.h"
#include "ui_pruefungdurchfuehren.h"

PruefungDurchfuehren::PruefungDurchfuehren(QWidget *parent, QString *pruefref, QString *szgref) :
    QDialog(parent),
    ui(new Ui::PruefungDurchfuehren)
{
    this->pruefref = *pruefref;
    this->szgref = *szgref;
    ui->setupUi(this);
}

PruefungDurchfuehren::~PruefungDurchfuehren()
{
    delete ui;
}


void PruefungDurchfuehren::on_abbrechen_clicked()
{
    this->close();
}

void PruefungDurchfuehren::on_speichern_clicked()
{
    if (DatabaseHelper::getInstance().verbinden()) {
        DatabaseHelper::getInstance().getSchrauberDb().transaction();
        QSqlQuery insertPruefung;
        QString pruefungsnr;
        if (this->szgref.isNull() || this->szgref.isEmpty()) {
            pruefungsnr = this->pruefref;
        } else {
            pruefungsnr = this->szgref;
        }
        insertPruefung.prepare("INSERT INTO pruefung  (pruefungsnr, datum, kommentar, kosten) VALUES (:pruefungsnr, :datum, :kommentar, :kosten)");
        insertPruefung.bindValue(":pruefungsnr", pruefungsnr);
        insertPruefung.bindValue(":datum", ui->isoDatum->selectedDate().toString());
        insertPruefung.bindValue(":kommentar",ui->kommentar->toPlainText());
        insertPruefung.bindValue(":kosten", ui->kosten->text().toDouble());

        if (insertPruefung.exec()) {
            QSqlQuery updateKosten;
            if(this->szgref.isNull() || this->szgref.isEmpty()) {
                updateKosten.prepare("UPDATE schrauber SET gesamtkosten=gesamtkosten+:kosten, letzteiso = aktuelleiso, aktuelleiso = :aktuelleiso WHERE pruefref=:pruefref");
                updateKosten.bindValue(":kosten", ui->kosten->text().toDouble());
                updateKosten.bindValue(":pruefref", this->pruefref);
                updateKosten.bindValue(":aktuelleiso", ui->isoDatum->selectedDate().toString());
                if(!updateKosten.exec()){
                    QMessageBox::critical(
                      this,
                      tr("Fehler beim Update von Gesamtkosten"),
                      updateKosten.lastError().text());
                    DatabaseHelper::getInstance().getSchrauberDb().rollback();
                }
            } else {
                double kosten = ui->kosten->text().toDouble();
                updateKosten.prepare("UPDATE szg SET kosten=kosten+:kosten WHERE szgref=:szgref");
                updateKosten.bindValue(":kosten", kosten);
                updateKosten.bindValue(":szgref", this->szgref);
                if(updateKosten.exec()){
                    QSqlQuery updateSchrauber;
                    updateSchrauber.prepare("UPDATE schrauber SET gesamtkosten=gesamtkosten+:kosten WHERE szgref=:szgref");
                    updateSchrauber.bindValue(":kosten", kosten);
                    updateSchrauber.bindValue(":szgref", this->szgref);
                    if(!updateSchrauber.exec()){
                        QMessageBox::critical(
                          this,
                          tr("Fehler beim Update von Gesamtkosten am Schrauber"),
                          updateKosten.lastError().text());
                        DatabaseHelper::getInstance().getSchrauberDb().rollback();
                    }
                }else {
                    QMessageBox::critical(
                      this,
                      tr("Fehler beim Update von Gesamtkosten"),
                      updateKosten.lastError().text());
                    DatabaseHelper::getInstance().getSchrauberDb().rollback();
                }
            }
        } else {
            QMessageBox::critical(
              this,
              tr("Die Daten für die Prüfung konnten nicht angelegt werden!"),
              insertPruefung.lastError().text());
       }
       DatabaseHelper::getInstance().getSchrauberDb().commit();
       this->close();
    }
}
