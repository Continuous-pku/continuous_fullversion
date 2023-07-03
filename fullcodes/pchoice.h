#ifndef PCHOICE_H
#define PCHOICE_H

#include <QWidget>
#include"QStringList"
#include"class.h"
class policy;

namespace Ui {
class pchoice;
}

class pchoice : public QWidget
{
    Q_OBJECT

    friend class policy;
public:
    explicit pchoice(policy *parent = nullptr);
    ~pchoice();
    void paintEvent(QPaintEvent *event);
    void set_items(Policy* pol);
    //void set_title(QString& s);
    //void set_picture

private slots:
    void on_exit_clicked();

    void on_take_effect_clicked();

private:
    Ui::pchoice *ui;
    QStringList ops,texts;
    Policy* p=NULL;
    policy* parent_;
};

#endif // PCHOICE_H
