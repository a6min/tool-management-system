#ifndef SCHRAUBERANZEIGEN_H
#define SCHRAUBERANZEIGEN_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDebug>
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

    void on_schrauberTable_clicked(const QModelIndex &index);

private:
    Ui::SchrauberAnzeigen *ui;
    DatabaseHelper dbhelper;
};

#endif // SCHRAUBERANZEIGEN_H
