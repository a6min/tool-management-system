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
        insertSchraueberQuery.prepare("INSERT INTO schrauber (inventarnr, schraubennr,maschnr, anlnr, modellnr, baugruppe, beschreibung, bezeichnung, einstellungenszg, klinge, schraube, pfadbedienungsanleitung) "
                                      "VALUES (:inventarnr, :schraubennr, :maschnr, :anlnr, :modellnr, :baugruppe, :beschreibung, :bezeichnung, :einstellungenszg, :klinge, :schraube, :pfadbedienungsanleitung)");

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
        insertSchraueberQuery.bindValue(":pfadbedienungsanleitung", ui->bedienung->text());

        if(insertSchraueberQuery.exec())
        {
            dbhelper->trennen();
            this->close();
        }
        else
        {
            QMessageBox::critical(
              this,
              tr("Der Schrauber konnte nicht angelegt werden!"),
              insertSchraueberQuery.lastError().text());
        }
    } else {
        QMessageBox::critical(
          this,
          tr("Fehler beim Verbinden mit der Database."),
          tr("Der Schrauber wurde nicht anglegt.") );
    }
}

