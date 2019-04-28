#include "schrauberanzeigen.h"
#include "ui_schrauberanzeigen.h"

SchrauberAnzeigen::SchrauberAnzeigen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberAnzeigen)
{
    ui->setupUi(this);
    DatabaseHelper dbhelper;
    dbhelper.verbinden();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *alleSchrauberHolen = new QSqlQuery();
    alleSchrauberHolen->prepare("select * from schrauber");
    alleSchrauberHolen->exec();

    model->setQuery(*alleSchrauberHolen);
    ui->schrauberTable->setModel(model);

    dbhelper.trennen();
}

SchrauberAnzeigen::~SchrauberAnzeigen()
{
    delete ui;
}

void SchrauberAnzeigen::on_schliessen_clicked()
{
    this->close();
}
