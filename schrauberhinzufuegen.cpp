#include "schrauberhinzufuegen.h"
#include "ui_schrauberhinzufuegen.h"
#include "schrauber.h"

SchrauberHinzufuegen::SchrauberHinzufuegen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberHinzufuegen)
{
    Schrauber schrauber;
    ui->setupUi(this);
    connect(this, SIGNAL(schrauber_neuladen()), &schrauber, SLOT(on_schrauber_laden()));
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
    if (DatabaseHelper::getInstance().verbinden()) {
        QSqlQuery insertSchraueberQuery;
        insertSchraueberQuery.prepare("INSERT INTO schrauber (inventarnr, schraubernr,maschnr, anlnr, modellnr, baugruppe,nm, beschreibung, bezeichnung, einstellungenszg, klinge, schraube,gesamtkosten, pfadbedienungsanleitung, szgref, pruefref) "
                                      "VALUES (:inventarnr, :schraubernr, :maschnr, :anlnr, :modellnr, :baugruppe, :nm, :beschreibung, :bezeichnung, :einstellungenszg, :klinge, :schraube, :gesamtkosten, :pfadbedienungsanleitung, :szgref, :pruefref)");


        insertSchraueberQuery.bindValue(":inventarnr", ui->invNr->text());
        insertSchraueberQuery.bindValue(":schraubernr", ui->schrauberNr->text());
        insertSchraueberQuery.bindValue(":maschnr", ui->maschNr->text());
        insertSchraueberQuery.bindValue(":anlnr", ui->anlNr->text().toInt());
        insertSchraueberQuery.bindValue(":modellnr", ui->modelNr->text());
        insertSchraueberQuery.bindValue(":baugruppe", ui->baugruppe->text());
        insertSchraueberQuery.bindValue(":nm", ui->nm->text());
        insertSchraueberQuery.bindValue(":beschreibung", ui->beschreibung->toPlainText());
        insertSchraueberQuery.bindValue(":bezeichnung", ui->bezeichnung->toPlainText());
        insertSchraueberQuery.bindValue(":einstellungenszg", ui->einstellSZG->text());
        insertSchraueberQuery.bindValue(":klinge", ui->klinge->text());
        insertSchraueberQuery.bindValue(":schraube", ui->schraube->text());
        insertSchraueberQuery.bindValue(":gesamtkosten", 0);
        insertSchraueberQuery.bindValue(":pfadbedienungsanleitung", ui->bedienung->text());
        insertSchraueberQuery.bindValue(":szgref", QUuid::createUuid().toString());
        insertSchraueberQuery.bindValue(":pruefref",QUuid::createUuid().toString());

        if(insertSchraueberQuery.exec())
        {
            emit schrauber_neuladen();
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
