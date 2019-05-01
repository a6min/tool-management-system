#ifndef SCHRAUBERSZGHINZUFUEGEN_H
#define SCHRAUBERSZGHINZUFUEGEN_H

#include <QDialog>

namespace Ui {
class SchrauberSZGHinzufuegen;
}

class SchrauberSZGHinzufuegen : public QDialog
{
    Q_OBJECT

public:
    explicit SchrauberSZGHinzufuegen(QWidget *parent = nullptr);
    ~SchrauberSZGHinzufuegen();

private:
    Ui::SchrauberSZGHinzufuegen *ui;
};

#endif // SCHRAUBERSZGHINZUFUEGEN_H
