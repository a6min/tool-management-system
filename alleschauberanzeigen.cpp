#include "alleschauberanzeigen.h"
#include "ui_alleschauberanzeigen.h"

alleSchauberAnzeigen::alleSchauberAnzeigen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alleSchauberAnzeigen)
{
    ui->setupUi(this);
    schrauberAnzeigen(ui);
}

alleSchauberAnzeigen::~alleSchauberAnzeigen()
{
    delete ui;
}

void alleSchauberAnzeigen(Ui::alleSchauberAnzeigen ui){
    DatabaseHelper dbhelper;
    dbhelper.verbinden();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *alleSchrauberHolen = new QSqlQuery();
    alleSchrauberHolen->prepare("select * from schrauber");
    alleSchrauberHolen->exec();

    model->setQuery(*alleSchrauberHolen);

    dbhelper.trennen();
}
