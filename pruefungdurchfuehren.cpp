#include "pruefungdurchfuehren.h"
#include "ui_pruefungdurchfuehren.h"

PruefungDurchfuehren::PruefungDurchfuehren(QWidget *parent, QString *schraubernr) :
    QDialog(parent),
    ui(new Ui::PruefungDurchfuehren)
{
    ui->setupUi(this);
    if (schraubernr->isNull()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT schraubennr FROM schrauber");
        if (query.exec()) {
            model->setQuery(query);

            ui->schrauberComboBox->setModel(model);
        }
    } else {
        ui->schrauberComboBox->addItem(*schraubernr);
    }
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
        insertPruefung.prepare("INSERT INTO pruefung  (pruefungsnr, datum, kommentar, kosten) VALUES (:pruefungsnr, :datum, :kommentar, :kosten)");
        insertPruefung.bindValue(":pruefungsnr", ui->schrauberComboBox->currentText());
        insertPruefung.bindValue(":datum", ui->isoDatum->selectedDate().toString());
        insertPruefung.bindValue(":kommentar",ui->kommentar->toPlainText());
        insertPruefung.bindValue(":kosten", ui->kosten->text().toDouble());

        if (insertPruefung.exec()) {
            QSqlQuery updateKosten;
            updateKosten.prepare("UPDATE schrauber SET gesamtkosten=gesamtkosten+:kosten, letzteiso = aktuelleiso, aktuelleiso = :aktuelleiso WHERE schraubernr=:schraubernr");
            updateKosten.bindValue(":kosten", ui->kosten->text().toDouble());
            updateKosten.bindValue(":schraubernr", ui->schrauberComboBox->currentText());
            updateKosten.bindValue(":aktuelleiso", ui->isoDatum->selectedDate().toString());
            if(!updateKosten.exec()){
                QMessageBox::critical(
                  this,
                  tr("Fehler beim Update von Gesamtkosten"),
                  updateKosten.lastError().text());
                DatabaseHelper::getInstance().getSchrauberDb().rollback();
            }
            this->close();
        } else {
            QMessageBox::critical(
              this,
              tr("Die Daten für die Prüfung konnten nicht angelegt werden!"),
              insertPruefung.lastError().text());
       }
       DatabaseHelper::getInstance().getSchrauberDb().commit();
    }
}
