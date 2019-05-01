#include "schrauber.h"
#include "ui_schrauber.h"


Schrauber::Schrauber(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Schrauber)
{
    ui->setupUi(this);
    DatabaseHelper *dbhelper = new DatabaseHelper();
    if (dbhelper->verbinden())
    {
            QSqlQuery querySchrauber("SELECT * FROM schrauber");
            if (!querySchrauber.isActive()) {
                QSqlQuery entferneSchrauber("DROP TABLE schrauber");
                QSqlQuery entferneSZG("DROP TABLE szg");
                QSqlQuery entfernePruefung("DROP TABLE pruefung");
                QSqlQuery erzeugeSchrauber("CREATE TABLE schrauber (id INTEGER PRIMARY KEY, "
                                           "inventarnr INTEGER, "
                                           "schraubennr TEXT, "
                                           "maschnr TEXT, "
                                           "anlnr INTEGER, "
                                           "modellnr TEXT, "
                                           "baugruppe TEXT, "
                                           "beschreibung TEXT, "
                                           "bezeichnung TEXT, "
                                           "nm TEXT,"
                                           "schraubernrz TEXT,"
                                           "einstellungenszg TEXT, "
                                           "klinge TEXT, "
                                           "schraube TEXT, "
                                           "gesamtkosten REAL, "
                                           "pfadbedienungsanleitung TEXT, "
                                           "letzteiso TEXT, "
                                           "aktuelleiso TEXT, "
                                           "historieiso TEXT,"
                                           "FOREIGN KEY (schraubernrz) REFERENCES szg (schraubernrz),"
                                           "FOREIGN KEY (schraubennr) REFERENCES pruefung (schraubernr))");
                QSqlQuery erzeugeSZG("CREATE TABLE szg (schraubernrz TEXT PRIMARY KEY, "
                                     "pfadbedienungsanleitung TEXT,"
                                     "pruefung TEXT,"
                                     "historiewartung TEXT,"
                                     "kommentar TEXT,"
                                     "kosten REAL)");

                QSqlQuery erzeugePruefung("CREATE TABLE pruefung (schraubennr TEXT PRIMARY KEY, "
                                     "datum TEXT,"
                                     "kommentar TEXT,"
                                     "kosten REAL)");

                qWarning() << erzeugeSchrauber.isActive();
                ui -> statusBar -> showMessage("Die Tabelle Schrauber wurde erzeugt!");
            }
            dbhelper->trennen();
            //ui -> statusBar -> showMessage("Verbunden mit der Datenbank");
    } else {
        QMessageBox::critical(
          this,
          tr("Fehler beim Verbinden mit der Database."),
          tr("Bitte starten Sie die Anwendung neu!") );
    }
}


Schrauber::~Schrauber()
{
    delete ui;
}

void Schrauber::on_hinzufuegen_clicked()
{
    schrauberHinzufuegen = new SchrauberHinzufuegen(this);
    schrauberHinzufuegen -> show();
}


void Schrauber::on_laden_clicked()
{
    schrauberAnzeigen = new SchrauberAnzeigen(this);
    schrauberAnzeigen->show();
}

void Schrauber::on_pushButton_clicked()
{
    pruefungDurchfueren = new PruefungDurchfuehren(this);
    pruefungDurchfueren->show();
}
