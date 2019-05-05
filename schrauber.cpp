#include "schrauber.h"
#include "ui_schrauber.h"


void Schrauber::dbTabellePruefenUndErzeugen()
{
    if (DatabaseHelper::getInstance().verbinden())
    {
            QSqlQuery querySchrauber("SELECT * FROM schrauber");
            if (!querySchrauber.isActive()) {
                QSqlQuery entferneSchrauber("DROP TABLE schrauber");
                QSqlQuery entferneSZG("DROP TABLE szg");
                QSqlQuery entfernePruefung("DROP TABLE pruefung");
                QSqlQuery erzeugeSchrauber("CREATE TABLE schrauber (id INTEGER PRIMARY KEY, "
                                           "inventarnr INTEGER, "
                                           "schraubernr TEXT UNIQUE, "
                                           "maschnr TEXT, "
                                           "anlnr INTEGER, "
                                           "modellnr TEXT, "
                                           "baugruppe TEXT, "
                                           "beschreibung TEXT, "
                                           "bezeichnung TEXT, "
                                           "nm TEXT,"
                                           "schraubernrz TEXT UNIQUE,"
                                           "einstellungenszg TEXT, "
                                           "klinge TEXT, "
                                           "schraube TEXT, "
                                           "gesamtkosten REAL, "
                                           "pfadbedienungsanleitung TEXT, "
                                           "letzteiso TEXT, "
                                           "aktuelleiso TEXT, "
                                           "historieiso TEXT,"
                                           "FOREIGN KEY (schraubernrz) REFERENCES szg (schraubernrz),"
                                           "FOREIGN KEY (schraubernr) REFERENCES pruefung (pruefungsnr))");
                QSqlQuery erzeugeSZG("CREATE TABLE szg (id INTEGER PRIMARY KEY, "
                                     "schraubernrz TEXT, "
                                     "pfadbedienungsanleitung TEXT,"
                                     "kommentar TEXT,"
                                     "kosten REAL,"
                                     "FOREIGN KEY (schraubernrz) REFERENCES pruefung (pruefungsnr))");

                QSqlQuery erzeugePruefung("CREATE TABLE pruefung (id INTEGER PRIMARY KEY,"
                                        "pruefungsnr TEXT, "
                                        "datum TEXT,"
                                        "kommentar TEXT,"
                                        "kosten REAL)");

                qWarning() << erzeugeSchrauber.isActive();
                ui -> statusBar -> showMessage("Die Tabelle Schrauber wurde erzeugt!");
            }
    } else {
        QMessageBox::critical(
          this,
          tr("Fehler beim Verbinden mit der Database."),
          tr("Bitte starten Sie die Anwendung neu!") );
    }
}

Schrauber::Schrauber(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Schrauber)
{
    ui->setupUi(this);
    dbTabellePruefenUndErzeugen();
    schrauberLaden();
    ui->statusBar->showMessage("Die Anwendung wurde erfolgreich gestartet");
}


Schrauber::~Schrauber()
{
    delete ui;
}


void Schrauber::schrauberLaden()
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("schrauber");
    model->select();
    ui->schrauberTabelle->setModel(model);
    ui->schrauberTabelle->setColumnHidden(0, true);
}

void Schrauber::on_hinzufuegen_clicked()
{
    (new SchrauberHinzufuegen(this))->show();
}

void Schrauber::on_actionSchliessen_triggered()
{
    DatabaseHelper::getInstance().trennen();
    QApplication::quit();
}

void Schrauber::on_szgHinzufuegen_clicked()
{
    (new SchrauberSZGHinzufuegen(this, &foreignKeySZG))->show();
}

void Schrauber::on_pruefen_clicked()
{
     (new PruefungDurchfuehren(this, &foreignKeySchraubernr))->show();
}

void Schrauber::on_schrauberTabelle_clicked(const QModelIndex &index)
{
    foreignKeySZG = ui->schrauberTabelle->model()->index(index.row() , 10).data().toString();
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("szg");
    model->setFilter("schraubernrz='"+ foreignKeySZG + "'");
    model->select();
    ui->szgTabelle->setModel(model);
    ui->szgTabelle->setColumnHidden(0, true);

    QSqlTableModel *modelPruef = new QSqlTableModel();
    foreignKeySchraubernr = ui->schrauberTabelle->model()->index(index.row() , 2).data().toString();
    modelPruef->setTable("pruefung");
    modelPruef->setFilter("pruefungsnr='" + foreignKeySchraubernr + "'");
    modelPruef->select();
    ui->pruefTabelle->setModel(modelPruef);
    ui->pruefTabelle->setColumnHidden(0, true);
}

void Schrauber::on_neuLaden_clicked()
{
    schrauberLaden();
}
