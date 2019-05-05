#include "pruefungdurchfuehren.h"
#include "ui_pruefungdurchfuehren.h"

PruefungDurchfuehren::PruefungDurchfuehren(QWidget *parent, QString *schraubernr) :
    QDialog(parent),
    ui(new Ui::PruefungDurchfuehren)
{
    ui->setupUi(this);
    if (schraubernr->isNull()) {
        dbhelper.verbinden();
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT schraubennr FROM schrauber");
        if (query.exec()) {
            model->setQuery(query);

            ui->schrauberComboBox->setModel(model);
        }
        dbhelper.trennen();
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
    dbhelper.verbinden();
    dbhelper.schauberDb.transaction();
    QSqlQuery insertPruefung;
    insertPruefung.prepare("INSERT INTO pruefung  (schraubennr, datum, kommentar, kosten) values (:schraubennr, :datum, :kommentar, :kosten)");
    insertPruefung.bindValue(":schraubennr", ui->schrauberComboBox->currentText());
    insertPruefung.bindValue(":datum", ui->isoDatum->selectedDate().toString());
    insertPruefung.bindValue(":kommentar",ui->kommentar->toPlainText());
    insertPruefung.bindValue(":kosten", ui->kosten->text().toDouble());

    if (insertPruefung.exec()) {
        QSqlQuery updateKosten;
        updateKosten.prepare("UPDATE schrauber SET gesamtkosten=gesamtkosten+:kosten WHERE schraubennr=:schraubennr");
        updateKosten.bindValue(":kosten", ui->kosten->text().toDouble());
        updateKosten.bindValue(":schraubennr", ui->schrauberComboBox->currentText());
        if(!updateKosten.exec()){
            QMessageBox::critical(
              this,
              tr("Fehler beim Update von Gesamtkosten"),
              updateKosten.lastError().text());
            dbhelper.schauberDb.rollback();
        }
        this->close();
    } else {
        QMessageBox::critical(
          this,
          tr("Die Daten für die Prüfung konnten nicht angelegt werden!"),
          insertPruefung.lastError().text());
   }
   dbhelper.schauberDb.commit();
   dbhelper.trennen();
}
