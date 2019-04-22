#include "schrauber.h"
#include "ui_schrauber.h"

const QString DRIVER("QSQLITE");

Schrauber::Schrauber(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Schrauber)
{
    ui->setupUi(this);



    if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        QString dbpfad = "data/schrauber.db";
        QSqlDatabase schauberDb = QSqlDatabase::addDatabase(DRIVER);
        schauberDb.setDatabaseName(dbpfad);

        if(!schauberDb.open()){
            qWarning() << "ERROR: " << schauberDb.lastError();
            ui -> statusBar -> showMessage("Fehler beim Verbinden mit der Datenbank!");
        } else {
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

                QSqlQuery erzeugePruefung("CREATE TABLE pruefung (schraubernr TEXT PRIMARY KEY, "
                                     "datum TEXT,"
                                     "kommentar TEXT,"
                                     "kosten REAL)");

                qWarning() << erzeugeSchrauber.isActive();
                ui -> statusBar -> showMessage("Die Tabelle Schrauber wurde erzeugt!");
            }
            ui -> statusBar -> showMessage("Verbunden mit der Datenbank");
        }
    }
    else {

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
