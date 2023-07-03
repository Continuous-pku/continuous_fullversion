#ifndef TUTOR_H
#define TUTOR_H

#include <QWidget>

namespace Ui {
class tutor;
}

class tutor : public QWidget
{
    Q_OBJECT

public:
    explicit tutor(QWidget *parent = nullptr);
    ~tutor();

private slots:
    void on_exit_clicked();

    void on_last_clicked();

    void on_next_clicked();

private:
    Ui::tutor *ui;
    int state=1;
    void show_stuff();
};

#endif // TUTOR_H
