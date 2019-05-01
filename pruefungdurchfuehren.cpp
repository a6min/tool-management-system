#include "pruefungdurchfuehren.h"
#include "ui_pruefungdurchfuehren.h"

PruefungDurchfuehren::PruefungDurchfuehren(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PruefungDurchfuehren)
{
    ui->setupUi(this);

    dbhelper.verbinden();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT schraubennr FROM schrauber");
    if (query.exec()) {
        model->setQuery(query);

        ui->schrauberComboBox->setModel(model);
    }
    dbhelper.trennen();

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
    QSqlQuery insertPruefung;
    insertPruefung.prepare("INSERT INTO pruefung  (schraubennr, datum, kommentar, kosten) values (:schraubennr, :datum, :kommentar, :kosten)");
    insertPruefung.bindValue(":schraubennr", ui->schrauberComboBox->currentText());
    insertPruefung.bindValue(":datum", ui->isoDatum->selectedDate().toString());
    insertPruefung.bindValue(":kommentar",ui->kommentar->toPlainText());
    insertPruefung.bindValue(":kosten", ui->kosten->text().toDouble());

    if (insertPruefung.exec()) {
        this->close();
    } else {
        QMessageBox::critical(
          this,
          tr("Der Schrauber konnte nicht angelegt werden!"),
          insertPruefung.lastError().text());
   }

   dbhelper.trennen();
}
