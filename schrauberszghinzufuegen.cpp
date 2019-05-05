#include "schrauberszghinzufuegen.h"
#include "ui_schrauberszghinzufuegen.h"

SchrauberSZGHinzufuegen::SchrauberSZGHinzufuegen(QWidget *parent, QString * schraubernrz) :
    QDialog(parent),
    ui(new Ui::SchrauberSZGHinzufuegen)
{
    ui->setupUi(this);

        if (DatabaseHelper::getInstance().verbinden()) {
            QSqlQueryModel *model = new QSqlQueryModel();
            QSqlQuery query;
            if (schraubernrz->isNull()) {
                query.prepare("SELECT schraubernr FROM schrauber");
            } else {
                query.prepare("SELECT schraubernr FROM schrauber WHERE schraubernrz=:schraubernrz");
                query.bindValue(":schraubernrz", *schraubernrz);
            }
            if (query.exec()) {
                model->setQuery(query);

                ui->schrauberComboBox->setModel(model);
            }
        } else {
            QMessageBox::critical(
              this,
              tr("Fehler beim Verbinden mit der Database."),
              tr("Bitte versuchen Sie erneut.") );
        }
}

SchrauberSZGHinzufuegen::~SchrauberSZGHinzufuegen()
{
    delete ui;
}

void SchrauberSZGHinzufuegen::on_abbrechen_clicked()
{
     this->close();
}

void SchrauberSZGHinzufuegen::on_speichern_clicked()
{
    QSqlQuery sucheSchraubernrZ;
    sucheSchraubernrZ.prepare("SELECT schraubernrz FROM schrauber WHERE schraubernr=:schraubernr");
    sucheSchraubernrZ.bindValue(":schraubernr", ui->schrauberComboBox->currentText());

    if (sucheSchraubernrZ.exec()) {
         QString schraubernrZ = sucheSchraubernrZ.value(0).toString();
         QSqlQuery insertSZG;
         insertSZG.prepare("INSERT INTO szg (schraubernrz, pfadbedienungsanleitung, kommentar, kosten) VALUES (:schraubernrz, :pfadbedienungsanleitung, :kommentar, :kosten)");
         insertSZG.bindValue(":schraubernrz", schraubernrZ);
         insertSZG.bindValue(":pfadbedienungsanleitung", ui->bedienung->text());
         insertSZG.bindValue(":kommentar", ui->kommentar->toPlainText());
         insertSZG.bindValue(":kosten", 0.0);
         if(!insertSZG.exec()){
             QMessageBox::critical(
               this,
               tr("Fehler beim hinzufügen von SZG"),
               insertSZG.lastError().text());
         }
         this->close();
    } else {
        QMessageBox::critical(
          this,
          tr("Fehler beim Suchen von Schraubernummer für SZG"),
          sucheSchraubernrZ.lastError().text());
    }
}
