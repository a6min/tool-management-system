#include "schrauber.h"
#include "ui_schrauber.h"

Schrauber::Schrauber(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Schrauber)
{
    ui->setupUi(this);
}

Schrauber::~Schrauber()
{
    delete ui;
}
