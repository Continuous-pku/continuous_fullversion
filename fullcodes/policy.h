#ifndef POLICY_H
#define POLICY_H

#include <QWidget>
#include"QStyleOption"
#include<QPainter>
//#include"QMouseEvent"

class mainw;
class pchoice;

namespace Ui {
class policy;
}

class policy : public QWidget
{
    Q_OBJECT

public:
    explicit policy(mainw *parent = nullptr);
    ~policy();
    mainw* p;
    void showits();
    //void paintEvent(QPaintEvent *event);
    //void mousePressEvent(QMouseEvent *event);

private slots:
    void hesuan_clicked();
    void on_exit_clicked();

    void on_keyan_clicked();

    void on_canguan_clicked();

    void on_kaixue_clicked();

    void on_shipin_clicked();

    void on_wangke_clicked();

    void on_pf_clicked();

private:
    Ui::policy *ui;
    pchoice* son;
};

#endif // POLICY_H
