#include "schrauberszghinzufuegen.h"
#include "ui_schrauberszghinzufuegen.h"

SchrauberSZGHinzufuegen::SchrauberSZGHinzufuegen(QWidget *parent, QString * szgref) :
    QDialog(parent),
    ui(new Ui::SchrauberSZGHinzufuegen)
{
    ui->setupUi(this);
    this->szgref = *szgref;
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
        QSqlQuery insertSZG;
        insertSZG.prepare("INSERT INTO szg (szgref, pfadbedienungsanleitung, kommentar, kosten) VALUES (:szgref, :pfadbedienungsanleitung, :kommentar, :kosten)");
        insertSZG.bindValue(":szgref", this->szgref);
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
}
