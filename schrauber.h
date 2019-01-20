#ifndef SCHRAUBER_H
#define SCHRAUBER_H

#include <QMainWindow>

namespace Ui {
class Schrauber;
}

class Schrauber : public QMainWindow
{
    Q_OBJECT

public:
    explicit Schrauber(QWidget *parent = nullptr);
    ~Schrauber();

private:
    Ui::Schrauber *ui;
};

#endif // SCHRAUBER_H
