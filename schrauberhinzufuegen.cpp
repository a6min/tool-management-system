#include "schrauberhinzufuegen.h"
#include "ui_schrauberhinzufuegen.h"

SchrauberHinzufuegen::SchrauberHinzufuegen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberHinzufuegen)
{
    ui->setupUi(this);
    dbhelper = new DatabaseHelper();
}

SchrauberHinzufuegen::~SchrauberHinzufuegen()
{
    delete ui;
}

void SchrauberHinzufuegen::on_abbrechen_clicked()
{
    this->close();
}

void SchrauberHinzufuegen::on_speichern_clicked()
{
    if (dbhelper->verbinden()) {
        QSqlQuery insertSchraueberQuery;
        insertSchraueberQuery.prepare("INSERT INTO schrauber (inventarnr, schraubennr,maschnr, anlnr, modellnr, baugruppe, beschreibung, bezeichnung, einstellungenszg, klinge, schraube,gesamtkosten, pfadbedienungsanleitung, schraubernrz) "
                                      "VALUES (:inventarnr, :schraubennr, :maschnr, :anlnr, :modellnr, :baugruppe, :beschreibung, :bezeichnung, :einstellungenszg, :klinge, :schraube, :gesamtkosten, :pfadbedienungsanleitung, :schraubernrz)");

        insertSchraueberQuery.bindValue(":inventarnr", ui->invNr->text());
        insertSchraueberQuery.bindValue(":schraubennr", ui->schraubenNr->text());
        insertSchraueberQuery.bindValue(":maschnr", ui->maschNr->text());
        insertSchraueberQuery.bindValue(":anlnr", ui->anlNr->text().toInt());
        insertSchraueberQuery.bindValue(":modellnr", ui->modelNr->text());
        insertSchraueberQuery.bindValue(":baugruppe", ui->baugruppe->text());
        insertSchraueberQuery.bindValue(":beschreibung", ui->beschreibung->toPlainText());
        insertSchraueberQuery.bindValue(":bezeichnung", ui->bezeichnung->toPlainText());
        insertSchraueberQuery.bindValue(":einstellungenszg", ui->einstellSZG->text());
        insertSchraueberQuery.bindValue(":klinge", ui->klinge->text());
        insertSchraueberQuery.bindValue(":schraube", ui->schraube->text());
        insertSchraueberQuery.bindValue(":gesamtkosten", 0);
        insertSchraueberQuery.bindValue(":pfadbedienungsanleitung", ui->bedienung->text());
        insertSchraueberQuery.bindValue(":schraubernrz", ui->SZGNr->text());

        if(insertSchraueberQuery.exec())
        {
            QSqlQuery insertSZGQuery;
            insertSZGQuery.prepare("INSERT INTO szg (schraubernrz, pfadbedienungsanleitung, kommentar) VALUES (:schraubernrz, :pfadbedienungsanleitung, :kommentar)");
            insertSZGQuery.bindValue(":schraubernrz", ui->SZGNr->text());
            insertSZGQuery.bindValue(":pfadbedienungsanleitung", ui->bedienung_SZG->text());
            insertSZGQuery.bindValue(":kommentar", ui->kommentarSZG->toPlainText());
            if (!insertSZGQuery.exec()) {
                QMessageBox::critical(
                  this,
                  tr("SZG zum Schrauber konnte nicht angelegt werden!"),
                  insertSZGQuery.lastError().text());
            }
            this->close();
        }
        else
        {
            QMessageBox::critical(
              this,
              tr("Der Schrauber konnte nicht angelegt werden!"),
              insertSchraueberQuery.lastError().text());
        }
        dbhelper->trennen();
    } else {
        QMessageBox::critical(
          this,
          tr("Fehler beim Verbinden mit der Database."),
          tr("Der Schrauber wurde nicht anglegt.") );
    }
}

