#ifndef SCHRAUBERANZEIGEN_H
#define SCHRAUBERANZEIGEN_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <databasehelper.h>

namespace Ui {
class SchrauberAnzeigen;
}

class SchrauberAnzeigen : public QDialog
{
    Q_OBJECT

public:
    explicit SchrauberAnzeigen(QWidget *parent = nullptr);
    ~SchrauberAnzeigen();

private slots:
    void on_schliessen_clicked();

private:
    Ui::SchrauberAnzeigen *ui;
};

#endif // SCHRAUBERANZEIGEN_H
