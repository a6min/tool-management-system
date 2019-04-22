#include "schrauberhinzufuegen.h"
#include "ui_schrauberhinzufuegen.h"

SchrauberHinzufuegen::SchrauberHinzufuegen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberHinzufuegen)
{
    ui->setupUi(this);
}

SchrauberHinzufuegen::~SchrauberHinzufuegen()
{
    delete ui;
}
