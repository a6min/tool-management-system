#include "schrauberanzeigen.h"
#include "ui_schrauberanzeigen.h"

SchrauberAnzeigen::SchrauberAnzeigen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberAnzeigen)
{
    ui->setupUi(this);
    laden();
}

SchrauberAnzeigen::~SchrauberAnzeigen()
{
    delete ui;
}

void SchrauberAnzeigen::laden()
{
    dbhelper.verbinden();
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("schrauber");
    model->select();
    ui->schrauberTable->setModel(model);
    ui->schrauberTable->setColumnHidden(0, true);
}

void SchrauberAnzeigen::on_schliessen_clicked()
{
    dbhelper.trennen();
    this->close();
}

void SchrauberAnzeigen::on_schrauberTable_clicked(const QModelIndex &index)
{
    foreignKeySZG = ui->schrauberTable->model()->index(index.row() , 10).data().toString();
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("szg");
    model->setFilter("schraubernrz='"+ foreignKeySZG + "'");
    model->select();
    ui->szgTabelle->setModel(model);
    ui->szgTabelle->setColumnHidden(0, true);

    QSqlTableModel *modelPruef = new QSqlTableModel();
    foreignKeySchraubennr = ui->schrauberTable->model()->index(index.row() , 2).data().toString();
    modelPruef->setTable("pruefung");
    modelPruef->setFilter("schraubennr='" + foreignKeySchraubennr + "'");
    modelPruef->select();
    ui->pruefTabelle->setModel(modelPruef);
    ui->pruefTabelle->setColumnHidden(0, true);
}

void SchrauberAnzeigen::on_szgHinzufuegen_clicked()
{

}

void SchrauberAnzeigen::on_pruefen_clicked()
{
    (new PruefungDurchfuehren(this, &foreignKeySchraubennr))->show();
}

void SchrauberAnzeigen::on_neuLaden_clicked()
{
    laden();
}
