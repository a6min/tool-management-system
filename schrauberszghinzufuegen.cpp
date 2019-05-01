#include "schrauberszghinzufuegen.h"
#include "ui_schrauberszghinzufuegen.h"

SchrauberSZGHinzufuegen::SchrauberSZGHinzufuegen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchrauberSZGHinzufuegen)
{
    ui->setupUi(this);
}

SchrauberSZGHinzufuegen::~SchrauberSZGHinzufuegen()
{
    delete ui;
}
