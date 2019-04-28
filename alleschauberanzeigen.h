#ifndef ALLESCHAUBERANZEIGEN_H
#define ALLESCHAUBERANZEIGEN_H

#include <QWidget>
#include "databasehelper.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "ui_alleschauberanzeigen.h"

namespace Ui {
class alleSchauberAnzeigen;
}

class alleSchauberAnzeigen : public QWidget
{
    Q_OBJECT

public:
    explicit alleSchauberAnzeigen(QWidget *parent = nullptr);
    ~alleSchauberAnzeigen();

private:
    Ui::alleSchauberAnzeigen *ui;
    void schrauberAnzeigen(Ui::alleSchauberAnzeigen *ui);
};

#endif // ALLESCHAUBERANZEIGEN_H
