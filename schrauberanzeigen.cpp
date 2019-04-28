#include "schrauberanzeigen.h"
#include "ui_schrauberanzeigen.h"

SchrauberAnzeigen::SchrauberAnzeigen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberAnzeigen)
{
    ui->setupUi(this);

    dbhelper.verbinden();
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("schrauber");
    model->select();
    ui->schrauberTable->setModel(model);


}

SchrauberAnzeigen::~SchrauberAnzeigen()
{
    delete ui;
}

void SchrauberAnzeigen::on_schliessen_clicked()
{
    dbhelper.trennen();
    this->close();
}

void SchrauberAnzeigen::on_schrauberTable_clicked(const QModelIndex &index)
{
   // QModelIndex rowIndex=ui->schrauberTable->selectionModel()->currentIndex();
    //QVariant value=index.sibling(index.row(),"schraubernr").data();

    QString foreignKeySZG = ui->schrauberTable->model()->index(index.row() , 10).data().toString();
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("szg");
    model->setFilter("schraubernrz='"+ foreignKeySZG + "'");
    model->select();
    ui->szgTabelle->setModel(model);
    //ui->szgTabelle->setMinimumHeight(ui->szgTabelle->horizontalHeader()->height() + ui->szgTabelle->rowHeight(0));
}
