#ifndef SCHRAUBERHINZUFUEGEN_H
#define SCHRAUBERHINZUFUEGEN_H

#include <QDialog>

namespace Ui {
class SchrauberHinzufuegen;
}

class SchrauberHinzufuegen : public QDialog
{
    Q_OBJECT

public:
    explicit SchrauberHinzufuegen(QWidget *parent = nullptr);
    ~SchrauberHinzufuegen();

private:
    Ui::SchrauberHinzufuegen *ui;
};

#endif // SCHRAUBERHINZUFUEGEN_H
